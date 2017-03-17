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
#include "model/quadrotor.h"

#define PI 3.14159265358979323846
static double RAD2DEG = 180.0 / PI;

//================================Dynamic Model Part==========================================
QDynamicModel::QDynamicModel(void)
{
    //Parameter assignment
    Pa.m = 1.68;
    Pa.l = 0.0;
    Pa.c = 0.0;
    Pa.g = 9.81;
    Pa.J1 = 0.0;
    Pa.J2 = 0.0;
    Pa.J3 = 0.0;
    Pa.K1 = 0.0;
    Pa.K2 = 0.0;
    Pa.K3 = 0.0;
    Pa.K4 = 0.0;
    Pa.K5 = 0.0;
    Pa.K6 = 0.0;
    Pa.dt = 18.0*20.0/360.0/50.0;
    Pa.maxdegree = 2.61799; //150 degree to rad
    Pa.minidegree = -2.61799;

    kpid.kpxy = 1.4;
    kpid.kpxy = 0.8;
    kpid.kixy = 0.0;
    kpid.kpz = 2.7;
    kpid.kiz = 0.0;
    kpid.kdz = 1.5;
    kpid.kppq = 4;
    kpid.kdpq = 2;
    kpid.th_hover = 0.59;
    kpid.maxtilt = 0.34;
    kpid.kpyaw = 6.0;
    kpid.kdyaw = 0.0;
    kpid.maxyawrate = 4.4;
    kpid.maxxyvel = 3.0;
    kpid.mass =Pa.m;
    kpid.g = Pa.g;
    kpid.gn = kpid.mass * kpid.g;
}

float QDynamicModel::limit(float x,float x1,float x2)
{
    if(x < x1)
        return x1;
    else if(x > x2)
        return x2;
    else
        return x;
}

/* Input: error
 * Output: rotation speed of four motors
 */
void QDynamicModel::PIDControler(void)
{ 
//    float desax,a1,a;
//    float desay,b1,b;
//    float desth,
    float a,b,c;

    st.exH = st.ex;
    st.ex = st.SetPosition[0] - st.OutPosition[0];
    st.exd = (st.ex -st.exH)/Pa.dt;
    st.xacc = kpid.kpxy * st.ex + kpid.kdxy * st.exd;
    a = st.xacc*kpid.mass;
    a = limit(a,-4,4);

    st.eyH = st.ey;
    st.ey =st.SetPosition[1] - st.OutPosition[1];
    st.eyd = (st.ey -st.eyH)/Pa.dt;
    st.yacc = kpid.kpxy * st.ey + kpid.kdxy * st.exd;
    b = st.yacc * kpid.mass;
    b = limit(b,-4,4);

    //printf("b:%lf,%lf,%lf \n", st.SetPosition[1],st.OutPosition[1], st.ey );

    st.ezH = st.ez;
    st.ez = st.SetPosition[2] - st.OutPosition[2];
    st.exd = (st.ez - st.ezH)/Pa.dt;
    st.zacc = kpid.kpz * st.ez + kpid.kdz * st.ezd;
    c = st.zacc * kpid.mass;

    //printf("c:%lf,%lf,%lf \n", st.SetPosition[2],st.OutPosition[2], st.ez );


    //the destanation angle
    st.SetAttitude[2] = atan(a/(c+kpid.gn));
    st.SetAttitude[1] = atan((-b*cos(st.SetAttitude[2]))/(c+kpid.gn));
    if(st.SetAttitude[1])
    {
        RotSta.u1 = (-b)/sin(st.SetAttitude[1]);
        RotSta.u1 = limit(RotSta.u1,0,10);
    }
    else
    {
        RotSta.u1 = (c+kpid.gn)/cos(st.SetAttitude[2]);
        RotSta.u1 = limit(RotSta.u1,0,10);
    }

    st.erollh = st.eroll;
    st.eroll = st.SetAttitude[2] - st.OutAttitude[2];
    st.erolld = (st.eroll - st.erollh)/Pa.dt;
    st.rollacc = kpid.kppq * st.eroll + kpid.kdpq * st.erolld;
    st.rollacc = limit(st.rollacc,-8,8);

    st.epitchh = st.epitch;
    st.epitch = st.SetAttitude[1] - st.OutAttitude[1];
    st.epitchd = (st.epitch - st.epitch)/Pa.dt;
    st.pitchacc = kpid.kppq * st.epitch + kpid.kdpq * st.epitchd;
    st.pitchacc = limit(st.pitchacc,-8,8);

    st.eyawh = st.eyaw;
    st.eyaw = 0 - st.OutAttitude[0];
    st.eyawd = (st.eyaw - st.eyawh)/Pa.dt;
    st.yawacc = kpid.kpyaw * st.eyaw + kpid.kdyaw *st.eyawd;

    //add some noise
    RotSta.u1 = RotSta.u1;
    RotSta.u2 = st.pitchacc;
    RotSta.u3 = st.rollacc;
    RotSta.u4 = st.yawacc;

    //printf("att:%lf,%lf,%lf \n",  RotSta.u2 , RotSta.u3,  RotSta.u4 );
    //printf("pos:%lf,%lf,%lf \n", a ,b, c );

    //printf("u:%lf,%lf,%lf,%lf \n", RotSta.u1 ,RotSta.u2, RotSta.u3,RotSta.u4 );

    //transform u1\u2\u3\u4 to f1\f2\f3\f4 and w1\w2\w3\w4
//    u1 = (RotSta.f1 + RotSta.f2 + RotSta.f3 + RotSta.f4) / Pa.m;
//    u2 = -(RotSta.f1 +RotSta.f4) + (RotSta.f2 + RotSta.f3);
//    u3 = -(RotSta.f1 +RotSta.f2) + (RotSta.f3 + RotSta.f3);
//    u4 = -(RotSta.f1 +RotSta.f3) + (RotSta.f2 + RotSta.f4);

}

