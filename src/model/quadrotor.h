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

/* rotate a vector to given euler angles */
void rotate_vector(const float*, float*, float, float, float);
void wake_rotate_vector(const float*vector,float* out,float* QuadCenterPos,float psi,float yaw, float pitch, float roll);

/* calculate four rotors' pos according to quadrotor's pos and attitude */
void QRCalculateAllRotorPos(const float* pos, const float* attitude, float strut, float* rpos1, float* rpos2, float* rpos3, float* rpos4);

//===========================Dynamic Model Part==============================
typedef struct
{
    float SetPosition[3];
    float SetAttitude[3];
    float OutPosition[3];
    float OutAttitude[3];

    float ex,ey,ez,eyaw,eroll,epitch;
    float exH,eyH,ezH,eyawh,erollh,epitchh;
    float exSS,eySS,ezSS,eyawSS,erollSS,epitchSS;
    float exd,eyd,ezd,eyawd,erolld,epitchd;

    float xacc,yacc,zacc,yawacc,pitchacc,rollacc;
    float xvel,yvel,zvel,yawvel,pitchvel,rollvel;
    float xvelh,yvelh,zvelh,yawvelh,pitchvelh,rollvelh;
    float u,v,w,p,q,r;
} StateValue;

typedef struct
{
    float kpxy,kixy,kdxy;
    float kpz,kiz,kdz;
    float kppq,kdpq;
    float kpyaw,kdyaw;

    float th_hover;//throttle hover offset
    float maxtilt;//max pitch/roll angle
    float maxyawrate;
    float maxxyvel;
    float mass;
    float g,gn;
} ParameterPID;

typedef struct
{
    float J1,J2,J3;//inertial moments of corresponding axes
    float K1,K2,K3,K4,K5,K6;//aerodynamic damping coefficients
    float g;//the acceleration of gravity
    float l;//the epicenter of the UAV and the rotor axes
    float c;//a constant force-to-moment factor
    float m;//the mass of the quadrotor
    float dt;//time

    float maxdegree; //150 degree to rad
    float minidegree;
} ModelParameter;

typedef struct
{
    float u1,u2,u3,u4;
    float f1,f2,f3,f4;
    float w1,w2,w3,w4;
} RotorState;

class QDynamicModel {
public:
    StateValue st;
    RotorState  RotSta;

    QDynamicModel(void);
    void Dynamic(float* SetPosition,float* OutPosition,float* OutAttitude,float sim_dt);//RotorVelocity, to dominate the speed of four motors

private:
    ModelParameter Pa;
    ParameterPID kpid;

    void PIDControler(void);
    void DynamicModel(void);
    void MoveQState(void);
    float limit(float x,float x1,float x2);

};

#endif /* End of file quadrotor.h */
