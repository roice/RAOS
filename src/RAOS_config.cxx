/*
 * Configuration file of RAOS
 *
 * This file contains configuration data and methods of RAOS.
 *
 * Author: Roice (LUO Bing)
 * Date: 2016-02-25 create this file
 */
#include "RAOS_config.h"
// for .ini file reading
#include <boost/property_tree/ptree.hpp>  
#include <boost/property_tree/ini_parser.hpp>

/* Configuration data */
static RAOS_config_t settings;

/* Restore settings from configuration file */
void RAOS_config_restore(void)
{
    /* check if there exists a config file */
    if(access("settings.ini", 0))
    {// config file not exist
        RAOS_config_init(); // load default config
        // create new config file
        FILE *fp;
        fp = fopen("settings.ini", "w+");
        RAOS_config_save();
        fclose(fp);
    }
    else // config file exist
    {
        char name_str[100];
        /* read configuration files */
        boost::property_tree::ptree pt;
        boost::property_tree::ini_parser::read_ini("settings.ini", pt);
        /* restore configs */
        // common
        settings.common.dt = pt.get<float>("Common.dt");
        settings.common.speed = pt.get<float>("Common.speed");
        // arena
        settings.arena.w = pt.get<float>("Arena.width");
        settings.arena.l = pt.get<float>("Arena.length");
        settings.arena.h = pt.get<float>("Arena.height");
        settings.arena.num_sources = pt.get<int>("Arena.num_sources");
        // wind
        settings.wind.model_name = pt.get<std::string>("Wind.model_name");
        settings.wind.wind_vel[0] = pt.get<float>("Wind.wind_vel_x");
        settings.wind.wind_vel[1] = pt.get<float>("Wind.wind_vel_y");
        settings.wind.wind_vel[2] = pt.get<float>("Wind.wind_vel_z");
        // plume
        for (int i = 0; i < RAOS_MAX_NUM_SOURCES; i++) {
            snprintf(name_str, 100, "Plume_%d.source_pos_x", i+1);
            settings.plume[i].source_pos[0] = pt.get<float>(name_str);
            snprintf(name_str, 100, "Plume_%d.source_pos_y", i+1);
            settings.plume[i].source_pos[1] = pt.get<float>(name_str);
            snprintf(name_str, 100, "Plume_%d.source_pos_z", i+1);
            settings.plume[i].source_pos[2] = pt.get<float>(name_str);
            snprintf(name_str, 100, "Plume_%d.source_molecules_per_second", i+1);
            settings.plume[i].source_mps = pt.get<double>(name_str); // molecules per second (10^18)
            snprintf(name_str, 100, "Plume_%d.model_name", i+1);
            settings.plume[i].model_name = pt.get<std::string>(name_str);
            snprintf(name_str, 100, "Plume_%d.model_farrell_pps", i+1);
            settings.plume[i].model_farrell_pps = pt.get<int>(name_str); // parcels per second
            snprintf(name_str, 100, "Plume_%d.model_farrell_lambda", i+1);
            settings.plume[i].model_farrell_lambda = pt.get<float>(name_str);
        }
        // robot
        for (int i = 0; i < RAOS_MAX_NUM_ROBOTS; i++) {
            snprintf(name_str, 100, "Robot_%d.type", i+1);
            settings.robot[i].type = pt.get<std::string>(name_str);
            snprintf(name_str, 100, "Robot_%d.init_pos_x", i+1);
            settings.robot[i].init_pos[0] = pt.get<float>(name_str);
            snprintf(name_str, 100, "Robot_%d.init_pos_y", i+1);
            settings.robot[i].init_pos[1] = pt.get<float>(name_str);
            snprintf(name_str, 100, "Robot_%d.init_pos_z", i+1);
            settings.robot[i].init_pos[2] = pt.get<float>(name_str);
        } 
    }
}

