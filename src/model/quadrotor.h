/*----------------------------------------------------------------------------
 *
 * quadrotor -- simple quad rotor model
 *        
 *
 * Date: 2016-02-23 Roice (LUO Bing) modified qrmod.h for RAOS project
 *       2016-03-09 Roice modified this file to make it compatible with
 *                  robot.cxx and robot.h
 *----------------------------------------------------------------------------
 */

#ifndef QUADROTOR_H
#define QUADROTOR_H

typedef struct
{
    float size; // distance between two diagonal motors
    float prop_radius; // propeller radius
    float prop_chord; // chord of propellers
    int prop_blades; // number of blades of a propeller
    float mass;
    float I[9];
    float k, b, kd;
} QRframe_t;

/* calculate four rotors' pos according to quadrotor's pos and att */
void QRCalculateAllRotorPos(const float* pos, const float* att, float strut, float* rpos1, float* rpos2, float* rpos3, float* rpos4);

typedef struct {
    float pos[3]; // position, inertial frame
    float vel[3]; // velocity, inertial frame
    float eta[3]; // rotation, phi(roll) theta(pitch) psi(yaw)  body frame
    float eta_dot[3]; // rotation speed, \dot{\phi} \dot{\theta} \dot{\psi}, body frame
    float motor_rot_speed[4];
} QRstate_t;

class QRdynamic {
    public:
        QRdynamic(float* pos_ref, float* pos, float* att, float delta_t, const char*, const char*, QRframe_t*); // constructor
        void update(void);
        /* quadrotor attributes */
        QRframe_t frame;
    private:
        /* input/output of QRdynamic */
        float dt;
        float *QR_pos_ref; // reference position
        float *QR_pos; // actual position
        float *QR_att; // actual attitude
        /* quadrotor model, input = motor rotation speeds */
        void quadrotor_model(void);
        /* quadrotor controller, output = motor rotation speeds */
        void controller_pid(void);
        /* quadrotor states */
        QRstate_t state;
};

#endif /* End of file quadrotor.h */
