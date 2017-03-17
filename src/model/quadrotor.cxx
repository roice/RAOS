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

#include <cmath>
#include <string.h>
#include "common/math/rotation.h"
#include "model/quadrotor.h"

#ifndef RAD2DEG
#define RAD2DEG (180.0/M_PI)
#endif

/* calculate four rotors' pos according to quadrotor's pos and att */
void QRCalculateAllRotorPos(const float* pos, const float* att, float strut, float* rpos1, float* rpos2, float* rpos3, float* rpos4) {
    // init rotor pos vector
    memcpy(rpos1, pos, 3*sizeof(float));
    memcpy(rpos2, pos, 3*sizeof(float));
    memcpy(rpos3, pos, 3*sizeof(float));
    memcpy(rpos4, pos, 3*sizeof(float));

#if 1
    // shape: +
    float v1[3] = {strut, 0.0, 0.0};
    float v2[3] = {0.0, strut, 0.0};
    float v3[3] = {-strut, 0.0, 0.0};
    float v4[3] = {0.0, -strut, 0.0};
#else
    // shape: x
    float v1[3] = {strut/1.41421356, strut/1.41421356, 0.0};
    float v2[3] = {-strut/1.41421356, strut/1.41421356, 0.0};
    float v3[3] = {-strut/1.41421356, -strut/1.41421356, 0.0};
    float v4[3] = {strut/1.41421356, -strut/1.41421356, 0.0};
#endif

    rotate_vector(v1, rpos1, att[0]*RAD2DEG, att[1]*RAD2DEG, att[2]*RAD2DEG);
    rotate_vector(v2, rpos2, att[0]*RAD2DEG, att[1]*RAD2DEG, att[2]*RAD2DEG);
    rotate_vector(v3, rpos3, att[0]*RAD2DEG, att[1]*RAD2DEG, att[2]*RAD2DEG);
    rotate_vector(v4, rpos4, att[0]*RAD2DEG, att[1]*RAD2DEG, att[2]*RAD2DEG);
}

QRdynamic::QRdynamic(float* pos_ref, float* pos, float* att, float delta_t)
{
    // save parameters and addr
    dt = delta_t;
    QR_pos_ref = pos_ref;
    QR_pos = pos;
    QR_att = att;
}

void QRdynamic::update(void)
{}

/* End of file quadrotor.cxx */
