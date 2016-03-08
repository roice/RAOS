/*
 * Models of RAOS
 *
 * This file is included by SimMain.cxx
 * The implementations are written in SimModel.cxx, which contains functions
 * in files qrmod.cxx plume_model.cxx wind_model.cxx
 *
 * Author: Roice (LUO Bing)
 * Date: 2016-02-23 create this file (RAOS)
 */
#ifndef SIMMODEL_H
#define SIMMODEL_H

#include "model/qrmod.h"
#include "model/wake_qr_cpu.h"

void SimModel_init(void);
qrstate_t* SimModel_get_qrstate(void);
QRWake* SimModel_get_qr_wake(void);
void SimModel_qr_wake_update(void);

#endif
/* End of SimModel.h */
