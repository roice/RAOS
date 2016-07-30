/*
 * Simulation Loop of Robot Active Olfaction
 *
 * This file implements the simulation loop of RAOS
 *
 * Author: Roice (LUO Bing)
 * Date: 2016-02-24 create this file
 */
#include "model/robot.h"
#include "model/SimModel.h"
#include "SimLoop.h"
#include <math.h>
#include <stdio.h>

GasDistMapping::GasDistMapping(void)
{
    float z = 1.8; // m

    for (int i = 0; i < 20; i++) {
        zigzag_waypoints[i][2] = z;

        if (i == 0 || i== 3 || i==4 || i==7 || i==8 || i==11 || i==12 ||
                i== 15 || i==16 || i==19)
            zigzag_waypoints[i][1] = 4.5;
        else
            zigzag_waypoints[i][1] = -4.5;
    }
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 2; j++)
            zigzag_waypoints[i*2+j][0] = 4.5-i*1.0;

    // init waypoint indexing
    next_waypoint_index = 8;
}

void GasDistMapping::waypoint_update(Robot* robot, SimState_t* sim_state)
{
    float vel_nrm = 0.1; // 1 m/s

    // get robot's position
    float* pos = &(robot->state.pos[0]);
    float* vel = &(robot->state.vel[0]);
    float dist[3];

    if (next_waypoint_index >= 20)
        return;

    // calculate the direction to fly
    for (int i = 0; i < 3; i++)
        dist[i] = zigzag_waypoints[next_waypoint_index][i] - pos[i];
    double dist_nrm = sqrt(dist[0]*dist[0] + dist[1]*dist[1] + dist[2]*dist[2]);
    for (int i = 0; i < 3; i++) {
        if (fabs(dist[i]) < 0.001)
            vel[i] = 0;
        else
            vel[i] = float(dist[i])*vel_nrm/dist_nrm;
    }
    // update robot's position
    for (int i = 0; i < 3; i++)
        pos[i] += vel[i]*sim_state->dt;

    if (fabs(dist[0]) < 0.1 && fabs(dist[1]) < 0.1 && fabs(dist[2]) < 0.1) {
        next_waypoint_index++;
        printf("next_way_point: %d\n", next_waypoint_index);
        fflush(stdout);
    }
}

/* End of file SimLoop.cxx */
