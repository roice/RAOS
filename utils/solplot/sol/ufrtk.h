/*
 * ufrtk.h -- header file of User Functions related to RTK gps
 *
 * Author: Roice (LUO Bing)
 * Date:   2014-11-15 Create this file
 */

#ifndef UFRTK_H
#define UFRTK_H

#ifdef __cplusplus
extern "C" {
#endif

#include <rtklib.h>

/* definitions */
#define MAXNFILE 256            // max number of solution files

int ReadSolutionFiles(char**, int, solbuf_t*);

#ifdef __cplusplus
}
#endif

#endif
