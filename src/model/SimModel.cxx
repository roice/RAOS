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
#include "model/wake.h"

/* Pointers of instances of RAOS models */
static std::vector<Robot*> robots; // pointer array of robot instances

void SimModel_init(void)
{
    /* create & init robot */
    Robot* new_robot = new Robot("helicopter");
    new_robot->state.pos[2] = 2.0;
    new_robot->init();
    robots.push_back(new_robot);

    /* init parallelization of rotor wakes computation */
    WakesInit(&robots);
}

void SimModel_update(void) {
    /* update robot */
    for (int i = 0; i < robots.size(); i++)
        robots.at(i)->update();

    /* update rotor wakes */
    WakesUpdate(&robots);

    /* update plume */
    //plume_update();
}

void SimModel_finish(void)
{
    // free memory of GPU computation
    WakesFinish();
}

// get the pointer to the robots
std::vector<Robot*>* SimModel_get_robots(void)
{
    return &robots;
}

/* End of SimModel.cxx */
