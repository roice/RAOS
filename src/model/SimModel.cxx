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
#include "SimLoop.h"
#include <math.h>

#include <stdio.h>

/* Pointers of instances of RAOS models */
static std::vector<Robot*> robots; // pointer array of robot instances

static SimState_t sim_state;

GasDistMapping gdm;

void SimModel_init(void)
{
    /* create & init robot */
    Robot* new_robot = new Robot("quadrotor");
    new_robot->state.pos[0] = 4.5;
    new_robot->state.pos[1] = 4.5;
    new_robot->state.pos[2] = 2.0;
    new_robot->init();
    robots.push_back(new_robot);

    /* init plume */
    plume_init();

#ifdef RAOS_FEATURE_WAKES
    /* init parallelization of rotor wakes computation */
    WakesInit(&robots);
    /* init para... of wakes-induced velocity at puffs */
    WakesIndVelatPlumePuffsInit(&robots, plume_get_fila_state());
#endif

    /* init timing */
    sim_state.time = 0.0;
    sim_state.dt = 20.0/360.0/50.0;
    sim_state.initialized = false;
}

void SimModel_update(void) {
    /* update strategy */
    if (sim_state.time > 10.0)
        gdm.waypoint_update(robots.at(0), &sim_state);
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
    if (sim_state.time > 0.5 && sim_state.initialized == false) {
        sim_state.initialized = true;
        sim_state.dt = 18.0*sim_state.dt;
    }
}

void SimModel_finish(void)
{
#ifdef RAOS_FEATURE_WAKES
    // free memory of GPU computation
    WakesFinish();
#endif
}

// get the pointer to the robots
std::vector<Robot*>* SimModel_get_robots(void)
{
    return &robots;
}

/* End of SimModel.cxx */
