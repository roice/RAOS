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
} QRframe_t;

/* calculate four rotors' pos according to quadrotor's pos and att */
void QRCalculateAllRotorPos(const float* pos, const float* att, float strut, float* rpos1, float* rpos2, float* rpos3, float* rpos4);

class QRdynamic {
    public:
        QRdynamic(float* pos_ref, float* pos, float* att, float delta_t); // constructor
        void update(void);
    private:
        float dt;
        float *QR_pos_ref;
        float *QR_pos;
        float *QR_att;
};

#endif /* End of file quadrotor.h */
