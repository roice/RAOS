/*
 * RAOS model create/destroy & model thread create/destroy
 *
 * Author: Roice (LUO Bing)
 * Date: 2017-03-15 create this file
 *       2017-07-21 modify this file
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <cstdint>
#include <time.h>
#include <cmath>
#include <vector>
/* thread */
#include <pthread.h>
/* RAOS */
#include "RAOS_config.h"
#include "common/RAOS_serial_protocol.h"
#include "common/endian/little_endian.hpp"
#include "model/RAOS_model.h"
#include "model/model_wind_uniform.h"
#include "model/model_wind_potential.h"
#include "model/model_plume_farrell.h"
#include "model/model_robot_pioneer.h"

/* Models */
// list containing info of models created
std::vector<RAOS_model_t>   RAOS_model_list;

/* Model thread */
// thread handler
static pthread_t RAOS_model_thread_handler = 0;
// mutex to lock/unlock result data of models
pthread_mutex_t RAOS_models_data_lock;
// model thread state
RAOS_model_thread_state_t RAOS_model_thread_state;

/* Model thread arguments */
typedef struct {
    bool* exit_model_thread;
    bool* pause_model_thread;
} Model_Thread_Args_t;
Model_Thread_Args_t model_thread_args;
static bool exit_model_thread = true;
static bool pause_model_thread = false;

/* Functions of model thread */

/* Model thread loop
 *
 * In this loop, the models update during every cycle
 */
static void* model_thread_loop(void* args)
{
    bool* exit = ((Model_Thread_Args_t*)args)->exit_model_thread;
    bool* pause = ((Model_Thread_Args_t*)args)->pause_model_thread; 

    /* initialize simulator stuff (wind, plume, robot, etc.) */
    RAOS_model_thread_state.time_passed = 0; // clear simulation time count
    RAOS_model_thread_unlock_data(); // clear data lock

    // for counting time
    struct timespec update_begin, update_end;

    // for delay
    struct timespec req, rem;

    // RAOS configs
    RAOS_config_t *configs = RAOS_config_get_settings();

    // init communication with strategy thread
    RAOS_model_thread_init_comm_with_strategy_thread();

    while (!*((bool*)exit))
    {

        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &update_begin);

        if (!*((bool*)pause)) {//if not pause
            /* receive robot commands from strategy thread */
            RAOS_model_thread_receive_cmd_from_strategy_thread();
            /* update models */
            RAOS_model_thread_lock_data();
            for (int i = 0; i < (int)(RAOS_model_list.size()); i++)
                RAOS_model_update(&RAOS_model_list.at(i));
            RAOS_model_thread_unlock_data();
            /* update model thread state */
            RAOS_model_thread_state.time_passed += 1.0/RAOS_MODEL_UPDATE_FREQ;
            /* send sensor/robot info to strategy thread */
            RAOS_model_thread_send_info_to_strategy_thread();
        }

        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &update_end);

        // control simulation speed
        double elapse_time = (update_end.tv_sec + (double)update_end.tv_nsec/1e9) - (update_begin.tv_sec + (double)update_begin.tv_nsec/1e9);
        if (configs->common.speed == 0) // auto highest
        {
            RAOS_model_thread_state.speed = 1.0 / (elapse_time*RAOS_MODEL_UPDATE_FREQ);
        }
        else if (elapse_time < 1.0/(RAOS_MODEL_UPDATE_FREQ*configs->common.speed)) {
            req.tv_sec = 0;
            req.tv_nsec = (1.0/(RAOS_MODEL_UPDATE_FREQ*configs->common.speed) - elapse_time)*1e9;
            nanosleep(&req, &rem);
            RAOS_model_thread_state.speed = configs->common.speed;
        }
    }

    // close comm with strategy thread
    RAOS_model_thread_close_comm_with_strategy_thread();

    return NULL;
}

