/*--------------------------------------------------------------------------
 *
 * quadrotor -- Simple quad rotor model
 *
 * 
 *
 * Date: 2016-02-23 Roice (LUO Bing) modified qrmod.cxx for RAOS project
 *       2016-03-09 Roice modified this file to make it compatible with
 *                  robot.cxx
 *
 *--------------------------------------------------------------------------
 */

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "cblas.h"

#define PI 3.14159265358979323846

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

/* calculate four rotors' pos according to quadrotor's pos and att */
void QRCalculateAllRotorPos(const float* pos, const float* att, float strut, float* rpos1, float* rpos2, float* rpos3, float* rpos4) {
    // init rotor pos vector
    memcpy(rpos1, pos, 3*sizeof(float));
    memcpy(rpos2, pos, 3*sizeof(float));
    memcpy(rpos3, pos, 3*sizeof(float));
    memcpy(rpos4, pos, 3*sizeof(float));

    // calculate rotor pos
    float v[3] = {strut, 0.0, 0.0};
    rotate_vector(v, rpos1, att[0], att[1], att[2]);
    rotate_vector(v, rpos2, 90+att[0], att[1], att[2]);
    rotate_vector(v, rpos3, 180+att[0], att[1], att[2]);
    rotate_vector(v, rpos4, 270+att[0], att[1], att[2]);
}

/* End of file quadrotor.cxx */
