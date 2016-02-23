/*
 * Models of RAOS
 *
 * Author: Roice (LUO Bing)
 * Date: 2016-02-23 create this file (RAOS)
 */

#include "qrmod.h"

/* define what is ground level z value for QR */
#define Z_AT_GND	(-0.3)

void SimModel_init(void)
{
    qr_init(&g_quad_state, Z_AT_GND);
}
