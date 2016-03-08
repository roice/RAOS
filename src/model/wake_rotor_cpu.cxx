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
#include "model/qrmod.h" // for type qrstate_t
#include "model/wake_rotor_cpu.h"

#define PI 3.14159265358979323846


// local function to compute vector cross product, N = 3
static void local_v3cp(const float* a, const float* b, float* out)
{
    
    out[0] = a[1]*b[2] - a[2]*b[1];
    out[1] = a[2]*b[0] - a[0]*b[2];
    out[2] = a[0]*b[1] - a[1]*b[0];
}
// calculate induced velocity from a vortex line segment to a point
//  a and b are endpoints of the vortex line segment
//  p is the point
static void BiotSavartInduction(const float* a, const float* b, const float* p, float Gamma, float* ind) {
    float ap[3], bp[3], ab[3], ba[3];
    
    // get vectors AP, BP and AB & BA
    memcpy(ap, p, sizeof(ap));
    cblas_saxpy(3, -1.0, a, 1, ap, 1);
    memcpy(bp, p, sizeof(bp));
    cblas_saxpy(3, -1.0, b, 1, bp, 1);
    memcpy(ab, b, sizeof(ab));
    cblas_saxpy(3, -1.0, a, 1, ab, 1);
    memcpy(ba, a, sizeof(ba));
    cblas_saxpy(3, -1.0, b, 1, ba, 1);
    
    // cos(ap-ab) and cos(ba-bp)
    float nrm2_ab = cblas_snrm2(3, ab, 1);
    float nrm2_ap = cblas_snrm2(3, ap, 1);
    float nrm2_bp = cblas_snrm2(3, bp, 1);
    if (nrm2_ab == 0.0 || nrm2_ap == 0.0 || nrm2_bp == 0.0) {// prevent producing NaN
        memset(ind, 0, 3*sizeof(float));
        return;
    }
    float cos_apab = cblas_sdot(3, ap, 1, ab, 1)/(nrm2_ap*nrm2_ab);
    float cos_babp = cblas_sdot(3, ba, 1, bp, 1)/(nrm2_ab*nrm2_bp);
    
    // h, perpendicular distance from P to AB
    float h = nrm2_ap * sqrt(1 - cos_apab*cos_apab);
    // calculate strength
    float scale = Gamma/(4*PI)*(h/(0.0001 + pow(h, 2)))*(cos_apab+cos_babp);

        //printf("sqrt(0) = %f, h = %f, scale = %f\n", sqrt(1 - 1.000000000), h, scale);
        //fflush(stdout);

    // get dir indicating the dir of induced velocity
    local_v3cp(ap, bp, ind);
    float e_nrm = cblas_snrm2(3, ind, 1);
    cblas_sscal(3, scale/e_nrm, ind, 1);
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
void rotate_vector(const float* vector, float* out, float yaw, float pitch, float roll)
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

/* get the induced velocity at a position, given several rotor wakes
 * arguments:
 *      vel         velocity vector, the result
 *      idx_rotor   index of rotor, which the marker belongs to
 *      idx_blade   index of blade, which the marker is produced by
 *      idx_marker  index of marker in that vortex filament
 *      wakes       an array containing the pointers of all RotorWake instances
 *      n_rotors    number of rotors
 */
void CalculateInducedVelocityOfMarker(float* vel, const int idx_rotor, const int idx_blade, const int idx_marker, RotorWake** wakes, const int n_rotors)
{
    int n_blades; // number of blades of a rotor, i.e., number of tip vortex filaments produced by a rotor
    int len_fila; // length of a vortex filament, i.e., number of markers of a filament
    float ind[3]; // induced velocity
    float temp[3]; // temporary array


//printf("vel = {%f, %f, %f}\n", vel[0], vel[1], vel[2]);
//fflush(stdout);

    memset(ind, 0, sizeof(ind));

//printf("ind = {%f, %f, %f}\n", ind[0], ind[1], ind[2]);
//fflush(stdout);

    for (int idx_r = 0; idx_r < n_rotors; idx_r++)
    {// traverse each rotor
        n_blades = wakes[idx_r]->rotor_state.frame.n_blades;

//printf("n_blades = %d\n", n_blades);
//fflush(stdout);

        for (int idx_b = 0; idx_b < n_blades; idx_b++) 
        {// traverse each blade/filament
            len_fila = wakes[idx_r]->wake_state.size()/n_blades;

//printf("len_fila = %d\n", len_fila);
//fflush(stdout);

            for (int idx_m = 0; idx_m < len_fila-1; idx_m++)
            {// traverse each segment of this filament

                // calculate the velocity induced by this vortex segment
                if ( idx_r == idx_rotor && idx_b == idx_blade && (idx_m == idx_marker || idx_m+1 == idx_marker) )
                    // skip this segment if the marker is one of the endpoint of this segment
                    continue;
                else
                {

//printf("%f\n", wakes[idx_r]->wake_state.at(idx_m*n_blades+idx_b).pos[0]);
//fflush(stdout);

                    BiotSavartInduction(
                            wakes[idx_r]->wake_state.at(idx_m*n_blades+idx_b).pos,
                            wakes[idx_r]->wake_state.at((idx_m+1)*n_blades+idx_b).pos,
                            wakes[idx_rotor]->wake_state.at(idx_marker*wakes[idx_rotor]->rotor_state.frame.n_blades+idx_blade).pos,
                            wakes[idx_r]->wake_state.at(idx_m*n_blades+idx_b).Gamma, temp);

//printf("%f\n", temp[0]);
//fflush(stdout);

                    cblas_saxpy(3, 1.0, temp, 1, ind, 1);
                }
            }// traversed this filament
        }// traversed all filaments of this rotor
    } // by far the induced velocity at a marker has been calculated
    // save result
    
//printf("ind = {%f, %f, %f}\n", ind[0], ind[1], ind[2]);
//fflush(stdout);

    memcpy(vel, ind, sizeof(ind));
}

void RotorWake::init(const qrstate_t* qrstate) // rotor wake initialization
{// by far config and rotor_state should be artificially configured

    // init vortex markers state
    max_markers = int(360.0*config.rounds/config.dpsi)+1; // calculate max lagrangian markers of a vortex filament
    wake_state.reserve(rotor_state.frame.n_blades*(max_markers+10)); // 10 is an arbitrary number, can be num>=1


//printf("wake_state.capacity = %d\n", wake_state.capacity());
//fflush(stdout);
    
    // release first pair of marker at the tips
    marker_release(qrstate);

//printf("wake_state.size = %d\n", wake_state.size());
//printf("wake_state.at(0).pos: {%f, %f, %f}\n", wake_state.at(0).pos[0], wake_state.at(0).pos[1], wake_state.at(0).pos[2]);
//fflush(stdout);

    /*
     * TODO:
     * different dt*/
    // init dt
    dt = config.dpsi/rotor_state.Omega; // time cost when rotor evolves interval angle

//printf("dt = %f\n", dt);
//fflush(stdout);
}

void RotorWake::maintain(const qrstate_t* qrstate) 
{/* marker maintainance */
    
    // release new markers
    marker_release(qrstate);
    
    // remove old markers
    if (wake_state.size() > max_markers) {
        for (int i = 0; i < rotor_state.frame.n_blades; i++)
            wake_state.erase(wake_state.begin());
    }

    /*
     * TODO:
     * different dt*/
    // update dt
    dt = config.dpsi/rotor_state.Omega; // time cost when rotor evolves interval angle
}

void RotorWake::marker_release(const qrstate_t* qrstate) {

    VortexMarker_t new_marker;
    float p_marker[3] = {rotor_state.frame.radius, 0, 0};

    // clear velocity
    memset(new_marker.vel, 0, sizeof(new_marker.vel));
    
//printf("vel = {%f, %f, %f}\n", new_marker.vel[0], new_marker.vel[1], new_marker.vel[2]);
//fflush(stdout);

    // calculate the tip vortex circulation: Gamma
    new_marker.Gamma = 1; // tip vortex circulation

    for (int i = 0; i < rotor_state.frame.n_blades; i++) {
        // calculate the position of this marker     
        memcpy(new_marker.pos, rotor_state.pos, sizeof(new_marker.pos));
        rotate_vector(p_marker, new_marker.pos, 360.0/rotor_state.frame.n_blades*i+rotor_state.psi+qrstate->psi, qrstate->theta, qrstate->phi);
        // push to wake state array
        wake_state.push_back(new_marker);

//printf("new_marker.pos = {%f, %f, %f}\n", new_marker.pos[0], new_marker.pos[1], new_marker.pos[2]);
//fflush(stdout);
    }

    // update blade azimuth
    if (rotor_state.psi + config.dpsi >= 360.0)
        rotor_state.psi += config.dpsi - 360.0;
    else
        rotor_state.psi += config.dpsi;


//printf("rotor_state.psi = %f\n", rotor_state.psi);
//fflush(stdout);
}

// Constructor
RotorWake::RotorWake(void)
{
    // init configurations
    config.dpsi = 15; // degrees
    config.rounds = 20; // 20 rounds

    // init rotor state
    rotor_state.frame.radius = 0.1; // meter
    rotor_state.frame.n_blades = 2; // two-blade
    rotor_state.pos[0] = 0; // meter
    rotor_state.pos[1] = 0;
    rotor_state.pos[2] = 0;
    rotor_state.Omega = 2*PI; // rad/s
    rotor_state.psi = 0;

    // init private parameters
    max_markers = 10;
    dt = 1.0;
}

/**********************************************************
 ***************** TEST THIS FILE **********************
 *********************************************************/
#ifdef TEST

int main(int argc, char **argv) {
#if 0
    RotorWake wake;

    qrstate_t qrstate;
    qr_init(&qrstate);

    wake.init(&qrstate);

    while(1) {
        wake.maintain(&qrstate);
    }
#endif

    // test BiotSavart
    float a[3] = {1,0,0};
    float b[3] = {0,1,0};
    float p[3] = {0,0,1};
    float vel[3];

    BiotSavartInduction(a,b,p,1,vel);

    printf("vel = {%f, %f, %f\n}", vel[0], vel[1], vel[2]);

    return 0;
}

#endif