//From f1,f2,f3,f4 to acc
void QDynamicModel::DynamicModel(void)
{
//    float u1,u2,u3,u4;
//    u1 = (RotSta.f1 + RotSta.f2 + RotSta.f3 + RotSta.f4) / Pa.m;
//    u2 = -(RotSta.f1 +RotSta.f4) + (RotSta.f2 + RotSta.f3);
//    u3 = -(RotSta.f1 +RotSta.f2) + (RotSta.f3 + RotSta.f3);
//    u4 = -(RotSta.f1 +RotSta.f3) + (RotSta.f2 + RotSta.f4);

    //  yaw=psi   pitch=phi roll=theta
    static float awpos[3] = {0.,0.,0.};
    static float abpos[3] = {0.,0.,0.};
    static float abatt[3] = {0.,0.,0.};
    static float vbpos[3] = {0.,0.,0.};
    static float vwpos[3] = {0.,0.,0.};
    static float R_w2b[9],R_b2w[9];
    float sin_yaw = sin(st.OutAttitude[0]);
    float cos_yaw = cos(st.OutAttitude[0]);
    float sin_pitch = sin (st.OutAttitude[1]);
    float cos_pitch = cos (st.OutAttitude[1]);
    float sin_roll = sin (st.OutAttitude[2]);
    float cos_roll = cos (st.OutAttitude[2]);
    float tan_roll = sin_roll/cos_roll;

    R_w2b[0] = cos_roll*cos_yaw;
    R_w2b[1] = cos_roll*sin_yaw;
    R_w2b[2] = -sin_roll;
    R_w2b[3] = sin_pitch*sin_roll*cos_yaw - cos_pitch*sin_yaw;
    R_w2b[4] = sin_pitch*sin_roll*sin_yaw + cos_pitch*cos_yaw;
    R_w2b[5] = sin_pitch*cos_roll;
    R_w2b[6] = cos_pitch*sin_roll*cos_yaw + sin_pitch*sin_yaw;
    R_w2b[7] = cos_pitch*sin_roll*sin_yaw - sin_pitch*cos_yaw;
    R_w2b[8] = cos_pitch*cos_roll;

    R_b2w[0] = R_w2b[0];
    R_b2w[1] = R_w2b[3];
    R_b2w[2] = R_w2b[6];
    R_b2w[3] = R_w2b[1];
    R_b2w[4] = R_w2b[4];
    R_b2w[5] = R_w2b[7];
    R_b2w[6] = R_w2b[2];
    R_b2w[7] = R_w2b[5];
    R_b2w[8] = R_w2b[8];


    st.OutPosition[0] += (st.xvel+st.xvelh)*Pa.dt/2.0;
    st.OutPosition[1] += (st.yvel+st.yvelh)*Pa.dt/2.0;
    st.OutPosition[2] += (st.zvel+st.zvelh)*Pa.dt/2.0;
    st.OutAttitude[2] += (st.rollvel+st.rollvelh)*Pa.dt/2.0;
    st.OutAttitude[1] += (st.pitchvel+st.pitchvelh)*Pa.dt/2.0;
    st.OutAttitude[0] += (st.yawvel+st.yawvelh)*Pa.dt/2.0;

    //printf("vel:%lf,%lf,%lf \n", st.xvel ,st.xvel, st.xvel );
    //printf("OutPosition:%lf,%lf,%lf \n", st.OutPosition[0] ,st.OutPosition[1], st.OutPosition[2] );

    st.u += abpos[0]*Pa.dt;
    st.v += abpos[1]*Pa.dt;
    st.w += abpos[2]*Pa.dt;
    st.p += abatt[1]*Pa.dt;
    st.q += abatt[2]*Pa.dt;
    st.r += abatt[3]*Pa.dt;

    //printf("uvw:%lf,%lf,%lf \n", st.u ,st.v, st.w);

    vbpos[0] = st.u;
    vbpos[1] = st.v;
    vbpos[2] = st.w;
    cblas_sgemv(CblasRowMajor, CblasNoTrans, 3, 3, 1.0, R_b2w, 3, vbpos, 1, 0.0, abpos, 1);
    st.xvelh = st.xvel;
    st.yvelh = st.yvel;
    st.zvelh = st.zvel;
    st.xvel = abpos[0];
    st.yvel = abpos[1];
    st.zvel = abpos[2];

    st.pitchvelh = st.pitchvel;
    st.rollvelh = st.rollvel;
    st.yawvelh = st.yawvel;
    st.pitchvel = st.p + st.q*sin_pitch*tan_roll + st.r*cos_pitch*tan_roll;
    st.rollvel = st.q*cos_pitch - st.r*sin_pitch;
    st.yawvel = st.q*sin_pitch/cos_roll + st.r*cos_pitch/cos_roll;


    awpos[0] = (cos_pitch*sin_roll*cos_yaw+sin_yaw*sin_pitch)*RotSta.u1/Pa.m;
    awpos[1] = (cos_pitch*sin_roll*sin_yaw-cos_yaw*sin_pitch)*RotSta.u1/Pa.m;
    awpos[2] = -(cos_pitch*cos_roll)*RotSta.u1/Pa.m + Pa.g;
    cblas_sgemv(CblasRowMajor, CblasNoTrans, 3, 3, 1.0, R_w2b, 3, awpos, 1, 0.0, abpos, 1);
    //add wind

    //printf("awpos:%lf,%lf,%lf \n", awpos[0] ,awpos[1], awpos[2] );
    //printf("abpos:%lf,%lf,%lf \n", abpos[0] ,abpos[1], abpos[2] );

    abatt[1] = RotSta.u2 - sin_roll*RotSta.u4 - abatt[0]*abatt[2];
    if((st.p > Pa.maxdegree && (abatt[1] > 0))||(st.p < Pa.minidegree && (abatt[1] < 0 )))
    {abatt[1] = 0;}

    abatt[2] = cos_pitch*RotSta.u3 + cos_roll*sin_pitch*RotSta.u4 + abatt[0]*abatt[1];
    if((st.q > Pa.maxdegree && (abatt[2] > 0))|| (st.q < Pa.minidegree && (abatt[2] < 0 )))
    {abatt[2] = 0;}

    abatt[0] = -sin_pitch*RotSta.u3 + cos_roll*cos_pitch*RotSta.u4;

//    st.xacc = -Pa.K1*st.xvel/Pa.m + (cos_pitch*sin_roll*cos_yaw + sin_pitch*sin_yaw)*u1;
//    st.yacc = -Pa.K2*st.yvel/Pa.m + (cos_pitch*sin_roll*sin_yaw - sin_pitch*cos_yaw)*u1;
//    st.zacc = -Pa.K3*st.zvel/Pa.m - Pa.g + cos_pitch*cos_roll*u1;
//    st.rollacc = -Pa.K4*Pa.l*st.rollvel/Pa.J1 + Pa.l*u2/Pa.J1;
//    st.pitchacc = -Pa.K5*Pa.l*st.pitchacc/Pa.J2 + Pa.l*u3/Pa.J2;
//    st.yawacc = -Pa.K6*st.yawacc/Pa.J3 + Pa.c*u4/Pa.J3;

}


