/*
 * Models of RAOS
 *
 * Author: Roice (LUO Bing)
 * Date: 2016-02-23 create this file (RAOS)
 */
#include "model/qrmod.h"
#include "model/plume.h"

/* global parameters for visualization */
static qrstate_t qr_state;

void SimModel_init(void)
{
    qr_init(&qr_state);
    plume_init();
}

// get the pointer to the qr_state
qrstate_t* SimModel_get_qrstate(void)
{
    return &qr_state;
}
/* End of SimModel.cxx */
