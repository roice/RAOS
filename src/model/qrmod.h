/*----------------------------------------------------------------------------
 *
 * qrmod -- simple quad rotor model
 *         Arjan van Gemund 
 *         Embedded Software Lab, TU Delft
 *
 * Date: 2016-02-23 Roice (LUO Bing) modified this file for RAOS project
 *----------------------------------------------------------------------------
 */

#ifndef QR_MOD_H
#define QR_MOD_H

typedef struct
{
    float size; // distance between two diagonal motors
    float prop_radius; // propeller radius
} qrframe_t; // mechanical frame (constant)

typedef struct {
    unsigned char enable_gravity;
    unsigned char verbose;
    unsigned char pause;
} qrcontrol_t;

/* QR state
 */
typedef struct {

  	double z_at_gnd;	/* position coordinate (earth axis z) */

	double t;	/* simulation time */

  	/* quad rotor
  	 */
  	double phi;	/* roll angle (Euler angle x) */
  	double theta;	/* pitch angle (Euler angle y) */
  	double psi;	/* yaw angle (Euler angle z) */
  	double x;	/* position coordinate (earth axis x) */
  	double y;	/* position coordinate (earth axis y) */
  	double z;	/* position coordinate (earth axis z) */
  	double p;	/* angular rotation speed phi (body axis x) */
  	double q;	/* angular rotation speed theta (body axis y) */
  	double r;	/* angular rotation speed psi (body axis z) */
  	double u;	/* airspeed (body axis x) */
  	double v;	/* airspeed (body axis y) */
  	double w;	/* airspeed (body axis z) */
  	double mx;
  	double my;

  	/* actuators 
  	 */
  	double a1;	/* rotor 1 control */
  	double a2;	/* rotor 2 control */
  	double a3;	/* rotor 3 control */
  	double a4;	/* rotor 4 control */

	int leds;	/* qr leds */
	double tleds;	/* last time blinked */

  	/* sensors 
  	 */
  	double sp;	/* gyro measrement of p */
  	double sq;	/* gyro measrement of q */
  	double sr;	/* gyro measrement of r */
  	double sx;	/* acceleration (body axis x) */
  	double sy;	/* acceleration (body axis y) */
  	double sz;	/* acceleration (body axis z) */

    qrcontrol_t sim_control;

    qrframe_t frame;

} qrstate_t;

void qr_init(qrstate_t *qrstate);
//extern void update_euler(qrstate_t *qrstate, double p, double q, double r, int use_body_angles);
//extern void qr_nextstate(qrstate_t *qrstate, double DT);

#endif /* QR_MOD_H */