bool RAOS_model_thread_create(void)
{
    // initialize lock
    pthread_mutex_init(&RAOS_models_data_lock, NULL);
    RAOS_model_thread_lock_data();

    // thread arguments to control exit/pause of simulation
    model_thread_args.exit_model_thread = &exit_model_thread;
    model_thread_args.pause_model_thread = &pause_model_thread;

    /* create models */
    RAOS_config_t *configs = RAOS_config_get_settings();
    // wind field
    if (configs->wind.model_name == "Uniform") {
        RAOS_model_create(RAOS_MODEL_WIND_UNIFORM); // create model
        // init parameters
        ((model_wind_uniform_c*)(RAOS_model_list.back().ptr))->wind_vel[0] = configs->wind.wind_vel[0];
        ((model_wind_uniform_c*)(RAOS_model_list.back().ptr))->wind_vel[1] = configs->wind.wind_vel[1];
        ((model_wind_uniform_c*)(RAOS_model_list.back().ptr))->wind_vel[2] = configs->wind.wind_vel[2];
    }
    else if (configs->wind.model_name == "Potential") {
        RAOS_model_create(RAOS_MODEL_WIND_POTENTIAL); // create model
        // init parameters
        ((model_wind_potential_c*)(RAOS_model_list.back().ptr))->mean_wind_vel[0] = configs->wind.wind_vel[0];
        ((model_wind_potential_c*)(RAOS_model_list.back().ptr))->mean_wind_vel[1] = configs->wind.wind_vel[1];
        ((model_wind_potential_c*)(RAOS_model_list.back().ptr))->mean_wind_vel[2] = configs->wind.wind_vel[2];
    }
    else
    {}
    // plume
    for (int i = 0; i < configs->arena.num_sources; i++)
    {
        if (configs->plume[i].model_name == "Farrell") {
            RAOS_model_create(RAOS_MODEL_PLUME_FARRELL); // create model
            // init parameters
            ((model_plume_farrell_c*)(RAOS_model_list.back().ptr))->lambda = configs->plume[i].model_farrell_lambda;
        }
        else
        {}
    }
    // robot
    for (int i = 0; i < configs->arena.num_robots; i++)
    {
        if (configs->robot[i].model_name == "Pioneer") {
            RAOS_model_create(RAOS_MODEL_ROBOT_PIONEER); // create model
        }
        else
        {}
    }

    /* create simulation loop */
    exit_model_thread = false;
    pause_model_thread = false;
    if (pthread_create(&RAOS_model_thread_handler, NULL, &model_thread_loop, (void*)&(model_thread_args)) != 0)
        return false;

    printf("RAOS model thread created.\n");

    return true;
}

bool RAOS_model_thread_destroy(void)
{
    if(!exit_model_thread) // to avoid close twice
    {
        // exit simulation thread
        exit_model_thread = true;
        pthread_join(RAOS_model_thread_handler, NULL);
        pthread_mutex_destroy(&RAOS_models_data_lock);
        // destroy models
        for (int i = 0; i < (int)(RAOS_model_list.size()); i++) {
            RAOS_model_destroy(&RAOS_model_list.at(i));
            memset(&RAOS_model_list.at(i), 0, sizeof(RAOS_model_t)); 
        }
        RAOS_model_list.clear();
        // clear handler
        RAOS_model_thread_handler = 0;
        printf("RAOS model thread has been terminated, and models have been destroyed.\n");
        return true;
    }
    else
        return false;
}

bool RAOS_model_thread_is_running(void)
{
    if (RAOS_model_thread_handler)
        return true;
    else
        return false;
}

RAOS_model_thread_state_t *RAOS_model_thread_get_state(void)
{
    return &RAOS_model_thread_state;
}

void RAOS_model_thread_pause(void)
{
    pause_model_thread = true;
}

void RAOS_model_thread_resume(void)
{
    pause_model_thread = false;
}

void RAOS_model_thread_lock_data(void)
{
    pthread_mutex_lock(&RAOS_models_data_lock);
}

void RAOS_model_thread_unlock_data(void)
{
    pthread_mutex_unlock(&RAOS_models_data_lock);
}

/* Functions of models */

/*
 * Count number of robots in the model list
 *
 * Output:  amount of robots in the model list
 */
int RAOS_model_list_amount_of_robots(void)
{
    int count = 0;

    for (int i = 0; i < (int)(RAOS_model_list.size()); i++) {
        if (RAOS_model_list.at(i).type >= RAOS_MODEL_ROBOT_PIONEER and RAOS_model_list.at(i).type <= RAOS_MODEL_ROBOT_ORNITHOPTER)
            count ++;
    }
    return count;
}

/*
 * find the robot model with the type and ID in the model list
 *
 * Input:   robot type and robot ID
 * Output:  position(order) of model struct in the model list
 *          -1: not found
 *          0~: position(order)
 */
int RAOS_model_list_find_robot_by_type_and_id(RAOS_model_type_e type, int id)
{
    int result = -1;

    for (int i = 0; i < (int)(RAOS_model_list.size()); i++) {
        if (RAOS_model_list.at(i).type == type) {
            switch (type) {
                case RAOS_MODEL_ROBOT_PIONEER:
                    if (((model_robot_pioneer_c*)(RAOS_model_list.at(i).ptr))->id == id)
                        result = i;
                    break;
                default:
                    break;
            }
        }
    }

    return result;
}

bool RAOS_model_create(RAOS_model_type_e type)
{
    RAOS_model_t    new_model;
    new_model.type = type;

    switch (type) {
        case RAOS_MODEL_WIND_UNIFORM: 
        {
            new_model.ptr = new model_wind_uniform_c();
            if (!new_model.ptr)
                return false;
            break;
        }
        case RAOS_MODEL_ROBOT_PIONEER:
        {
            new_model.ptr = new model_robot_pioneer_c();
            if (!new_model.ptr)
                return false;
            ((model_robot_pioneer_c*)(new_model.ptr))->type = RAOS_MODEL_ROBOT_PIONEER;
            ((model_robot_pioneer_c*)(new_model.ptr))->id = RAOS_model_list_amount_of_robots();
            RAOS_config_t *configs = RAOS_config_get_settings();
            memcpy(((model_robot_pioneer_c*)(new_model.ptr))->pos, configs->robot[((model_robot_pioneer_c*)(new_model.ptr))->id].init_pos, 3*sizeof(float));
            memcpy(((model_robot_pioneer_c*)(new_model.ptr))->att, configs->robot[((model_robot_pioneer_c*)(new_model.ptr))->id].init_att, 3*sizeof(float));
            break;
        }
        default:
            return false;
    }

    RAOS_model_list.push_back(new_model);

    return true;
}

