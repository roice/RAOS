/*
 * Wakes in the simulation environment
 *
 * Author: Roice (LUO Bing)
 * Date: 2016-03-08 create this file (RAOS)
 */

#ifndef WAKE_H
#define WAKE_H

void WakesInit(std::vector<Robot*>*);
void WakesUpdate(std::vector<Robot*>*, const char*); // update all of the wakes in the environment
void WakesFinish(void);

#endif

/* End of file wake.h */
