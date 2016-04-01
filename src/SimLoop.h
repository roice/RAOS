/*
 * Simulation Loop of Robot Active Olfaction
 *
 * This file defines functions & global parameters of RAOS simulation loop
 *
 * Author: Roice (LUO Bing)
 * Date: 2016-02-24 create this file
 */
#ifndef SIMLOOP_H
#define SIMLOOP_H

#include "model/robot.h"
#include "model/SimModel.h"

class GasDistMapping {
    public:
        GasDistMapping(void);
        void waypoint_update(Robot*, SimState_t*);
    private:
        float zigzag_waypoints[20][3];
        int next_waypoint_index;
};

#endif

/* End of file SimLoop.h */
