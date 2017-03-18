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
#include "cblas.h"
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

    // init parameters
    memset(&state, 0, sizeof(state));
    state.pos[2] = 3;
    frame.mass = 0.8; // kg
}
#include <stdio.h>
void QRdynamic::update(void)
{
    /* update quad_rotor_model */
    quadrotor_model();
    /* update controller */
    controller_pid();

printf("pos = [ %f, %f, %f ]\n", state.pos[0], state.pos[1], state.pos[2]);
}

void QRdynamic::quadrotor_model(void)
{
    float L = frame.size/2.0;
    float k = frame.k;
    float b = frame.b;
    float kd = frame.kd;
    float* motor_rot_speed = state.motor_rot_speed;

    // compute thrust given rotation speeds of motors and thrust coefficient (k), body frame
    float T_B[3] = {0., 0., k*( motor_rot_speed[0]*motor_rot_speed[0] +
                              motor_rot_speed[1]*motor_rot_speed[1] +
                              motor_rot_speed[2]*motor_rot_speed[2] +
                              motor_rot_speed[3]*motor_rot_speed[3])};
    // compute torques, given rotation speeds of motors, length from quadrotor center to motor (L), drag coefficient (b), thrust coefficient (k), body frame
    float tau_B[3] = {
        L*k*(motor_rot_speed[0]*motor_rot_speed[0] - motor_rot_speed[2]*motor_rot_speed[2]),
        L*k*(motor_rot_speed[1]*motor_rot_speed[1] - motor_rot_speed[3]*motor_rot_speed[3]),
        b*(motor_rot_speed[0]*motor_rot_speed[0] - motor_rot_speed[1]*motor_rot_speed[1] + motor_rot_speed[2]*motor_rot_speed[2] - motor_rot_speed[3]*motor_rot_speed[3])
    };
    // body frame to inertial frame
    float R[9] = {
        std::cos(state.eta[0])*std::cos(state.eta[2]) - std::cos(state.eta[1])*std::sin(state.eta[0])*std::sin(state.eta[2]),
        -std::cos(state.eta[2])*std::sin(state.eta[0]) - std::cos(state.eta[0])*std::cos(state.eta[1])*std::sin(state.eta[2]),
        std::sin(state.eta[1])*std::sin(state.eta[2]),
        std::cos(state.eta[1])*std::cos(state.eta[2])*std::sin(state.eta[0]) + std::cos(state.eta[0])*std::sin(state.eta[2]),
        std::cos(state.eta[0])*std::cos(state.eta[1])*std::cos(state.eta[2]) - std::sin(state.eta[0])*std::sin(state.eta[2]),
        -std::cos(state.eta[2])*std::sin(state.eta[1]),
        std::sin(state.eta[0])*std::sin(state.eta[1]),
        std::cos(state.eta[0])*std::sin(state.eta[1]),
        std::cos(state.eta[1])
    };
    // compute acceleration a, given T_B, R, friction coefficient kd, translation velocity in inertial frame (state.vel)
    float T[3] = {0., 0., 0.}; // thrust, inertial frame
    cblas_sgemv(CblasRowMajor, CblasNoTrans, 3, 3, 1.0, R, 3, T_B, 1, 1.0, T, 1);
    float Fd[3] = { -kd*state.vel[0], -kd*state.vel[1], -kd*state.vel[2]};
    float a[3] = {
        0. + (T[0] + Fd[0])/frame.mass,
        0. + (T[1] + Fd[1])/frame.mass,
        -9.8 + (T[2] + Fd[2])/frame.mass
    };

    // compute w (omega), given etadot_to_w matrix and rotation angle (eta), rotational speed (eta_dot)
    float etadot_to_w[9] = {
        1.,
        0.,
        -std::sin(state.eta[1]),
        0.,
        std::cos(state.eta[0]),
        std::cos(state.eta[1])*std::sin(state.eta[0]),
        0.,
        -std::sin(state.eta[0]),
        std::cos(state.eta[1])*std::cos(state.eta[0])
    };
    float w[3] = {0., 0., 0.};
    cblas_sgemv(CblasRowMajor, CblasNoTrans, 3, 3, 1.0, etadot_to_w, 3, state.eta_dot, 1, 1.0, w, 1);
    // compute angular acceleration (wdot), given tau_B, w, inertial matrix of quadrotor (I)
    float Iw[3] = {0., 0., 0.}; // I*w
    cblas_sgemv(CblasRowMajor, CblasNoTrans, 3, 3, 1.0, frame.I, 3, w, 1, 1.0, Iw, 1);
    float w_cross_Iw[3] = {
        w[1]*Iw[2] - w[2]*Iw[1],
        w[2]*Iw[0] - w[0]*Iw[2],
        w[0]*Iw[1] - w[1]*Iw[0],
    }; // w x (Iw)
    float tau_sub_w_cross_Iw[3]; // tau - w x (Iw)
    memcpy(tau_sub_w_cross_Iw, tau_B, sizeof(tau_B));
    cblas_saxpy(3, -1.0, w_cross_Iw, 1, tau_sub_w_cross_Iw, 1);
    float wdot[3]; memcpy(wdot, tau_sub_w_cross_Iw, sizeof(wdot)); // \dot{\w}
    cblas_strsv(CblasRowMajor, CblasLower, CblasNoTrans, CblasUnit, 3, frame.I, 3, wdot, 1);

    // refresh w
    cblas_saxpy(3, dt, wdot, 1, w, 1); // w = w + wdot * dt
    // refresh eta_dot, given w_to_etadot matrix and w
    float eta_dot[3]; memcpy(eta_dot, w, sizeof(eta_dot));
    cblas_strsv(CblasRowMajor, CblasLower, CblasNoTrans, CblasUnit, 3, etadot_to_w, 3, eta_dot, 1);
    memcpy(state.eta_dot, eta_dot, sizeof(eta_dot));
    // refresh eta
    cblas_saxpy(3, dt, state.eta_dot, 1, state.eta, 1); // eta = eta + eta_dot * dt
    // refresh velocity
    cblas_saxpy(3, dt, a, 1, state.vel, 1); // vel = vel + a * dt
    // refresh position
    cblas_saxpy(3, dt, state.vel, 1, state.pos, 1); // pos = pos + vel * dt

    // constrain of ground
    if (state.pos[2] < 0.)
        state.pos[2] = 0.;

    // save to global
    memcpy(QR_pos, state.pos, 3*sizeof(float));
}

void QRdynamic::controller_pid(void)
{

    /* attitude control loop */

}

/* End of file quadrotor.cxx */