/* Save settings to configuration file */
void RAOS_config_save(void)
{
    char name_str[100];
    
    /* prepare to write configuration files */
    boost::property_tree::ptree pt;
    
    // common
    pt.put("Common.dt", settings.common.dt);
    pt.put("Common.speed", settings.common.speed);
    // arena size
    pt.put("Arena.width", settings.arena.w);
    pt.put("Arena.length", settings.arena.l);
    pt.put("Arena.height", settings.arena.h);
    pt.put("Arena.num_sources", settings.arena.num_sources);
    // wind
    pt.put("Wind.model_name", settings.wind.model_name);
    pt.put("Wind.wind_vel_x", settings.wind.wind_vel[0]);
    pt.put("Wind.wind_vel_y", settings.wind.wind_vel[1]);
    pt.put("Wind.wind_vel_z", settings.wind.wind_vel[2]);
    // plume
    for (int i = 0; i < RAOS_MAX_NUM_SOURCES; i++) {
        snprintf(name_str, 100, "Plume_%d.source_pos_x", i+1);
        pt.put(name_str, settings.plume[i].source_pos[0]);
        snprintf(name_str, 100, "Plume_%d.source_pos_y", i+1);
        pt.put(name_str, settings.plume[i].source_pos[1]);
        snprintf(name_str, 100, "Plume_%d.source_pos_z", i+1);
        pt.put(name_str, settings.plume[i].source_pos[2]);
        snprintf(name_str, 100, "Plume_%d.source_molecules_per_second", i+1);
        pt.put(name_str, settings.plume[i].source_mps);
        snprintf(name_str, 100, "Plume_%d.model_name", i+1);
        pt.put(name_str, settings.plume[i].model_name);
        snprintf(name_str, 100, "Plume_%d.model_farrell_pps", i+1);
        pt.put(name_str, settings.plume[i].model_farrell_pps);
        snprintf(name_str, 100, "Plume_%d.model_farrell_lambda", i+1);
        pt.put(name_str, settings.plume[i].model_farrell_lambda);
    }
    // robot
    for (int i = 0; i < RAOS_MAX_NUM_ROBOTS; i++) {
        snprintf(name_str, 100, "Robot_%d.type", i+1);
        pt.put(name_str, settings.robot[i].type);
        snprintf(name_str, 100, "Robot_%d.init_pos_x", i+1);
        pt.put(name_str, settings.robot[i].init_pos[0]);
        snprintf(name_str, 100, "Robot_%d.init_pos_y", i+1);
        pt.put(name_str, settings.robot[i].init_pos[1]);
        snprintf(name_str, 100, "Robot_%d.init_pos_z", i+1);
        pt.put(name_str, settings.robot[i].init_pos[2]);
    }

    /* write */
    boost::property_tree::ini_parser::write_ini("settings.ini", pt);
}

/* init settings (obsolete) */
void RAOS_config_init(void)
{
    /* init arena settings */
    // common
    settings.common.dt = 1.0/50.0; // 50 Hz
    settings.common.speed = 0; // auto highest
    // arena
    settings.arena.w = 10; // x
    settings.arena.l = 10; // y
    settings.arena.h = 10; // z
    settings.arena.num_sources = 1; // one source by default
    // wind
    settings.wind.model_name = "Uniform"; // "Potential"
    settings.wind.wind_vel[0] = 0.5;
    settings.wind.wind_vel[1] = 0.;
    settings.wind.wind_vel[2] = 0.;
    // plume
    for (int i = 0; i < RAOS_MAX_NUM_SOURCES; i++) {
        settings.plume[i].source_pos[0] = 0;
        settings.plume[i].source_pos[1] = 0+i*0.5;
        settings.plume[i].source_pos[2] = 0;
        settings.plume[i].source_mps = 235.5; // 2.355*10^20 molecules/parcel
        settings.plume[i].model_name = "Farrell";
        settings.plume[i].model_farrell_pps = 100;
        settings.plume[i].model_farrell_lambda = 0.3;
    }
    // robot
    for (int i = 0; i < RAOS_MAX_NUM_ROBOTS; i++) {
        settings.robot[i].type = "quadrotor";
        settings.robot[i].init_pos[0] = 1;
        settings.robot[i].init_pos[1] = 0+i*0.5;
        settings.robot[i].init_pos[2] = 2;
    }
}

/* get pointer of config data */
RAOS_config_t* RAOS_config_get_settings(void)
{
    return &settings;
}

/* End of RAOS_config.cxx */
