#ifndef RAOS_TYPES_H
#define RAOS_TYPES_H

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
    RAOS_MODEL_PLUME_FARRELL, // begin of plume types
    // custom plume model
    RAOS_MODEL_PLUME_CUSTOM,  // end of plume types
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

typedef struct {
    double  time_passed;
    float   speed;  // simulation speed
} RAOS_model_thread_state_t;

#endif
