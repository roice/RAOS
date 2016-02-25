/*
 * Configuration file of RAOS
 *
 * This file contains declarations of the configuration data & methods
 * of RAOS.
 * The implementations of the classes, functions and data are written in 
 * file SimConfig.cxx.
 *
 * Author: Roice (LUO Bing)
 * Date: 2016-02-25 create this file
 */

typedef struct {
    /* width, length and height */
    float w;
    float l;
    float h;
}SimConfig_Arena_t;

typedef struct {
    /* source position */
    float x;
    float y;
    float z;
    /*  */
}SimConfig_Source_t;

typedef struct {
    /* init pos */
    float init_x;
    float init_y;
    float init_z;
}SimConfig_Robot_t;

/* configuration struct */
typedef struct {
    /* Arena */
    SimConfig_Arena_t arena;
    SimConfig_Source_t source;
    SimConfig_Robot_t robot;
} SimConfig_t;

void SimConfig_restore(void);
void SimConfig_save(void);
void SimConfig_init(void);
// get pointer of configuration data
SimConfig_t* SimConfig_get_configs(void);

/* End of SimConfig.h */