bool RAOS_model_destroy(RAOS_model_t *model)
{
    switch (model->type)
    {
        case RAOS_MODEL_WIND_UNIFORM:
            if (!model->ptr)
                return false;
            delete (model_wind_uniform_c*)(model->ptr);
            break;
        default:
            return false;
    }

    return true;
}

bool RAOS_model_update(RAOS_model_t *model)
{
    switch (model->type)
    {
        case RAOS_MODEL_WIND_UNIFORM:
            if (!model->ptr)
                return false;
            ((model_wind_uniform_c*)(model->ptr))->update();
            break;
        default:
            return false;
    }

    return true;
}

int RAOS_model_encode_info2string(RAOS_model_t *model, uint8_t *buf)
{
    switch (model->type)
    {
        case RAOS_MODEL_ROBOT_PIONEER:
            if (!model->ptr)
                return false;
            return ((model_robot_pioneer_c*)(model->ptr))->encode_info2string(buf);
            break;
        default:
            return 0;
    }
}

RAOS_SP_frame_t     rsp_frame = {0};

bool RAOS_model_decode_string2cmd(uint8_t *buf, int len)
{
    for (int i = 0; i < len; i++) {
        if (RAOS_serial_protocol_parser(buf[i], &rsp_frame)) {
            
printf("Received a frame\n");
            
            // received a frame
            switch (rsp_frame.cmd) {
                case RSP_CMD_ROBOT_GOTO: {
                    int model_list_idx = RAOS_model_list_find_robot_by_type_and_id((RAOS_model_type_e)rsp_frame.data[0], rsp_frame.data[1]);
                    if (model_list_idx < 0)
                        break;
                    model_robot_pioneer_c *robot = (model_robot_pioneer_c*)(RAOS_model_list.at(model_list_idx).ptr);
                    uint32_t temp;
                    // position
                    for (int i = 0; i < 3; i++) {
                        temp = endian::little_endian::get32(&rsp_frame.data[2+i*sizeof(uint32_t)]);
                        robot->pos_ref[i] = *((float*)(&temp));
                    }
                    // heading
                    temp = endian::little_endian::get32(&rsp_frame.data[14]);
                    robot->heading_ref = *((float*)(&temp));

printf("Received robot pioneer goto command, pos_ref = [%f, %f, %f], heading_ref = %f\n", robot->pos_ref[0], robot->pos_ref[1], robot->pos_ref[2], robot->heading_ref);

                    break;
                }
                default:
                    break;
            }
        }
    }
    return true;
}

/* Functions to communicate with strategy thread */

#include <nanomsg/nn.h>
#include <nanomsg/pair.h>
#include <nanomsg/ws.h>
int RAOS_model_strategy_threads_sock = -1;
bool RAOS_model_thread_init_comm_with_strategy_thread(void)
{
    RAOS_model_strategy_threads_sock = nn_socket (AF_SP, NN_PAIR);
    if (RAOS_model_strategy_threads_sock < 0) {
        printf("RAOS Error: Model thread failed to create socket communication with strategy thread. nn_socket in RAOS_model_thread_init_comm_with_strategy_thread function.\n");
        return false;
    }
    if (nn_bind (RAOS_model_strategy_threads_sock, "ws://127.0.0.1:5555") < 0) {
        printf("RAOS Error: Model thread failed to bind socket communication with strategy thread. nn_bind in RAOS_model_thread_init_comm_with_strategy_thread function.\n");
        return false;
    }
    return true;
}

bool RAOS_model_thread_close_comm_with_strategy_thread(void)
{
    if (RAOS_model_strategy_threads_sock >= 0) {
        nn_close(RAOS_model_strategy_threads_sock);
        RAOS_model_strategy_threads_sock = -1;
        return true;
    }
    else
        return false;
}

bool RAOS_model_thread_receive_cmd_from_strategy_thread(void)
{
    uint8_t *buf = NULL;
    int len = nn_recv (RAOS_model_strategy_threads_sock, &buf, NN_MSG, 0);
    if (len > 0)
    {
        RAOS_model_decode_string2cmd(buf, len);
        nn_freemsg (buf);
        return true;
    }
    else
        return false;
}

bool RAOS_model_thread_send_info_to_strategy_thread(void)
{
    uint8_t buf[4096]; int idx = 0;
    for (int i = 0; i < (int)(RAOS_model_list.size()); i++) {
        idx += RAOS_model_encode_info2string(&RAOS_model_list.at(i), buf+idx);
    }
    if (idx == nn_send(RAOS_model_strategy_threads_sock, buf, idx, 0))
        return true;
    else
        return false;
}
