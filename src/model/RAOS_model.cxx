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
#include <time.h>
#include <cmath>
#include <vector>
/* thread */
#include <pthread.h>
/* RAOS */
#include "model/RAOS_model.h"
#include "model/model_wind_uniform.h"

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

    // loop interval
    struct timespec req, rem;
    req.tv_sec = 0;
    req.tv_nsec = 1000000; // 0.001 s

    /* initialize simulator stuff (wind, plume, robot, etc.) */
    RAOS_model_thread_state.dt = 0.001;
    RAOS_model_thread_state.time_passed = 0; // clear simulation time count
    RAOS_model_thread_unlock_data(); // clear data lock

    while (!*((bool*)exit))
    {
        if (!*((bool*)pause)) {//if not pause
            /* update models */
            RAOS_model_thread_lock_data();
            for (int i = 0; i < RAOS_model_list.size(); i++)
                RAOS_model_update(&RAOS_model_list.at(i));
            RAOS_model_thread_unlock_data();
            /* update model thread state */
            RAOS_model_thread_state.time_passed += RAOS_model_thread_state.dt;
        }

        nanosleep(&req, &rem);
    }

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
    // wind field
    RAOS_model_create(RAOS_MODEL_WIND_UNIFORM);
    // plume
    //RAOS_model_create(RAOS_MODEL_PLUME_FARRALL);
    // robot

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
        for (int i = 0; i < RAOS_model_list.size(); i++) {
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

bool RAOS_model_create(RAOS_model_type_e type)
{
    RAOS_model_t    new_model;
    new_model.type = type;

    switch (type)
    {
        case RAOS_MODEL_WIND_UNIFORM:
            new_model.ptr = new model_wind_uniform_c();
            if (!new_model.ptr)
                return false;
            break;
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
