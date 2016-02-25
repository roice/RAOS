/*
 * Configuration file of RAOS
 *
 * This file contains configuration data and methods of RAOS.
 * The declarations of the classes, functions and data are written in 
 * file SimConfig.h, which is included by SimMain.cxx SimLoop.cxx and
 * user interface & drawing files.
 *
 * Author: Roice (LUO Bing)
 * Date: 2016-02-25 create this file
 */
#include "SimConfig.h"
// for .ini file reading
#include <boost/property_tree/ptree.hpp>  
#include <boost/property_tree/ini_parser.hpp>

/* Configuration data */
static SimConfig_t settings;

/* Restore settings from configuration file */
void SimConfig_restore(void)
{
    /* check if there exists a config file */
    if(access("settings.cfg", 0))
    {// config file not exist
        SimConfig_init(); // load default config
        // create new config file
        FILE *fp;
        fp = fopen("settings.cfg", "w+");
        fclose(fp);
    }
    else // config file exist
    {
        /* read configuration files */
        boost::property_tree::ptree pt;
        boost::property_tree::ini_parser::read_ini("settings.cfg", pt);
        /* restore configs */
        // arena
        settings.arena.w = pt.get<float>("Arena.width");
        settings.arena.l = pt.get<float>("Arena.length");
        settings.arena.h = pt.get<float>("Arena.height");
        // source
        settings.source.x = pt.get<float>("Source.x");
        settings.source.y = pt.get<float>("Source.y");
        settings.source.z = pt.get<float>("Source.z");
        // robot
        settings.robot.init_x = pt.get<float>("Robot.init_x");
        settings.robot.init_y = pt.get<float>("Robot.init_y");
        settings.robot.init_z = pt.get<float>("Robot.init_z");
    }
}

/* Save settings to configuration file */
void SimConfig_save(void)
{
    /* prepare to write configuration files */
    boost::property_tree::ptree pt;
    // arena size
    pt.put("Arena.width", settings.arena.w);
    pt.put("Arena.length", settings.arena.l);
    pt.put("Arena.height", settings.arena.h);
    // odor source
    pt.put("Source.x", settings.source.x);
    pt.put("Source.y", settings.source.y);
    pt.put("Source.z", settings.source.z);
    // odor source
    pt.put("Robot.init_x", settings.robot.init_x);
    pt.put("Robot.init_y", settings.robot.init_y);
    pt.put("Robot.init_z", settings.robot.init_z);
    /* write */
    boost::property_tree::ini_parser::write_ini("settings.cfg", pt);
}

/* init settings (obsolete) */
void SimConfig_init(void)
{
    /* init arena settings */
    // arena
    settings.arena.w = 10; // x
    settings.arena.l = 10; // y
    settings.arena.h = 10; // z
    // source
    settings.source.x = 0;
    settings.source.y = 0;
    settings.source.z = 2; // 2 m
    // robot
    settings.robot.init_x = 1;
    settings.robot.init_y = 0;
    settings.robot.init_z = 2;
}

/* get pointer of config data */
SimConfig_t* SimConfig_get_configs(void)
{
    return &settings;
}

/* End of SimConfig.cxx */
