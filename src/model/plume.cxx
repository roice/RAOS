/*
 * plume model
 *
 * Author: Roice (LUO Bing)
 * Date: 2016-02-26 create this file (RAOS)
 */
#include <vector>
#include <stdio.h>
#include <stdlib.h> // drand48 and srand48 on Linux
#include <time.h> // for random seed
#include "model/plume.h"
#include "SimConfig.h"
#include "ziggurat.h" // for normal distribution number

/*============== Filament Model ============*/
#if defined(USE_FILAMENT_MODEL)



#if defined(WIN32) || defined(__EMX__)
#  define drand48() (((float) rand())/((float) RAND_MAX))
#  define srand48(x) (srand((x)))
#elif defined __APPLE__
#  define drand48() (((float) rand())/((float) RAND_MAX))
#  define srand48(x) (srand((x)))
#endif

class FilaModel
{
    public:
        std::vector<FilaState_t> state; // state of fila, a list

        /* parameters for ziggurat method */
        float fn[128];
        unsigned int kn[128];
        float wn[128];
        unsigned int seed;

        void init(void) // fila initialization
        {
            // init delta time
            dt = 0.01; // sec
            // init source pos params
            SimConfig_t *config = SimConfig_get_configs();
            source_pos[0] = config->source.x;
            source_pos[1] = config->source.y;
            source_pos[2] = config->source.z;
            /* init fila state */
            state.reserve(MAX_NUM_PUFFS+10); // make room for MAX_NUM_PUFFS fila
            /* release first odor pack at source */
            fila_release();
            /* clear number of fila need to release */
            fila_num_need_release = 0.0;
            /* seed the random generator */
            srand48(time(NULL));
            /* setup ziggurat method to generate normal distribution numbers */
            r4_nor_setup ( kn, fn, wn );
            seed = time(NULL);
        }
        void update(void) // update fila
        {
            float wind_x, wind_y, wind_z;
            float vm_x, vm_y, vm_z;
        /* Step 1: update positions of fila */
            for (int i = 0; i < state.size(); i++) // for each fila
            {
                // calculate wind
                wind_x = 1;
                wind_y = 0;
                wind_z = 0;
                // calculate centerline relative dispersion
                /*
                vm_x = (drand48() - 0.5);
                vm_y = (drand48() - 0.5);
                vm_z = (drand48() - 0.5);
                */
                vm_x = 0.2*r4_nor ( seed, kn, fn, wn );
                vm_y = 0.2*r4_nor ( seed, kn, fn, wn );
                vm_z = 0.2*r4_nor ( seed, kn, fn, wn );
                // calculate pos increment
                state.at(i).pos[0] += (wind_x+vm_x + state.at(i).vel[0]) * dt;
                state.at(i).pos[1] += (wind_y+vm_y + state.at(i).vel[1]) * dt;
                state.at(i).pos[2] += (wind_z+vm_z + state.at(i).vel[2]) * dt;
            }
        /* Step 2: update sizes of fila */
            for (int i = 0; i < state.size(); i++) // for each fila
            {
                state.at(i).r += 0.0001;
            }
        /* Step 3: fila maintainance */
            fila_release();
            if (state.size() > MAX_NUM_PUFFS)
                state.erase(state.begin());                
        }
    private: 
        float dt; // delta time
        float source_pos[3]; // source pos
        float fila_num_need_release; // "buffer" fila
        void fila_release(void) // release a filament (puff)
        {
            FilaState_t new_fila;
            new_fila.pos[0] = source_pos[0];
            new_fila.pos[1] = source_pos[1];
            new_fila.pos[2] = source_pos[2];
            new_fila.r = 0.001;
            state.push_back(new_fila);
        }
};
#endif

/*==============   Plume Model  ============*/
#if defined(USE_FILAMENT_MODEL)
FilaModel *fila;
#endif

void plume_init(void)
{
#if defined(USE_FILAMENT_MODEL)
    fila = new FilaModel();
    fila->init();
#endif
}

void plume_update(void)
{
#if defined(USE_FILAMENT_MODEL)
    fila->update();
#endif
}

#if defined(USE_FILAMENT_MODEL)
std::vector<FilaState_t>* plume_get_fila_state(void)
{
    return &fila->state;
}
#endif

/* End of plume.cxx */
