/*
 * Simulation Thread
 *
 * Author: Roice (LUO Bing)
 * Date: 2017-03-15 create this file
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <cmath>
/* thread */
#include <pthread.h>
/* RAOS */
#include "model/SimModel.h" // models
#include "SimRecord.h"

bool sim_is_running = false;
pthread_mutex_t sim_data_lock;
double sim_time_passed = 0;

static pthread_t sim_thread_handle;
static bool exit_sim_thread = true;

static void* sim_loop(void* exit)
{
    struct timespec req, rem;

    // loop interval
    req.tv_sec = 0;
    req.tv_nsec = 1000000; // 0.001 s

    /* initialize simulator stuff (quadrotor, plume, etc.) */
  	SimModel_init();
    sim_time_passed = 0;
    sim_is_running = true;
    pthread_mutex_unlock(&sim_data_lock);

    while (!*((bool*)exit))
    {
        // update models
        pthread_mutex_lock(&sim_data_lock);
        SimModel_update();
        pthread_mutex_unlock(&sim_data_lock);

        nanosleep(&req, &rem);
    }

    sim_is_running = false;
    /* Save data */
    SimSaveData();
    // delete events, free memory...
    SimModel_destroy();
}

bool sim_start(void)
{
    // initialize lock
    pthread_mutex_init(&sim_data_lock, NULL);
    pthread_mutex_lock(&sim_data_lock);

    /* create simulation loop */
    exit_sim_thread = false;
    if (pthread_create(&sim_thread_handle, NULL, &sim_loop, (void*)&exit_sim_thread) != 0)
        return false;

    return true;
}

void sim_stop(void)
{
    if(!exit_sim_thread) // to avoid close twice
    {
        // exit simulation thread
        exit_sim_thread = true;
        pthread_join(sim_thread_handle, NULL);
        pthread_mutex_destroy(&sim_data_lock);
        printf("Simulation thread terminated.\n");
    }
}

bool sim_is_running_or_not(void)
{
    return sim_is_running;
}

double sim_get_time_passed(void)
{
    return sim_time_passed;
}

pthread_mutex_t* sim_get_data_lock(void)
{
    return &sim_data_lock;
}
