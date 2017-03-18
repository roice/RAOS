#ifndef SIM_THREAD_H
#define SIM_THREAD_H

#include <pthread.h>

bool sim_start(void);
bool sim_stop(void);
bool sim_is_running_or_not(void);
pthread_mutex_t* sim_get_data_lock(void);
bool* sim_get_pauss_control_addr(void);

#endif
