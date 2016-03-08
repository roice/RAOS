/*
 * Models of RAOS
 *
 * Author: Roice (LUO Bing)
 * Date: 2016-02-23 create this file (RAOS)
 */
#include "model/qrmod.h"
#include "model/plume.h"
#include "model/wake_qr_cpu.h"
#include <stdio.h>

/* global parameters for visualization */
static qrstate_t qr_state;
static QRWake wake;

void SimModel_init(void)
{
    qr_init(&qr_state);

printf("wake.rotor_wake[0]->config.dpsi = %f\n", wake.rotor_wake[0]->config.dpsi);
fflush(stdout);

    wake.init(&qr_state);

    plume_init();
}

// get the pointer to the qr_state
qrstate_t* SimModel_get_qrstate(void)
{
    return &qr_state;
}

// get the pointer to instance RotorWake
QRWake* SimModel_get_qr_wake(void) {
    return &wake;
}

void SimModel_qr_wake_update(void) {
    wake.update(&qr_state);

    //printf("%f\n", wake.rotor_wake[0]->wake_state.at(0).pos[0]);
    //fflush(stdout);
}
/* End of SimModel.cxx */
