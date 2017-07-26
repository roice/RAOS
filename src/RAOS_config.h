#ifndef RAOS_CONFIG_H
#define RAOS_CONFIG_H
#endif

#include <string>

#define RAOS_MAX_NUM_SOURCES    4
#define RAOS_MAX_NUM_ROBOTS     4

typedef struct {
    float dt;
    int speed;  // simulation speed, 0 for auto highest
}RAOS_config_common_t;

typedef struct {
    /* width, length and height */
    float w;
    float l;
    float h;
    // number of sources
    int num_sources;
}RAOS_config_arena_t;

typedef struct {
    std::string model_name;
    // uniform/potential wind field
    float wind_vel[3];
}RAOS_config_wind_t;

typedef struct {
    // source position
    float source_pos[3];
    // source release rate
    double source_mps; // molecules per second (10^18)
    // model type
    std::string model_name;
    // Farrell model parameters
    int model_farrell_pps;
    float model_farrell_lambda;
}RAOS_config_plume_t;

typedef struct {
    // robot type
    std::string type;
    // init pos
    float init_pos[3];
}RAOS_config_robot_t;

/* configuration struct */
typedef struct {
    RAOS_config_common_t common;
    RAOS_config_arena_t arena;
    RAOS_config_wind_t  wind;
    RAOS_config_plume_t plume[RAOS_MAX_NUM_SOURCES];
    RAOS_config_robot_t robot[RAOS_MAX_NUM_ROBOTS];
} RAOS_config_t;

void RAOS_config_restore(void);
void RAOS_config_save(void);
void RAOS_config_init(void);
// get pointer of configuration data
RAOS_config_t* RAOS_config_get_settings(void);

/* End of RAOS_config.h */
