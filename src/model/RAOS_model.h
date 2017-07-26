#ifndef RAOS_MODEL_H
#define RAOS_MODEL_H

/*
 * RAOS model types
 *
 * A model has its unique type name
 */
typedef enum {
    // uniform wind field model
    //  the wind vectors are the same everywhere
    RAOS_MODEL_WIND_UNIFORM,
    // Farrell plume model
    RAOS_MODEL_PLUME_FARRELL,
    // pioneer robot model
    RAOS_MODEL_ROBOT_PIONEER,
    // microbee robot model
    RAOS_MODEL_ROBOT_MICROBEE,
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

typedef struct {
    float   dt;
    double  time_passed;
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

#endif
