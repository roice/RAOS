#include "hdf5.h"
#include <vector>
#include "model/robot.h"
#include "model/SimModel.h"
#include "model/plume.h"

#include <string.h>
#include <stdlib.h>

void SimSaveData(void)
{
    hid_t file_id, group_id, dataset_id, dataspace_id;
    herr_t status;
    hsize_t data_dims[2];

    char ds_name[20];
    char gr_name[20];
    int idx_vortice = 0;

    // create file, if the file already exists, the current contents will be 
    // deleted so that the application can rewrite the file with new data.
    char filename[60];
    time_t t = time(NULL);
    struct tm* t_lo = localtime(&t);
    strftime(filename, sizeof(filename), "Record_%Y-%m-%d_%H-%M-%S.h5", t_lo);
    //file_id = H5Fcreate(filename, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    file_id = H5Fcreate("record.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

    float* data;
   
    std::vector<Robot*>* robots = SimModel_get_robots();
    std::vector<FilaState_t>* plume = plume_get_fila_state();
#ifdef RAOS_FEATURE_WAKES
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
#endif
    /* Save all plume puffs into this file */
    /* Create the data space for the dataset. */
    data_dims[0] = plume->size();
    data_dims[1] = 4; // 3 dim position and r
    dataspace_id = H5Screate_simple(2, data_dims, NULL);
    /* Create the dataset. */
    dataset_id = H5Dcreate2(file_id, "plume", H5T_NATIVE_FLOAT, dataspace_id, 
                          H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    /* write data */
    data = (float*)malloc(data_dims[0]*data_dims[1]*sizeof(*data));
    for (int idx_p = 0; idx_p < data_dims[0]; idx_p++) {
        memcpy(&(data[idx_p*4]), &(plume->at(idx_p).pos[0]), 3*sizeof(float)); // 3 dims position
        memcpy(&(data[idx_p*4+3]), &(plume->at(idx_p).r), sizeof(float)); // radius
    }
    status = H5Dwrite(dataset_id, H5T_NATIVE_FLOAT, H5S_ALL, H5S_ALL,
                      H5P_DEFAULT, data);
    /* End access to the dataset and release resources used by it. */
    status = H5Dclose(dataset_id);
    /* Terminate access to the data space. */ 
    status = H5Sclose(dataspace_id);
    // free space
    free(data);
    
    /* Save robot record into this file */
    for (int idx_robot = 0; idx_robot < robots->size(); idx_robot++)
    {
        /* Create a group named "robot1..." in the file */
        snprintf(gr_name, 32, "robot%d", idx_robot+1);
        group_id = H5Gcreate2(file_id, gr_name, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

        /* Create the data space for the dataset. */
        data_dims[0] = robots->at(idx_robot)->record.size();
        // robot pos, vel, acc, att, att_vel, wind
        data_dims[1] = 3; // 3 dim

        dataspace_id = H5Screate_simple(2, data_dims, NULL);
        /* Create the dataset. */
        dataset_id = H5Dcreate2(group_id, "pos", H5T_NATIVE_FLOAT, dataspace_id, 
                          H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        /* write data */
        data = (float*)malloc(data_dims[0]*data_dims[1]*sizeof(*data));
        for (int idx_p = 0; idx_p < data_dims[0]; idx_p++)
            memcpy(&(data[idx_p*3]), robots->at(idx_robot)->record.at(idx_p).pos, 3*sizeof(float)); // 3 dims position
        status = H5Dwrite(dataset_id, H5T_NATIVE_FLOAT, H5S_ALL, H5S_ALL,
                      H5P_DEFAULT, data);
        /* End access to the dataset and release resources used by it. */
        status = H5Dclose(dataset_id);
        /* Terminate access to the data space. */ 
        status = H5Sclose(dataspace_id);
        // free space
        free(data);

        dataspace_id = H5Screate_simple(2, data_dims, NULL);
        /* Create the dataset. */
        dataset_id = H5Dcreate2(group_id, "vel", H5T_NATIVE_FLOAT, dataspace_id, 
                          H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        /* write data */
        data = (float*)malloc(data_dims[0]*data_dims[1]*sizeof(*data));
        for (int idx_p = 0; idx_p < data_dims[0]; idx_p++)
            memcpy(&(data[idx_p*3]), robots->at(idx_robot)->record.at(idx_p).vel, 3*sizeof(float)); // 3 dims position
        status = H5Dwrite(dataset_id, H5T_NATIVE_FLOAT, H5S_ALL, H5S_ALL,
                      H5P_DEFAULT, data);
        /* End access to the dataset and release resources used by it. */
        status = H5Dclose(dataset_id);
        /* Terminate access to the data space. */ 
        status = H5Sclose(dataspace_id);
        // free space
        free(data);

        dataspace_id = H5Screate_simple(2, data_dims, NULL);
        /* Create the dataset. */
        dataset_id = H5Dcreate2(group_id, "acc", H5T_NATIVE_FLOAT, dataspace_id, 
                          H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        /* write data */
        data = (float*)malloc(data_dims[0]*data_dims[1]*sizeof(*data));
        for (int idx_p = 0; idx_p < data_dims[0]; idx_p++)
            memcpy(&(data[idx_p*3]), robots->at(idx_robot)->record.at(idx_p).acc, 3*sizeof(float)); // 3 dims position
        status = H5Dwrite(dataset_id, H5T_NATIVE_FLOAT, H5S_ALL, H5S_ALL,
                      H5P_DEFAULT, data);
        /* End access to the dataset and release resources used by it. */
        status = H5Dclose(dataset_id);
        /* Terminate access to the data space. */ 
        status = H5Sclose(dataspace_id);
        // free space
        free(data);

        dataspace_id = H5Screate_simple(2, data_dims, NULL);
        /* Create the dataset. */
        dataset_id = H5Dcreate2(group_id, "att", H5T_NATIVE_FLOAT, dataspace_id, 
                          H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        /* write data */
        data = (float*)malloc(data_dims[0]*data_dims[1]*sizeof(*data));
        for (int idx_p = 0; idx_p < data_dims[0]; idx_p++)
            memcpy(&(data[idx_p*3]), robots->at(idx_robot)->record.at(idx_p).att, 3*sizeof(float)); // 3 dims position
        status = H5Dwrite(dataset_id, H5T_NATIVE_FLOAT, H5S_ALL, H5S_ALL,
                      H5P_DEFAULT, data);
        /* End access to the dataset and release resources used by it. */
        status = H5Dclose(dataset_id);
        /* Terminate access to the data space. */ 
        status = H5Sclose(dataspace_id);
        // free space
        free(data);

        dataspace_id = H5Screate_simple(2, data_dims, NULL);
        /* Create the dataset. */
        dataset_id = H5Dcreate2(group_id, "wind", H5T_NATIVE_FLOAT, dataspace_id, 
                          H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        /* write data */
        data = (float*)malloc(data_dims[0]*data_dims[1]*sizeof(*data));
        for (int idx_p = 0; idx_p < data_dims[0]; idx_p++)
            memcpy(&(data[idx_p*3]), robots->at(idx_robot)->record.at(idx_p).wind, 3*sizeof(float)); // 3 dims position
        status = H5Dwrite(dataset_id, H5T_NATIVE_FLOAT, H5S_ALL, H5S_ALL,
                      H5P_DEFAULT, data);
        /* End access to the dataset and release resources used by it. */
        status = H5Dclose(dataset_id);
        /* Terminate access to the data space. */ 
        status = H5Sclose(dataspace_id);
        // free space
        free(data);

        dataspace_id = H5Screate_simple(2, data_dims, NULL);
        /* Create the dataset. */
        dataset_id = H5Dcreate2(group_id, "wind_est_incl", H5T_NATIVE_FLOAT, dataspace_id, 
                          H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        /* write data */
        data = (float*)malloc(data_dims[0]*data_dims[1]*sizeof(*data));
        for (int idx_p = 0; idx_p < data_dims[0]; idx_p++)
            memcpy(&(data[idx_p*3]), robots->at(idx_robot)->record.at(idx_p).wind_est_incl, 3*sizeof(float)); // 3 dims position
        status = H5Dwrite(dataset_id, H5T_NATIVE_FLOAT, H5S_ALL, H5S_ALL,
                      H5P_DEFAULT, data);
        /* End access to the dataset and release resources used by it. */
        status = H5Dclose(dataset_id);
        /* Terminate access to the data space. */ 
        status = H5Sclose(dataspace_id);
        // free space
        free(data);

        dataspace_id = H5Screate_simple(2, data_dims, NULL);
        /* Create the dataset. */
        dataset_id = H5Dcreate2(group_id, "wind_est_leso", H5T_NATIVE_FLOAT, dataspace_id, 
                          H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        /* write data */
        data = (float*)malloc(data_dims[0]*data_dims[1]*sizeof(*data));
        for (int idx_p = 0; idx_p < data_dims[0]; idx_p++)
            memcpy(&(data[idx_p*3]), robots->at(idx_robot)->record.at(idx_p).wind_est_leso, 3*sizeof(float)); // 3 dims position
        status = H5Dwrite(dataset_id, H5T_NATIVE_FLOAT, H5S_ALL, H5S_ALL,
                      H5P_DEFAULT, data);
        /* End access to the dataset and release resources used by it. */
        status = H5Dclose(dataset_id);
        /* Terminate access to the data space. */ 
        status = H5Sclose(dataspace_id);
        // free space
        free(data);
    }

    /* Terminate access to the file. */
    status = H5Fclose(file_id);
}
