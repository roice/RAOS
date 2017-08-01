#ifndef RAOS_MODEL_H
#define RAOS_MODEL_H

// update frequency (Hz)
#define RAOS_MODEL_UPDATE_FREQ  100

/*
 * RAOS model types
 *
 * A model has its unique type name
 */
typedef enum {
    // uniform wind field model
    //  the wind vectors are the same everywhere
    RAOS_MODEL_WIND_UNIFORM = 0,
    // potential flow field model
    RAOS_MODEL_WIND_POTENTIAL,
    // Farrell plume model
    RAOS_MODEL_PLUME_FARRELL,
    // pioneer robot model
    RAOS_MODEL_ROBOT_PIONEER, // begin of robot types
    // microbee robot model
    RAOS_MODEL_ROBOT_MICROBEE,
    // qingluan robot model
    RAOS_MODEL_ROBOT_QINGLUAN,
    // typical wheeled mobile robot
    RAOS_MODEL_ROBOT_WHEELED,
    // typical quadrotor model
    RAOS_MODEL_ROBOT_QUADROTOR,
    // typical hexrotor model
    RAOS_MODEL_ROBOT_HEXROTOR,
    // typical helicopter model
    RAOS_MODEL_ROBOT_HELICOPTER,
    // typical flapped model
    RAOS_MODEL_ROBOT_ORNITHOPTER, // end of robot types
} RAOS_model_type_e;

/*
 * RAOS model struct
 *
 * This struct contains the type name and class pointer of a model
 * */
typedef struct {
    RAOS_model_type_e   type;
    void    *ptr; // storing class pointer
} RAOS_model_t;

/*
 * Functions to create/destroy models
 */
bool RAOS_model_create(RAOS_model_type_e);
bool RAOS_model_destroy(RAOS_model_t*);
bool RAOS_model_update(RAOS_model_t*);
int RAOS_model_encode_info2string(RAOS_model_t*, char*);
bool RAOS_model_decode_string2cmd(char*, int);

typedef struct {
    double  time_passed;
    float   speed;  // simulation speed
} RAOS_model_thread_state_t;

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
