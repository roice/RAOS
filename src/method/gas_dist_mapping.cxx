/*
 * Gas Distribution Mapping
 *
 * Author: Roice (LUO Bing)
 * Date: 2017-03-16 create this file
 */
#include "model/robot.h"
#include "model/SimModel.h"
#include <math.h>
#include <stdio.h>

class GasDistMapping {
    public:
        GasDistMapping(void);
        void waypoint_update(Robot*, SimState_t*);
    private:
        float zigzag_waypoints[20][3];
        int next_waypoint_index;
};

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
    float vel_nrm = 1.0; // velocity

    // get robot's position
    float* ref_pos = &(robot->ref_state.pos[0]);
    float dist[3];

    float ref_vel[3] = {0};

    if (next_waypoint_index >= 20)
        return;

    // calculate the direction to fly
    for (int i = 0; i < 3; i++)
        dist[i] = zigzag_waypoints[next_waypoint_index][i] - ref_pos[i];
    double dist_nrm = sqrt(dist[0]*dist[0] + dist[1]*dist[1] + dist[2]*dist[2]);
    for (int i = 0; i < 3; i++) {
        if (fabs(dist[i]) < 0.001)
            ref_vel[i] = 0;
        else
            ref_vel[i] = float(dist[i])*vel_nrm/dist_nrm;
    }
    // update robot's position
    for (int i = 0; i < 3; i++)
        ref_pos[i] += ref_vel[i]*sim_state->dt;

    if (fabs(dist[0]) < 0.1 && fabs(dist[1]) < 0.1 && fabs(dist[2]) < 0.1) {
        next_waypoint_index++;
        printf("next_way_point: %d\n", next_waypoint_index);
        fflush(stdout);
    }
}

GasDistMapping *gdm;
bool gas_dist_mapping_init(void)
{
    gdm = new GasDistMapping();
}
void gas_dist_mapping_update(SimState_t* sim_state)
{
    gdm->waypoint_update((SimModel_get_robots())->at(0), sim_state);
}
void gas_dist_mapping_stop(void)
{
    delete gdm;
}

/* End of file gas_dist_mapping.cxx */
