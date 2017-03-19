/*
 *          Robot model
 *
 * Author: Roice (LUO Bing)
 * Date: 2016-03-08 create this file (RAOS)
 */

#include <vector>
#include <stdlib.h>
#include <string.h> // memset
#include "model/robot.h"
#include "model/helicopter.h" // for HLframe_t
#include "model/quadrotor.h" // for QRframe_t and euler rotation functions

Robot::Robot(const char* robot_type, const char* robot_name, const char* controller_name, float delta_t)
{
    // save args
    dt = delta_t;
  
    /* =============== Create Robot ================== */
    /******* Helicopter *******/
    if (strcmp(robot_type, "helicopter") == 0) {
        config.type = helicopter;
#ifdef RAOS_FEATURE_WAKES
        config.wake = on; // calculate wake by default
#endif
        config.frame = (HLframe_t*)malloc(sizeof(HLframe_t));
        ((HLframe_t*)(config.frame))->main_prop_radius = 0.1; // meter
        ((HLframe_t*)(config.frame))->main_prop_blades = 2; // two-blade
        ((HLframe_t*)(config.frame))->main_prop_chord = 0.01; // chord
        
        memset(state.pos, 0, sizeof(state.pos));
        memset(state.att, 0, sizeof(state.att));
    }
    /******* QuadRotor *******/
    else if (strcmp(robot_type, "quadrotor") == 0) {
        config.type = quadrotor;
#ifdef RAOS_FEATURE_WAKES
        config.wake = on; // calculate wake by default
#endif
        config.frame = (QRframe_t*)malloc(sizeof(QRframe_t));
        ((QRframe_t*)(config.frame))->size = 0.45;
        ((QRframe_t*)(config.frame))->prop_radius = 0.15; // m
        ((QRframe_t*)(config.frame))->prop_chord = 0.01; // m
        ((QRframe_t*)(config.frame))->prop_blades = 2;
        ((QRframe_t*)(config.frame))->mass = 0.8; // kg
        ((QRframe_t*)(config.frame))->I[0] = 0.0081;
        ((QRframe_t*)(config.frame))->I[1] = 0.0;
        ((QRframe_t*)(config.frame))->I[2] = 0.0;
        ((QRframe_t*)(config.frame))->I[3] = 0.0;
        ((QRframe_t*)(config.frame))->I[4] = 0.0081;
        ((QRframe_t*)(config.frame))->I[5] = 0.0;
        ((QRframe_t*)(config.frame))->I[6] = 0.0;
        ((QRframe_t*)(config.frame))->I[7] = 0.0;
        ((QRframe_t*)(config.frame))->I[8] = 0.0142;
        ((QRframe_t*)(config.frame))->k = 0.0000542;
        ((QRframe_t*)(config.frame))->b = 0.0000011;
        ((QRframe_t*)(config.frame))->kd = 1.2;

        memset(state.pos, 0, sizeof(state.pos));
        memset(state.att, 0, sizeof(state.att));
        memset(ref_state.pos, 0, sizeof(ref_state.pos));
    }
    /******* Other *******/
    else {// cannot recognize robot type
        // Exit program
    }

    /* ================ Init Robot ================= */
    /******* Helicopter *******/
    if (config.type == helicopter) {
#ifdef RAOS_FEATURE_WAKES
        /* init rotor wake */
        if (config.wake == on) {
            RotorWake* new_wake = new RotorWake();
            new_wake->rotor_state.frame.radius
                = ((HLframe_t*)(config.frame))->main_prop_radius;
            new_wake->rotor_state.frame.n_blades
                = ((HLframe_t*)(config.frame))->main_prop_blades;
            new_wake->rotor_state.frame.chord
                = ((HLframe_t*)(config.frame))->main_prop_chord;
            new_wake->rotor_state.thrust = 0.2*9.8; // 0.1 kg
            memcpy(new_wake->rotor_state.pos, state.pos, sizeof(state.pos));
            memcpy(new_wake->rotor_state.att,
                state.att, sizeof(state.att));
            new_wake->init();
            wakes.push_back(new_wake);
        }
#endif
    }
    /******* Quadrotor *******/
    else if (config.type == quadrotor) {
#ifdef RAOS_FEATURE_WAKES
        /* init rotor wakes */
        if (config.wake == on) {
            for (int i = 0; i < 4; i++) // init four rotor wakes
            {
                RotorWake* new_wake = new RotorWake();
                new_wake->rotor_state.frame.radius
                    = ((QRframe_t*)(config.frame))->prop_radius;
                new_wake->rotor_state.frame.n_blades
                    = ((QRframe_t*)(config.frame))->prop_blades;
                new_wake->rotor_state.frame.chord
                    = ((QRframe_t*)(config.frame))->prop_chord;
                new_wake->rotor_state.thrust
                    = ((QRframe_t*)(config.frame))->mass*9.8/4.0; // N
                if (i%2 == 0)
                    new_wake->rotor_state.direction = WAKE_ROTOR_CLOCKWISE;
                else
                    new_wake->rotor_state.direction = WAKE_ROTOR_CCLOCKWISE;
                memcpy(new_wake->rotor_state.att,
                    state.att, sizeof(state.att)); 
                wakes.push_back(new_wake);
            }
            // init four rotor pos for wake computation
            QRCalculateAllRotorPos(state.pos, state.att, ((QRframe_t*)(config.frame))->size/2.0, wakes.at(0)->rotor_state.pos, wakes.at(1)->rotor_state.pos, wakes.at(2)->rotor_state.pos, wakes.at(3)->rotor_state.pos);
            for (int i = 0; i < 4; i++) // init four rotor wakes
                wakes.at(i)->init(); 
        }
#endif
        /* init quadrotor dynamic model */
        model = new QRdynamic(ref_state.pos, state.pos, state.att, dt, robot_name, controller_name, (QRframe_t*)(config.frame));
        memcpy(&(((QRdynamic*)model)->frame), (QRframe_t*)(config.frame), sizeof(QRframe_t));

        /* init leds */
        state.leds = 1;
    }
    /******* Other *******/
    else {
        // Exit program
    }
}

