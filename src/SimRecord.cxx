#include "hdf5.h"
#include <vector>
#include "model/robot.h"
#include "model/SimModel.h"

#include <string.h>
#include <stdlib.h>

void SimSaveData(void)
{
    hid_t file_id, dataset_id, dataspace_id;
    herr_t status;
    hsize_t data_dims[2];

    char ds_name[20];
    int idx_vortice = 0;

    float* data;
   
    std::vector<Robot*>* robots = SimModel_get_robots(); 

    // create file, if the file already exists, the current contents will be 
    // deleted so that the application can rewrite the file with new data.
    file_id = H5Fcreate("vortices.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

    /* Save all vortices into this file */
    for (int i = 0; i < robots->size(); i++) {
        for (int j = 0; j < robots->at(i)->wakes.size(); j++) {
            for (int k = 0; k < robots->at(i)->wakes.at(j)->rotor_state.frame.n_blades; k++) {
                /* Create the data space for the dataset. */
                data_dims[0] = robots->at(i)->wakes.at(j)->wake_state[k]->size();
                data_dims[1] = 3; // 3 dim position info
                dataspace_id = H5Screate_simple(2, data_dims, NULL);
    
                /* Create the dataset. */
                sprintf(ds_name, "vortice_%d", idx_vortice++);
                dataset_id = H5Dcreate2(file_id, ds_name, H5T_NATIVE_FLOAT, dataspace_id, 
                          H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    
                /* write data */
                data = (float*)malloc(data_dims[0]*data_dims[1]*sizeof(*data));
                for (int idx_m = 0; idx_m < data_dims[0]; idx_m++) {
                    memcpy(&(data[idx_m*3]), &(robots->at(i)->wakes.at(j)->wake_state[k]->at(idx_m).pos[0]), 3*sizeof(float)); // 3 dims position
                }
                status = H5Dwrite(dataset_id, H5T_NATIVE_FLOAT, H5S_ALL, H5S_ALL,
                      H5P_DEFAULT, data);

                /* End access to the dataset and release resources used by it. */
                status = H5Dclose(dataset_id);

                /* Terminate access to the data space. */ 
                status = H5Sclose(dataspace_id);

                // free space
                free(data);
            }
        }
    }

    /* Terminate access to the file. */
    status = H5Fclose(file_id);
}
