/*
 * Wakes in the simulation environment
 *
 * Author: Roice (LUO Bing)
 * Date: 2016-03-08 create this file (RAOS)
 */

#include "model/robot.h"
#include "model/wake_rotor.h"

/* update all of the rotor wakes in the environment
 * this routine will traverse all of the robot instances
 * and update all of the Lagrangian markers for all robots */
void WakesUpdate(std::vector<Robot*>* robots)
{
    /* maintain markers of wakes */
    for(int idx_robot = 0; idx_robot < robots->size(); idx_robot++)
    {
        for (int idx_r = 0; idx_r < robots->at(idx_robot)->wakes.size(); idx_r++) {
            robots->at(idx_robot)->wakes[idx_r]->maintain();
        }
    }
}

/* End of file wake.cxx */
