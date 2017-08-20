#include <vector>
#include "RAOS_model.h"
#include "model_plume_farrell.h"

void* model_plume_get_state(int idx_plume)
{
    int count = 0;
    std::vector<RAOS_model_t> *model_list = RAOS_model_get_list();

    for (int idx_model = 0; idx_model < (int)(model_list->size()); idx_model++)
    {
        if (model_list->at(idx_model).type >= RAOS_MODEL_PLUME_FARRELL and model_list->at(idx_model).type <= RAOS_MODEL_PLUME_CUSTOM) {
            if (count == idx_plume) {
                // find the plume model
                if (model_list->at(idx_model).type == RAOS_MODEL_PLUME_FARRELL)
                    return (void*)((model_plume_farrell_c*)model_list->at(idx_model).ptr)->get_state();
            }
            else
                count++;
        }
    }
    return 0;
}
