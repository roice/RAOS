/*
 * plume model
 *
 * Author: Roice (LUO Bing)
 * Date: 2016-02-26 create this file (RAOS)
 */
#include <vector>
#include <time.h> // for random seed
#include "model/plume.h"
#include "SimConfig.h"
#include "ziggurat.h" // for normal distribution number
#include "SimModel.h"

/*============== Filament Model ============*/
#if defined(USE_FILAMENT_MODEL)
typedef struct {
    float source_pos[3]; // position of the source
    double pps; // parcels released per second
    double mpp; // molecules per parcel
    float lambda; // N(mu, lambda), vm
} PlumeConfig_t;
class FilaModel
{
    public:
        std::vector<FilaState_t> state; // state of fila, a list
        PlumeConfig_t config; // plume model settings

        /* parameters for ziggurat method */
        float fn[128];
        unsigned int kn[128];
        float wn[128];
        unsigned int seed;

        void init(void) // plume initialization
        {
            // init settings
            SimConfig_t* sim_config = SimConfig_get_configs();
            config.pps = sim_config->source.pps;
            config.mpp = sim_config->source.mpp;
            config.source_pos[0] = sim_config->source.x;
            config.source_pos[1] = sim_config->source.y;
            config.source_pos[2] = sim_config->source.z;
            config.lambda = sim_config->plume.lambda;

            /* init fila state */
            state.reserve(MAX_NUM_PUFFS+10); // make room for MAX_NUM_PUFFS fila
            /* release first odor pack at source */
            fila_release();
            
            /* clear number of fila need to release */
            fila_num_need_release = 0.0;

            /* setup ziggurat method to generate normal distribution numbers */
            r4_nor_setup ( kn, fn, wn );
            seed = time(NULL);
        }

        void update(SimState_t* sim_state) // update fila
        {
            float wind_x, wind_y, wind_z;
            float vm_x, vm_y, vm_z;

        /* Step 1: update positions of fila */
            for (int i = 0; i < state.size(); i++) // for each fila
            {
                // calculate wind
                wind_x = 0.5;
                wind_y = 0;
                wind_z = 0;
                // calculate centerline relative dispersion
                /*
                vm_x = (drand48() - 0.5);
                vm_y = (drand48() - 0.5);
                vm_z = (drand48() - 0.5);
                */
                vm_x = 0.3*r4_nor ( seed, kn, fn, wn );
                vm_y = 0.3*r4_nor ( seed, kn, fn, wn );
                vm_z = 0.3*r4_nor ( seed, kn, fn, wn );
                // calculate pos increment
                state.at(i).pos[0] += (wind_x+vm_x + state.at(i).vel[0]) * sim_state->dt;
                state.at(i).pos[1] += (wind_y+vm_y + state.at(i).vel[1]) * sim_state->dt;
                state.at(i).pos[2] += (wind_z+vm_z + state.at(i).vel[2]) * sim_state->dt;
                if (state.at(i).pos[2] < 0.0)
                    state.at(i).pos[2] = -state.at(i).pos[2];
            }
        /* Step 2: update sizes of fila */
            for (int i = 0; i < state.size(); i++) // for each fila
            {
                state.at(i).r += 0.0001;
                //state.at(i).r += 0.00001;
            }
        /* Step 3: fila maintainance */
            fila_num_need_release += config.pps*sim_state->dt;
            // remove fila which moved outside sim area
            int n = state.size(), i = 0;
            bool moved_outside = false;
            while (i != n) {
                for (int j = 0; j < 3; j++) {
                    if (state.at(i).pos[j] > 5.0 || state.at(i).pos[j] < -5.0)
                        moved_outside = true;
                }
                if (moved_outside == true) {
                    state.erase(state.begin()+i);
                    n--;
                    moved_outside = false;
                }
                else
                    i++;
            }
            // release & remove fila
            while (fila_num_need_release >= 1.0) {
                fila_release();
                fila_num_need_release -= 1.0;
                if (state.size() > MAX_NUM_PUFFS)
                    state.erase(state.begin());
            } 
        }
    private: 
        float fila_num_need_release; // "buffer" fila
        void fila_release(void) // release a filament (puff)
        {
            FilaState_t new_fila;
            new_fila.pos[0] = config.source_pos[0];
            new_fila.pos[1] = config.source_pos[1];
            new_fila.pos[2] = config.source_pos[2];
            new_fila.vel[0] = 0;
            new_fila.vel[1] = 0;
            new_fila.vel[2] = 0;
            new_fila.r = 0.001;
            //new_fila.r = 0.01;
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

void plume_update(SimState_t* sim_state)
{
#if defined(USE_FILAMENT_MODEL)
    fila->update(sim_state);
#endif
}

#if defined(USE_FILAMENT_MODEL)
std::vector<FilaState_t>* plume_get_fila_state(void)
{
    return &fila->state;
}
#endif

/* End of plume.cxx */