void QDynamicModel::MoveQState(void)
{
    st.xvelh = st.xvel;
    st.yvelh = st.yvel;
    st.zvelh = st.zvel;
    st.rollvelh = st.rollvel;
    st.pitchvelh =st.pitchvel;
    st.yawvelh = st.yawvel;

//    st.xacch = st.xacc;
//    st.yacch = st.yacc;
//    st.zacch = st.zacc;
//    st.rollacch = st.rollacc;
//    st.pitchacch =st.pitchacc;
//    st.yawacch = st.yawacc;

    //Trapezoidal integral to get velocity
//    st.xvel += (st.xacc+st.xacch)*Pa.dt/2.0;
//    st.yvel += (st.yacc+st.yacch)*Pa.dt/2.0;
//    st.zvel += (st.zacc+st.zacch)*Pa.dt/2.0;
//    st.rollvel += (st.rollacc+st.rollacch)*Pa.dt/2.0;
//    st.pitchvel += (st.pitchacc+st.pitchacch)*Pa.dt/2.0;
//    st.yawvel += (st.yawacc+st.yawacch)*Pa.dt/2.0;

    //Trapezoidal integral to get position and angle
    st.OutPosition[0] += (st.xvel+st.xvelh)*Pa.dt/2.0;
    st.OutPosition[1] += (st.yvel+st.yvelh)*Pa.dt/2.0;
    st.OutPosition[2] += (st.zvel+st.zvelh)*Pa.dt/2.0;
    st.OutAttitude[2] += (st.rollvel+st.rollvelh)*Pa.dt/2.0;
    st.OutAttitude[1] += (st.pitchvel+st.pitchvelh)*Pa.dt/2.0;
    st.OutAttitude[0] += (st.yawvel+st.yawvelh)*Pa.dt/2.0;
}

