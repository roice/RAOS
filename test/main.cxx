#include "SimConfig.h"
#include "model/SimModel.h"

int main(int argc, char **argv)
{
    SimConfig_restore();

    SimModel_init();

    for (int i = 0; i < 1000; i++)
    {
        SimModel_update();
    }

    SimModel_finish();

    return 0;
}
