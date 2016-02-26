/*
 * plume model
 *
 * Author: Roice (LUO Bing)
 * Date: 2016-02-26 create this file (RAOS)
 */
#include <vector>
#include "plume.h"
#include "SimConfig.h"

/*============== Filament Model ============*/
#if defined(USE_FILAMENT_MODEL)

#define MAX_NUM_FILA 100
class FilaModel
{
    public:
        std::vector<FilaState_t> state; // state of fila, a list

        void init(void) // fila initialization
        {
            // init delta time
            dt = 0.1; // sec
            // init source pos params
            SimConfig_t *config = SimConfig_get_configs();
            source_pos[0] = config->source.x;
            source_pos[1] = config->source.y;
            source_pos[2] = config->source.z;
            /* init fila state */
            state.reserve(MAX_NUM_FILA); // make room for MAX_NUM_FILA fila
            /* release first odor pack at source */
            fila_release();
            /* clear number of fila need to release */
            fila_num_need_release = 0.0;
        }
        void update(void) // update fila
        {
        /* Step 1: update positions of fila */
            int i;
            for (i = 0; i < state.size(); i++) // for each fila
            {
                // calculate wind
                // calculate pos increment
                state.at(i).x += 3.0 * dt;
            }
        /* Step 2: update sizes of fila */
        /* Step 3: fila maintainance */
            fila_release();
        }
    private:
        float dt; // delta time
        float source_pos[3]; // source pos
        float fila_num_need_release; // "buffer" fila
        void fila_release(void) // release a filament (puff)
        {
            FilaState_t new_fila;
            new_fila.x = source_pos[0];
            new_fila.y = source_pos[1];
            new_fila.z = source_pos[2];
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