void QDynamicModel::Dynamic(float* SetPosition,float* OutPosition,float* OutAttitude,float sim_dt)
{
    Pa.dt = sim_dt;

//    st.SetPosition[0] = SetPosition[0];
//    st.SetPosition[1] = SetPosition[1];
//    st.SetPosition[2] = SetPosition[2];
    st.SetPosition[0] = 0.0;
    st.SetPosition[1] = 0.0;
    st.SetPosition[2] = 3.0;

    st.OutPosition[0] = OutPosition[0];
    st.OutPosition[1] = OutPosition[1];
    st.OutPosition[2] = OutPosition[2];
    st.OutAttitude[0] = OutAttitude[0];
    st.OutAttitude[1] = OutAttitude[1];
    st.OutAttitude[2] = OutAttitude[2];

    PIDControler();
    DynamicModel();

    OutPosition[0] = st.OutPosition[0];
    OutPosition[1] = st.OutPosition[1];
    OutPosition[2] = st.OutPosition[2];
    OutAttitude[0] = st.OutAttitude[0];
    OutAttitude[1] = st.OutAttitude[1];
    OutAttitude[2] = st.OutAttitude[2];
}


//=============================Vector Transformation Part=====================================


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

void wake_rotate_vector(const float*vector,float* out,float* QuadCenterPos,float psi,float yaw, float pitch, float roll)
{
    //step1: get normal vector n
    float p[3] = { 0.0 , 0.0 , 1.0 };
    float n[3] = { 0.0 , 0.0 , 0.0 };
    rotate_vector(p ,n , yaw ,pitch ,roll);//no yaw

    //step2: get vector a when psi=0
    float a2[3] = {out[0] - QuadCenterPos[0], out[1] - QuadCenterPos[1], out[2] - QuadCenterPos[2]}; //a1的模＝0.45/2=0.225
    float a1[3] = {vector[0]/0.225*a2[0],vector[0]/0.225*a2[1], vector[0]/0.225*a2[2],};
//    printf("out:%lf,%lf,%lf \n", out[0] ,out[1], out[2] );
//    printf("a2:%lf,%lf,%lf \n", a2[0] ,a2[1], a2[2] );
//    printf("QuadCenterPos:%lf,%lf,%lf \n", QuadCenterPos[0] ,QuadCenterPos[1], QuadCenterPos[2] );

    //step3: rotate vector a around the normal vector n to obtain a'
    float a[3] = { 0.0 ,0.0 ,0.0};
    float cos_psi = cos(psi*PI/180.0);
    float sin_psi = sin(psi*PI/180.0);

    a[0] = (n[0]*n[0]*(1.0-cos_psi)+cos_psi)*a1[0]        + (n[1]*n[0]*(1.0-cos_psi)-n[2]*sin_psi)*a1[1]    +(n[0]*n[2]*(1.0-cos_psi)+n[1]*sin_psi)*a1[2];
    a[1] = (n[0]*n[1]*(1.0-cos_psi)+n[2]*sin_psi)*a1[0]   + (n[1]*n[1]*(1.0-cos_psi)+cos_psi)*a1[1]         +(n[1]*n[2]*(1.0-cos_psi)-n[0]*sin_psi)*a1[2];
    a[2] = (n[0]*n[2]*(1.0-cos_psi)-n[1]*sin_psi)*a1[0]   + (n[1]*n[2]*(1.0-cos_psi)+n[0]*sin_psi)*a1[1]    +(n[2]*n[2]*(1.0-cos_psi)+cos_psi)*a1[2];

    out[0] += a[0];
    out[1] += a[1];
    out[2] += a[2];
}

