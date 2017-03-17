/*
 *          Robot model
 *
 *
 * Author: Roice (LUO Bing)
 * Date: 2016-03-08 create this file (RAOS)
 */

#ifndef ROBOT_H
#define ROBOT_H

#include <vector>

#ifdef RAOS_FEATURE_WAKES
    #include "wake_rotor.h"
#endif
#include "quadrotor.h"

enum RobotType{helicopter, quadrotor};

enum FuncSwitch{on, off};

typedef struct {
    /* Robot type */
    enum RobotType type; // robot type
    void* frame; // robot frame
#ifdef RAOS_FEATURE_WAKES
    /* rotor wake switch */
    enum FuncSwitch wake; // indicating whether to calculate wake or not
#endif
}RobotConfig_t;

typedef struct {    
    float pos[3];	/* position coordinate (earth axis x), volatile */
    float vel[3];
    float attitude[3]; // yaw, pitch, roll
    int   leds;
    float gas_sensor; // reading of gas sensor
}RobotState_t;

class Robot {
    public:
        Robot(const char* robot_type_name); // constructor
        void init(void);
        void update(void);
        void destroy(void);

#ifdef RAOS_FEATURE_WAKES
        std::vector<RotorWake*> wakes; // pointer of array containing pointers of RotorWake instances describing wakes of rotors (if has)
#endif
        QDynamicModel dynamic;
        RobotState_t state; // robot state
        RobotConfig_t config; // robot configs
        std::vector<RobotState_t> record;
};

#endif
/* End of file robot.h */