void Robot::update(void) {
    /* Save record */
    record.push_back(state);

    /******* Helicopter *******/
    if (config.type == helicopter) {
#ifdef RAOS_FEATURE_WAKES
        /* syncronize rotor att and pos (for wake computation) with robot */
        memcpy(wakes.at(0)->rotor_state.pos, state.pos, sizeof(state.pos));
        memcpy(wakes.at(0)->rotor_state.att,
            state.att, sizeof(state.att));
#endif
    }
    /******* Quadrotor *******/
    else if (config.type == quadrotor) {
#ifdef RAOS_FEATURE_WAKES
        /* syncronize rotors' att and pos (for wake computation) with robot */
        for (int i = 0; i < 4; i++) // init four rotor wakes
            memcpy(wakes.at(i)->rotor_state.att,
                state.att, sizeof(state.att)); 
        QRCalculateAllRotorPos(state.pos, state.att,
            ((QRframe_t*)(config.frame))->size/2.0,
            wakes.at(0)->rotor_state.pos,
            wakes.at(1)->rotor_state.pos,
            wakes.at(2)->rotor_state.pos,
            wakes.at(3)->rotor_state.pos);
#endif
        /* update quadrotor dynamic model */
        ((QRdynamic*) model)->update();
    }
    /******* Other *******/
    else {
        // Exit program
    } 
}

void Robot::destroy(void) {
#ifdef RAOS_FEATURE_WAKES
    if (wakes.size()) {
        for (int i = 0; i < wakes.size(); i++) {
            wakes.at(i)->destroy();
            delete wakes.at(i);
        }
        wakes.clear();
        std::vector<RotorWake*>().swap(wakes);
    }
#endif
    if (config.type == quadrotor) {
        delete ((QRdynamic*) model);
    }
    record.clear();
    std::vector<RobotState_t>().swap(record);
}



/* End of file robot.cxx */
