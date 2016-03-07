/*
 * single-rotor wake model running on CPU
 *      Free vortex method
 *
 * Author: Roice (LUO Bing)
 * Date: 2016-03-02 create this file (RAOS)
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h> // drand48 and srand48 on Linux
#include <string.h> // memset
#include "cblas.h" // CBLAS for vector arithmetic
#include "model/wake_rotor_cpu.h"

#define PI 3.14159265358979323846


// local function to compute vector cross product, N = 3
static void local_v3cp(const float* a, const float* b, float* out)
{
    
    out[0] = a[1]*b[2] - a[2]*b[1];
    out[1] = a[2]*b[0] - a[0]*b[2];
    out[2] = a[0]*b[1] - a[1]*b[0];
}
// local function to compute vector minus vector
//   out = a - b
static void local_vmv(const int N, const float* a, const float* b, float* out)
{
    for (int i = 0; i < N; i++) {
        out[i] = a[i] - b[i];
    }
}
// calculate induced velocity from a vortex line segment to a point
//  a and b are endpoints of the vortex line segment
//  p is the point
static void BiotSavartInduction(const float* a, const float* b, const float* p, float Gamma, float* ind) {
    float ap[3], bp[3], ab[3], ba[3];
    // get vectors AP, BP and AB & BA
    local_vmv(3, p, a, ap);
    local_vmv(3, p, b, bp);
    local_vmv(3, b, a, ab);
    local_vmv(3, a, b, ba);
    // cos(ap-ab) and cos(ba-bp)
    float nrm2_ab = cblas_snrm2(3, ab, 1);
    float cos_apab = cblas_sdot(3, ap, 1, ab, 1)/(cblas_snrm2(3, ap, 1)*nrm2_ab);
    float cos_babp = cblas_sdot(3, ba, 1, bp, 1)/(nrm2_ab*cblas_snrm2(3, bp, 1));
    // h, perpendicular distance from P to AB
    float h = cblas_snrm2(3, ap, 1) * sqrt(1 - cos_apab*cos_apab);
    // e, unit vector indicating the dir of induced velocity
    float e[3];
    local_v3cp(ap, bp, e);
    float e_nrm = cblas_snrm2(3, e, 1);
    for (int i = 0; i < 3; i++)
        e[i] = e[i]/e_nrm;
    float scale = Gamma/(4*PI)*(h/sqrt(pow(0.01, 4)+pow(h, 4)))*(cos_apab+cos_babp);
    for (int i = 0; i < 3; i++)
        ind[i] = e[i]*scale;
}
/* rotate a vector with angles yaw pitch roll (degree)
 * Right-Hand(counterclockwise)
 * 
 *                 cos(yaw)  -sin(yaw)  0
 *    R_z(yaw)   = sin(yaw)  cos(yaw)   0
 *                    0         0       1
 *
 *                 cos(pitch)   0     sin(pitch)
 *    R_y(pitch) =     0        1         0
 *                 -sin(pitch)  0     cos(pitch)
 *
 *                     1        0         0
 *    R_x(roll)  =     0    cos(roll)  -sin(roll)
 *                     0    sin(roll)   cos(roll)
 *
 *    R(yaw, pitch, roll) = R_z(yaw)R_y(pitch)R_x(roll)
 *
 *    out = R * vector + out
 */