/* calculate four rotors' pos according to quadrotor's pos and attitude */
void QRCalculateAllRotorPos(const float* pos, const float* attitude, float strut, float* rpos1, float* rpos2, float* rpos3, float* rpos4) {
    // init rotor pos vector
    memcpy(rpos1, pos, 3*sizeof(float));
    memcpy(rpos2, pos, 3*sizeof(float));
    memcpy(rpos3, pos, 3*sizeof(float));
    memcpy(rpos4, pos, 3*sizeof(float));

   // calculate rotor pos
    float v[3] = {strut, 0.0, 0.0};
    float v1[3] = {strut, 0.0, 0.0};
    float v2[3] = {0.0, strut, 0.0};
    float v3[3] = {-strut, 0.0, 0.0};
    float v4[3] = {0.0, -strut, 0.0};

    //printf("pos:%lf,%lf,%lf \n", pos[0] ,pos[1], pos[2] );
    rotate_vector(v1, rpos1, RAD2DEG * attitude[0], RAD2DEG *attitude[1], RAD2DEG *attitude[2]);
    //printf("pos1:%lf,%lf,%lf \n", rpos1[0] ,rpos1[1], rpos1[2] );
    rotate_vector(v2, rpos2, RAD2DEG * attitude[0], RAD2DEG *attitude[1], RAD2DEG *attitude[2]);
    //printf("pos2:%lf,%lf,%lf \n", rpos2[0] ,rpos2[1], rpos2[2] );
    rotate_vector(v3, rpos3, RAD2DEG * attitude[0], RAD2DEG *attitude[1], RAD2DEG *attitude[2]);
    //printf("pos3:%lf,%lf,%lf \n", rpos3[0] ,rpos3[1], rpos3[2] );
    rotate_vector(v4, rpos4, RAD2DEG * attitude[0], RAD2DEG *attitude[1], RAD2DEG *attitude[2]);
    //printf("pos4:%lf,%lf,%lf \n", rpos4[0] ,rpos4[1], rpos4[2] );
}

/* End of file quadrotor.cxx */
