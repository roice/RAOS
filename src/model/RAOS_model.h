#ifndef RAOS_MODEL_H
#define RAOS_MODEL_H

#include "common/RAOS_types.h"

// update frequency (Hz)
#define RAOS_MODEL_UPDATE_FREQ  100

/*
 * Functions to create/destroy models
 */
bool RAOS_model_create(RAOS_model_type_e);
bool RAOS_model_destroy(RAOS_model_t*);
bool RAOS_model_update(RAOS_model_t*);
int RAOS_model_encode_info2string(RAOS_model_t*, char*);
bool RAOS_model_decode_string2cmd(char*, int);


/*
 * Functions to create/destroy/manage model thread
 */
bool RAOS_model_thread_create(void);
bool RAOS_model_thread_destroy(void);
bool RAOS_model_thread_is_running(void);
RAOS_model_thread_state_t *RAOS_model_thread_get_state(void);
void RAOS_model_thread_pause(void);
void RAOS_model_thread_resume(void);
void RAOS_model_thread_lock_data(void);
void RAOS_model_thread_unlock_data(void);
bool RAOS_model_thread_init_comm_with_strategy_thread(void);
bool RAOS_model_thread_close_comm_with_strategy_thread(void);
bool RAOS_model_thread_receive_cmd_from_strategy_thread(void);
bool RAOS_model_thread_send_info_to_strategy_thread(void);

#endif