static void rotate_vector(float* vector, float* out, float yaw, float pitch, float roll)
{
    // calculate rotation matrix
    float sin_yaw = sin(yaw*PI/180.0);
    float cos_yaw = cos(yaw*PI/180.0);
    float sin_pitch = sin(pitch*PI/180.0);
    float cos_pitch = cos(pitch*PI/180.0);
    float sin_roll = sin(roll*PI/180.0);
    float cos_roll = cos(roll*PI/180.0);
    float R_x[9], R_y[9], R_z[9];
    R_z[0] = cos_yaw;
    R_z[1] = -sin_yaw;
    R_z[2] = 0.0;
    R_z[3] = sin_yaw;
    R_z[4] = cos_yaw;
    R_z[5] = 0.0;
    R_z[6] = 0.0;
    R_z[7] = 0.0;
    R_z[8] = 1.0;
    R_y[0] = cos_pitch;
    R_y[1] = 0.0;
    R_y[2] = sin_pitch;
    R_y[3] = 0.0;
    R_y[4] = 1.0;
    R_y[5] = 0.0;
    R_y[6] = -sin_pitch;
    R_y[7] = 0.0;
    R_y[8] = cos_pitch;
    R_x[0] = 1.0;
    R_x[1] = 0.0;
    R_x[2] = 0.0;
    R_x[3] = 0.0;
    R_x[4] = cos_roll;
    R_x[5] = -sin_roll;
    R_x[6] = 0.0;
    R_x[7] = sin_roll;
    R_x[8] = cos_roll;
    // rotate
    float R_zy[9];
    float R_zyx[9];
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 3, 3, 3, 1.0, R_z, 3, R_y, 3, 0.0, R_zy, 3);
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 3, 3, 3, 1.0, R_zy, 3, R_x, 3, 0.0, R_zyx, 3);
    cblas_sgemv(CblasRowMajor, CblasNoTrans, 3, 3, 1.0, R_zyx, 3, vector, 1, 1.0, out, 1);
}
void RotorWake::init(void) // rotor wake initialization
{// by far config and rotor_state should be artificially configured

    // init vortex markers state
    max_markers = int(360.0*config.rounds/config.dpsi)+1; // calculate max lagrangian markers of a vortex filament
    wake_state.reserve(rotor_state.frame.n_blades*(max_markers+10)); // 10 is an arbitrary number, can be num>=1
    
    // release first pair of marker at the tip
    marker_release();

    // init dt
    dt = config.dpsi/rotor_state.Omega; // time cost when rotor evolves interval angle
}

void RotorWake::update(void) 
{// update markers

    float p[3] = {0,0,0};
    float temp[3], ind[3];

    /* Step 1: update existing markers */
    for (int i = 0; i < wake_state.size(); i++) {// for each marker
        memset(ind, 0, sizeof(ind)); // clear ind[3]
        // calculate overall flow at this marker's position
        for (int j = 0; j < wake_state.size() - 1; j++) {
            if ((i == j) || (i-1 == j)) // skip this segment if i-th marker is on it
                continue;
            else
            {
                BiotSavartInduction(wake_state.at(j).pos, wake_state.at(j+1).pos, 
                        wake_state.at(i).pos, wake_state.at(j).Gamma, temp);
                for (int idx = 0; idx < 3; idx++)
                    ind[idx] += temp[idx];
            }
        } // by far the induced velocity at a marker has been calculated
        // save velocity to state
        memcpy(wake_state.at(i).vel, ind, sizeof(ind));
    }

    /* Step 2: marker maintainance */
    // release new markers
    marker_release();
    // remove old markers
    if (wake_state.size() > max_markers)
        wake_state.erase(wake_state.begin());
}

void RotorWake::marker_release(void) {

    VortexMarker_t new_marker;

    // calculate the tip vortex circulation: Gamma
    new_marker.Gamma = 1; // tip vortex circulation

    // calculate the position of this marker
    float p_marker[3] = {rotor_state.frame.radius, 0, 0};
    new_marker.pos[0] = rotor_state.x;
    new_marker.pos[1] = rotor_state.y;
    new_marker.pos[2] = rotor_state.z;
    rotate_vector(p_marker, new_marker.pos, rotor_state.psi, rotor_state.pitch, rotor_state.roll);
    // update blade azimuth
    if (rotor_state.psi + config.dpsi >= 360.0)
        rotor_state.psi += config.dpsi - 360.0;
    else
        rotor_state.psi += config.dpsi; 

    // init other params
    memset(new_marker.vel, 0, sizeof(new_marker.vel));

    wake_state.push_back(new_marker);

    printf("pos = {%f, %f, %f}\n", wake_state.back().pos[0], wake_state.back().pos[1], wake_state.back().pos[2]);
}

// Constructor
RotorWake::RotorWake(void)
{
    // init configurations
    config.dpsi = 15; // degrees
    config.rounds = 20; // 20 rounds

    // init rotor state
    rotor_state.frame.radius = 0.2; // meter
    rotor_state.frame.n_blades = 2; // two-blade
    rotor_state.roll = 0; // degree
    rotor_state.pitch = 0;
    rotor_state.yaw = 0;
    rotor_state.x = 0; // meter
    rotor_state.y = 0;
    rotor_state.z = 0;
    rotor_state.Omega = 2*PI; // rad/s

    // init private parameters
    max_markers = 10;
    dt = 1.0;
}

/**********************************************************
 ***************** TEST THIS FILE **********************
 *********************************************************/
#if 1

int main(int argc, char **argv) {
    RotorWake wake;
    wake.init();

    while(1) {
        wake.update();
    }

    return 0;
}

#endif
