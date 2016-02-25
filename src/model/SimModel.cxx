/*
 * Models of RAOS
 *
 * Author: Roice (LUO Bing)
 * Date: 2016-02-23 create this file (RAOS)
 */

#include "qrmod.h"

/* global parameters for visualization */
qrstate_t global_qrstate;

void SimModel_init(void)
{
    qr_init(&global_qrstate);
}
/* End of SimModel.cxx */
