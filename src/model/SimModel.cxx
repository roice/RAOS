/*
 * Models of RAOS
 *
 * Author: Roice (LUO Bing)
 * Date: 2016-02-23 create this file (RAOS)
 */

#include <vector>
#include <string.h>
#include "model/robot.h"
#include "model/plume.h"
#ifdef RAOS_FEATURE_WAKES
    #include "model/wake.h"
#endif
#include "model/SimModel.h"
#include "method/method.h"
#include "SimConfig.h"
#include <math.h>

#include <stdio.h>

/* Pointers of instances of RAOS models */
static std::vector<Robot*> robots; // pointer array of robot instances

static SimState_t sim_state;

#define ESTABLISH_WAKE_DT_DIVIDE 18.0

void SimModel_init(void)
{
    SimConfig_t* configs = SimConfig_get_configs(); // get runtime configs

    /* init timing */
    sim_state.time = 0.0;
#ifdef RAOS_FEATURE_WAKES
    sim_state.dt = configs->common.dt/ESTABLISH_WAKE_DT_DIVIDE;
    sim_state.wake_initialized = false;
#else
    sim_state.dt = configs->common.dt; // 50 Hz
#endif

    /* create & init robot */
    Robot* new_robot = new Robot("quadrotor");
    new_robot->ref_state.pos[0] = 0.5;
    new_robot->ref_state.pos[1] = 4.5;
    new_robot->ref_state.pos[2] = 2.0;
    new_robot->init(configs->common.dt);
    robots.push_back(new_robot);

    /* init plume */
    plume_init();

#ifdef RAOS_FEATURE_WAKES
    /* init parallelization of rotor wakes computation */
    WakesInit(&robots);
    /* init para... of wakes-induced velocity at puffs */
    WakesIndVelatPlumePuffsInit(&robots, plume_get_fila_state());
#endif

    /* init method */
    method_init(METHOD_GAS_DIST_MAPPING); // gas distribution mapping 
}

void SimModel_update(void) {
    /* update strategy */
#ifdef RAOS_FEATURE_WAKES
    if (sim_state.wake_initialized)
#endif
        method_update(&sim_state);
        
    /* update robot */
    for (int i = 0; i < robots.size(); i++)
        robots.at(i)->update();
#ifdef RAOS_FEATURE_WAKES
    /* update rotor wakes */
    WakesUpdate(&robots, "Euler", &sim_state);

    /* update plume */
    WakesIndVelatPlumePuffsUpdate(&robots, plume_get_fila_state());
#endif

/* debug */
/*
std::vector<FilaState_t>* plume = plume_get_fila_state();
printf("v_z = %f, size_m = %d\n", plume->back().vel[2], robots.at(0)->wakes.at(0)->wake_state[0]->size());
*/
    plume_update(&sim_state);

    /* calculate concentration at robot's position */
    std::vector<FilaState_t>* puffs = plume_get_fila_state();
    float inv_sigma[3] = {1.42857, 9.34579, 9.34579};
    float delta[3];
    float power;
    float conc = 0.0;
    for (int i = 0; i < puffs->size(); i++) {
        power = 0.0;
        // get delta
        for (int k = 0; k < 3; k++)
            delta[k] = robots.at(0)->state.pos[k] - puffs->at(i).pos[k];
        for (int k = 0; k < 3; k++)
            power += delta[k]*inv_sigma[k]*delta[k];
        // calculate delta^T*sigma*delta
        conc += 1.0/1.40995*exp(-power);
    }
    robots.at(0)->state.gas_sensor = conc;

    /* update timing */
    sim_state.time += sim_state.dt;
#ifdef RAOS_FEATURE_WAKES
    if (sim_state.time > 0.5 && sim_state.wake_initialized == false) {
        sim_state.wake_initialized = true;
        sim_state.dt = ESTABLISH_WAKE_DT_DIVIDE*sim_state.dt;
    }
#endif
}

void SimModel_destroy(void)
{
#ifdef RAOS_FEATURE_WAKES
    // free memory of GPU computation
    WakesFinish();
#endif
    // destroy plumes
    plume_destroy();
    // destroy robots
    if (robots.size()) {
        for (int i = 0; i < robots.size(); i++)
        {
            robots.at(i)->destroy();
            delete robots.at(i);
        }
        robots.clear();
    }
}

SimState_t* SimModel_get_sim_state(void)
{
    return &sim_state;
}

// get the pointer to the robots
std::vector<Robot*>* SimModel_get_robots(void)
{
    return &robots;
}

/* End of SimModel.cxx */
