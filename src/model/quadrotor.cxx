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

#include <stdio.h>
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

#if 0
    printf("rpos1 = [ %f, %f, %f ]\n", rpos1[0], rpos1[1], rpos1[2]);
    printf("rpos2 = [ %f, %f, %f ]\n", rpos2[0], rpos2[1], rpos2[2]);
    printf("rpos3 = [ %f, %f, %f ]\n", rpos3[0], rpos3[1], rpos3[2]);
    printf("rpos4 = [ %f, %f, %f ]\n", rpos4[0], rpos4[1], rpos4[2]);
#endif
}

QRdynamic::QRdynamic(float* pos_ref, float* pos, float* att, float delta_t, const char* robot_name, const char* ctl_name, QRframe_t* frm)
{
    // save parameters and addr
    dt = delta_t;
    QR_pos_ref = pos_ref;
    QR_pos = pos;
    QR_att = att;

    // init parameters
    memset(&state, 0, sizeof(state));
    state.pos[2] = 3;
    state.eta[0] = 45.*M_PI/180.;
    frame.mass = 0.8; // kg
}

void QRdynamic::update(void)
{
    /* update quad_rotor_model */
    quadrotor_model();
    /* update controller */
    controller_pid();
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
    memcpy(QR_att, state.eta, 3*sizeof(float));
}

float limit(float x,float x1,float x2)
{
    if(x < x1)
        return x1;
    else if(x > x2)
        return x2;
    else
        return x;
}

void QRdynamic::controller_pid(void)
{
float att_ref[3] ;

    float kp_xy = 1.6;
    float kd_xy = 0.0;
    float kp_z  = 2.0;
    float kd_z  = 0.0;
    float kp_phi_the = 8.0;
    float kd_phi_the = 0.0;
    float kp_psi  = 6.0;
    float kd_psi  = 0.0;
    //float frame.mass;
    float g = 9.8;

    QR_pos_ref[0] = -1.0;
    QR_pos_ref[1] = -1.0;
    QR_pos_ref[2] = 3.0;


    static float x_error,x_errorh,x_errord;
    static float y_error,y_errorh,y_errord;
    static float z_error,z_errorh,z_errord;
    static float phi_error,phi_errorh,phi_errord;
    static float theta_error,theta_errorh,theta_errord;
    static float psi_error,psi_errorh,psi_errord;

    float x_acc,y_acc,z_acc;
    float x_force,y_force,z_force;
    float phi_acc,theta_acc,psi_acc;

    float u1,u2,u3,u4;
    float f[4];

    printf("______________________________\n");
    printf("pos_ref = [ %f, %f, %f ]\n", QR_pos_ref[0], QR_pos_ref[1], QR_pos_ref[2]);
    printf("pos = [ %f, %f, %f ]\n", state.pos[0], state.pos[1], state.pos[2]);

    x_errorh = x_error;
    x_error = QR_pos_ref[0] - QR_pos[0];
    x_errord = (x_error - x_errorh)/dt;
    x_acc = kp_xy*x_error + kd_xy*x_errord;
    x_acc = limit(x_acc,-8.0,8.0);

    y_errorh = y_error;
    y_error = QR_pos_ref[1] - QR_pos[1];
    y_errord = (y_error - y_errorh)/dt;
    y_acc = kp_xy*y_error + kd_xy*y_errord;
    y_acc = limit(y_acc,-8.0,8.0);

    z_errorh = z_error;
    z_error = QR_pos_ref[2] - QR_pos[2];
    z_errord = (z_error - z_errorh)/dt;
    z_acc = kp_z*z_error + kd_z*z_errord;
    z_acc = limit(z_acc,-8.0,8.0);

    printf("pos_error:[ %lf, %lf, %lf]\n",x_error,y_error,z_error);
    printf("pos_acc:[ %lf, %lf, %lf]\n",x_acc,y_acc,z_acc);

    att_ref[2] = atan(-x_acc/(z_acc+g));
    att_ref[1] = atan((y_acc*cos(att_ref[2]))/(z_acc+g));

    if(att_ref[1])
    {
        u1 = (y_acc)/sin(att_ref[1]);
        u1 = limit(u1,-20.0,25.0);
    }
    else
    {
        u1 = (z_acc+g)/(cos(att_ref[2])*cos(att_ref[1]));
        u1 = limit(u1,-20.0,25.0);
    }

    phi_errorh = phi_error;
    phi_error = att_ref[1] - QR_att[1];
    phi_errord = (phi_error - phi_errorh)/dt;
    phi_acc = kp_phi_the*phi_error + kd_phi_the*phi_errord;
    phi_acc = limit(phi_acc,-4.0,4.0);

    theta_errorh = theta_error;
    theta_error = att_ref[2] - QR_att[2];
    theta_errord = (theta_error - theta_errorh)/dt;
    theta_acc = kp_phi_the*theta_error + kd_phi_the*theta_errord;
    theta_acc = limit(theta_acc,-4.0,4.0);

    psi_errorh = psi_error;
    psi_error = 0.0 - QR_att[0];
    psi_errord = (psi_error - psi_errorh)/dt;
    psi_acc = kp_psi*psi_error + kd_psi*psi_errord;
    psi_acc = limit(psi_acc,-4.0,4.0);

    u2 = phi_acc;
    u3 = theta_acc;
    u4 = psi_acc;

    printf("att_ref:[ %lf, %lf, %lf]\n",0.0,att_ref[1],att_ref[2]);
    printf("att:[ %lf, %lf, %lf]\n",QR_att[0],QR_att[1],QR_att[2]);
    printf("angle_acc:[ %lf, %lf, %lf]\n",phi_acc,theta_acc,psi_acc);

    //calculate equation
    //m*u1 = f1+f2+f3+f4
    //u2 = -f1+f3
    //u3 = -f4+f2
    //u4 = -(f1+f3)+f2+f4

    f[0] = (frame.mass*u1 + u4 + 2.0*u3)/4.0;
    f[1] = (frame.mass*u1 - u4 - 2.0*u2)/4.0;
    f[2] = (frame.mass*u1 + u4 - 2.0*u3)/4.0;
    f[3] = (frame.mass*u1 - u4 + 2.0*u2)/4.0;

    for (int i  = 0; i < 4; i++)
    {
        state.motor_rot_speed[i] = std::sqrt(f[i]/frame.k);
    }

//    printf("u1~4:[ %lf, %lf, %lf, %lf]\n",u1,u2,u3,u4);
//    printf("rot_speed:[ %lf, %lf, %lf, %lf]\n",state.motor_rot_speed[0],state.motor_rot_speed[1],state.motor_rot_speed[2],state.motor_rot_speed[3]);

//    state.motor_rot_speed[0] = 190.08;
//    state.motor_rot_speed[1] = 190.08;
//    state.motor_rot_speed[2] = 190.08;
//    state.motor_rot_speed[3] = 190.08;

    printf("u1~4:[ %lf, %lf, %lf, %lf]\n",u1,u2,u3,u4);
    printf("rot_speed:[ %lf, %lf, %lf, %lf]\n",state.motor_rot_speed[0],state.motor_rot_speed[1],state.motor_rot_speed[2],state.motor_rot_speed[3]);

    /* attitude control loop */ 

}

/* End of file quadrotor.cxx */
