/*
 * User Interface of Simulator
 *         using FLTK
 *
 * Author: Roice (LUO Bing)
 * Date: 2016-02-01 create this file
 */

/* FLTK */
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Pixmap.H>
#include <FL/Fl_Tabs.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Value_Input.H>
#include <FL/Fl_Value_Slider.H>
/* OpenGL */
#include <FL/Fl_Gl_Window.H>
#include GL_HEADER
#include GLUT_HEADER
/* RAOS */
#include "RAOS_config.h" // runtime RAOS configs
#include "ui/RAOS_UI.h"
#include "ui/icons/icons.h" // pixmap icons used in Tool bar
#include "ui/RAOS_view.h" // 3D RAO view
#include "model/RAOS_model.h"

/*------- Configuration Dialog -------*/
struct ConfigDlg_widgets { // for parameter saving
    // arena widith/length/height
    Fl_Value_Input  *arena_w;
    Fl_Value_Input  *arena_l;
    Fl_Value_Input  *arena_h;
    // source position
    Fl_Choice       *source_num;  // number of source 
    Fl_Choice       *source_sel;  // select which source to change pos
    Fl_Value_Slider *source_x;
    Fl_Value_Slider *source_y;
    Fl_Value_Slider *source_z;
    // wind
    Fl_Choice       *wind_model_sel; // wind model selection
    Fl_Box          *wind_vel_box; // (mean) wind velocity box
    Fl_Value_Slider *wind_vel_x;
    Fl_Value_Slider *wind_vel_y;
    Fl_Value_Slider *wind_vel_z;
    // plume
    Fl_Choice       *plume_sel; // select which plume to change parameters
    Fl_Choice       *plume_model_sel; // plume model selection
    Fl_Box          *plume_model_farrell_box; // farrell model paramenter box
    Fl_Value_Input  *plume_model_farrell_pps;   // parcels per second of Farrell model
    Fl_Value_Input  *plume_model_farrell_lambda; // lambda parameter of Farrell model
};
class ConfigDlg : public Fl_Window
{
public:
    ConfigDlg(int xpos, int ypos, int width, int height, const char* title);
private:
    // widgets
    struct ConfigDlg_widgets dlg_w;
    // callback funcs
    static void cb_close(Fl_Widget*, void*);
    static void cb_switch_tabs(Fl_Widget*, void*);
    static void cb_change_src_num(Fl_Widget*, void*);
    static void cb_change_src_sel(Fl_Widget*, void*);
    static void cb_change_src_pos_bounds(Fl_Widget*, void*);
    static void cb_change_src_pos_x(Fl_Widget*, void*);
    static void cb_change_src_pos_y(Fl_Widget*, void*);
    static void cb_change_src_pos_z(Fl_Widget*, void*);
    static void cb_change_wind_model_selection(Fl_Widget*, void*);
    static void cb_change_wind_velocity(Fl_Widget*, void*);
    static void cb_change_plume_sel(Fl_Widget*, void*);
    static void cb_change_plume_model_selection(Fl_Widget*, void*);
    static void cb_change_plume_model_parameters(Fl_Widget*, void*);
    // function to get runtime configs to set value of widgets
    static void set_value_from_configs(ConfigDlg_widgets*);
};

void ConfigDlg::cb_close(Fl_Widget* w, void* data) {
    if (Fl::event() == FL_CLOSE) {
        // save RAOS runtime configs to file when closing the dialog window
        RAOS_config_save();
        ((Fl_Window*)w)->hide();
    }
}

void ConfigDlg::cb_switch_tabs(Fl_Widget *w, void *data)
{
    Fl_Tabs *tabs = (Fl_Tabs*)w; 
    // When tab changed, make sure it has same color as its group
    tabs->selection_color( (tabs->value())->color() );
}

// change source number and source selections
void ConfigDlg::cb_change_src_num(Fl_Widget* src_num, void* data) {
    struct ConfigDlg_widgets *ws = (struct ConfigDlg_widgets*)data;
    char name_str[20];
    // change source selection candidates
    int src_sel_value = ws->source_sel->value();
    ws->source_sel->clear();
    for (int i = 0; i < ((Fl_Choice*)src_num)->value()+1; i++) {
        snprintf(name_str, 20, "%d", i+1);
        ws->source_sel->add(name_str);
    } 
    // change source selection if nessesary
    if (src_sel_value > ((Fl_Choice*)src_num)->value())
        ws->source_sel->value(((Fl_Choice*)src_num)->value());
    else
        ws->source_sel->value(src_sel_value);
    // change plume selection candidates
    int plume_sel_value = ws->plume_sel->value();
    ws->plume_sel->clear();
    for (int i = 0; i < ((Fl_Choice*)src_num)->value()+1; i++) {
        snprintf(name_str, 20, "%d", i+1);
        ws->plume_sel->add(name_str);
    }
    // change plume selection if nessesary
    if (plume_sel_value > ((Fl_Choice*)src_num)->value())
        ws->plume_sel->value(((Fl_Choice*)src_num)->value());
    else
        ws->plume_sel->value(plume_sel_value);
    // save to configs
    RAOS_config_t *configs = RAOS_config_get_settings();
    configs->arena.num_sources = ((Fl_Choice*)src_num)->value()+1;
}

void ConfigDlg::cb_change_src_sel(Fl_Widget* src_sel, void* data) {
    struct ConfigDlg_widgets *ws = (struct ConfigDlg_widgets*)data;
    RAOS_config_t *configs = RAOS_config_get_settings();
    ws->source_x->value(configs->plume[((Fl_Choice*)src_sel)->value()].source_pos[0]);
    ws->source_y->value(configs->plume[((Fl_Choice*)src_sel)->value()].source_pos[1]);
    ws->source_z->value(configs->plume[((Fl_Choice*)src_sel)->value()].source_pos[2]);
}

// change source position bounds according to arena size
void ConfigDlg::cb_change_src_pos_bounds(Fl_Widget* arena_wlh, void* src_xyz) {
    ((Fl_Value_Slider*)src_xyz)->minimum(-((Fl_Valuator*)arena_wlh)->value()/2.0);
    ((Fl_Value_Slider*)src_xyz)->maximum(((Fl_Valuator*)arena_wlh)->value()/2.0);
}

// change source position
void ConfigDlg::cb_change_src_pos_x(Fl_Widget* src_xyz, void* src_sel) {
    RAOS_config_t* configs = RAOS_config_get_settings(); // get runtime configs
    configs->plume[((Fl_Choice*)src_sel)->value()].source_pos[0] = ((Fl_Value_Slider*)src_xyz)->value(); 
}
void ConfigDlg::cb_change_src_pos_y(Fl_Widget* src_xyz, void* src_sel) {
    RAOS_config_t* configs = RAOS_config_get_settings(); // get runtime configs
    configs->plume[((Fl_Choice*)src_sel)->value()].source_pos[1] = ((Fl_Value_Slider*)src_xyz)->value(); 
}
void ConfigDlg::cb_change_src_pos_z(Fl_Widget* src_xyz, void* src_sel) {
    RAOS_config_t* configs = RAOS_config_get_settings(); // get runtime configs
    configs->plume[((Fl_Choice*)src_sel)->value()].source_pos[2] = ((Fl_Value_Slider*)src_xyz)->value(); 
}

// change wind model selection
void ConfigDlg::cb_change_wind_model_selection(Fl_Widget* sel, void* data)
{
    struct ConfigDlg_widgets *ws = (struct ConfigDlg_widgets*)data;
    if (((Fl_Choice*)sel)->value() == 0) { // uniform flow field
        ws->wind_vel_box->label("Wind Velocity");
        ws->wind_vel_box->hide();
        ws->wind_vel_box->show();
    }
    if (((Fl_Choice*)sel)->value() == 1) { // potential flow field
        ws->wind_vel_box->label("Mean Wind Velocity");
        ws->wind_vel_box->hide();
        ws->wind_vel_box->show();
    }

    // save to config
    RAOS_config_t* configs = RAOS_config_get_settings(); // get runtime configs
    if (((Fl_Choice*)sel)->value() == 0)
        configs->wind.model_name = "Uniform";
    else if (((Fl_Choice*)sel)->value() == 1)
        configs->wind.model_name = "Potential";
}

void ConfigDlg::cb_change_wind_velocity(Fl_Widget* wind_vel_xyz, void* idx)
{
    RAOS_config_t* configs = RAOS_config_get_settings(); // get runtime configs
    configs->wind.wind_vel[(long int)((long int*)idx)] = ((Fl_Value_Slider*)wind_vel_xyz)->value();
}

void ConfigDlg::cb_change_plume_sel(Fl_Widget* sel, void* data)
{
    RAOS_config_t* configs = RAOS_config_get_settings(); // get runtime configs
    struct ConfigDlg_widgets *ws = (struct ConfigDlg_widgets*)data;

    // display the parameters of this plume selection
    ws->plume_model_farrell_pps->value(configs->plume[((Fl_Choice*)sel)->value()].model_farrell_pps);
    ws->plume_model_farrell_lambda->value(configs->plume[((Fl_Choice*)sel)->value()].model_farrell_lambda);
}

void ConfigDlg::cb_change_plume_model_selection(Fl_Widget* sel, void* data)
{
    RAOS_config_t* configs = RAOS_config_get_settings(); // get runtime configs
    struct ConfigDlg_widgets *ws = (struct ConfigDlg_widgets*)data;
    
    if (((Fl_Choice*)sel)->value() == 0) { // Farrell plume model
        ws->plume_model_farrell_box->show();
        configs->plume[ws->plume_sel->value()].model_name = "Farrell";
    }
}

void ConfigDlg::cb_change_plume_model_parameters(Fl_Widget* w, void* data)
{
    struct ConfigDlg_widgets *ws = (struct ConfigDlg_widgets*)data;
    RAOS_config_t* configs = RAOS_config_get_settings(); // get runtime configs
    // find which widget called this function and execute corresponding actions
    if (w == ws->plume_model_farrell_pps)
        configs->plume[ws->plume_sel->value()].model_farrell_pps = ((Fl_Value_Input*)w)->value();
    else if (w == ws->plume_model_farrell_lambda)
        configs->plume[ws->plume_sel->value()].model_farrell_lambda = ((Fl_Value_Input*)w)->value();
}

void ConfigDlg::set_value_from_configs(ConfigDlg_widgets* ws) {
    RAOS_config_t* configs = RAOS_config_get_settings(); // get runtime configs
    char name_str[20];
    // set arena size
    ws->arena_w->value(configs->arena.w);
    ws->arena_l->value(configs->arena.l);
    ws->arena_h->value(configs->arena.h);
    // set source num
    ws->source_num->value(configs->arena.num_sources-1);
    // set source selection candidates
    ws->source_sel->clear();
    for (int i = 0; i < ws->source_num->value()+1; i++) {
        snprintf(name_str, 20, "%d", i+1);
        ws->source_sel->add(name_str);
    }
    ws->source_sel->value(0);
    // set source position
    ws->source_x->value(configs->plume[ws->source_sel->value()].source_pos[0]);
    ws->source_y->value(configs->plume[ws->source_sel->value()].source_pos[1]);
    ws->source_z->value(configs->plume[ws->source_sel->value()].source_pos[2]);
    ws->source_x->minimum(-configs->arena.w/2.0);
    ws->source_y->minimum(-configs->arena.l/2.0);
    ws->source_z->minimum(-configs->arena.h/2.0);
    ws->source_x->maximum(configs->arena.w/2.0);
    ws->source_y->maximum(configs->arena.l/2.0);
    ws->source_z->maximum(configs->arena.h/2.0);
    // set wind type
    if (configs->wind.model_name == "Uniform") {
        ws->wind_model_sel->value(0);
        ws->wind_vel_box->label("Wind Velocity");
        ws->wind_vel_box->hide();
        ws->wind_vel_box->show();
    }
    else if (configs->wind.model_name == "Potential") {
        ws->wind_model_sel->value(1);
        ws->wind_vel_box->label("Mean Wind Velocity");
        ws->wind_vel_box->hide();
        ws->wind_vel_box->show();
    }
    // set wind velocity
    ws->wind_vel_x->value(configs->wind.wind_vel[0]);
    ws->wind_vel_y->value(configs->wind.wind_vel[1]);
    ws->wind_vel_z->value(configs->wind.wind_vel[2]);
    // set plume selection candidates
    ws->plume_sel->clear();
    for (int i = 0; i < ws->source_num->value()+1; i++) {
        snprintf(name_str, 20, "%d", i+1);
        ws->plume_sel->add(name_str);
    }
    ws->plume_sel->value(0);
    // set plume model
    if (configs->plume[ws->plume_sel->value(0)].model_name == "Farrell")
        ws->plume_model_sel->value(0);
    // set plume model parameters
    if (ws->plume_model_sel->value() == 0) { // "Farrell"
        ws->plume_model_farrell_box->show();
        ws->plume_model_farrell_pps->value(configs->plume[ws->plume_sel->value()].model_farrell_pps);
        ws->plume_model_farrell_lambda->value(configs->plume[ws->plume_sel->value()].model_farrell_lambda);
    }
}

ConfigDlg::ConfigDlg(int xpos, int ypos, int width, int height, 
        const char* title=0):Fl_Window(xpos,ypos,width,height,title)
{
    // add event handle to dialog window
    callback(cb_close, (void*)&dlg_w);   
    // begin adding children
    begin();
    char name_str[20]; // name string
    // Tabs
    int t_x = 5, t_y = 5, t_w = w()-10, t_h = h()-10;
    Fl_Tabs *tabs = new Fl_Tabs(t_x, t_y, t_w, t_h);
    {
        tabs->callback(cb_switch_tabs); // callback func when switch tabs
        // Tab Scenario
        Fl_Group *scenario = new Fl_Group(t_x,t_y+25,t_w,t_h-25,"Scenario");
        {
            // color of this tab
            scenario->color(0xe8e8e800); // light milk tea
            scenario->selection_color(0xe8e8e800); // light milk tea
            // Arena
            Fl_Box *arena = new Fl_Box(t_x+10, t_y+25+10, t_w-20, 60,"Arena Size X-E/Y-N/Z-U");
            arena->box(FL_PLASTIC_UP_FRAME);
            arena->labelsize(16);
            arena->labelfont(FL_COURIER_BOLD_ITALIC);
            arena->align(Fl_Align(FL_ALIGN_TOP|FL_ALIGN_INSIDE));
            // Arena width/length/height
            dlg_w.arena_w = new Fl_Value_Input(t_x+10+10,t_y+25+10+30,t_w/4, 25,"");
            dlg_w.arena_l = new Fl_Value_Input(t_x+10+10+(t_w-20)/3,t_y+25+10+30, t_w/4, 25,"");
            dlg_w.arena_h = new Fl_Value_Input(t_x+10+10+(t_w-20)*2/3,t_y+25+10+30, t_w/4, 25,"");
            new Fl_Box(t_x+(t_w-20)/3-10,t_y+25+10+30, 20, 25, "m");
            new Fl_Box(t_x+(t_w-20)*2/3-10,t_y+25+10+30, 20, 25, "m");
            new Fl_Box(t_x+t_w-30,t_y+25+10+30, 20, 25, "m");
            // Source
            Fl_Box *source = new Fl_Box(t_x+10, t_y+25+10+65, t_w-20, 120,"Source Position");
            source->box(FL_PLASTIC_UP_FRAME);
            source->labelsize(16);
            source->labelfont(FL_COURIER_BOLD_ITALIC);
            source->align(Fl_Align(FL_ALIGN_TOP|FL_ALIGN_INSIDE));
            // Source number
            dlg_w.source_num = new Fl_Choice(t_x+10+10, t_y+25+10+65+40, 100, 25, "");
            new Fl_Box(t_x+10+10,t_y+25+10+65+20, 100, 25, "Num of Sources");
            // Source pos
            dlg_w.source_sel = new Fl_Choice(t_x+10+10, t_y+25+10+65+90, 100, 25, "");
            new Fl_Box(t_x+10+10,t_y+25+10+65+65, 100, 25, "Which to Edit");
            dlg_w.source_x = new Fl_Value_Slider(t_x+10+(t_w-20)/2,t_y+25+10+65+30,(t_w-20)/2-20,25,"X-E");
            dlg_w.source_y = new Fl_Value_Slider(t_x+10+(t_w-20)/2,t_y+25+10+65+60,(t_w-20)/2-20,25,"Y-N");
            dlg_w.source_z = new Fl_Value_Slider(t_x+10+(t_w-20)/2,t_y+25+10+65+90,(t_w-20)/2-20,25,"Z-U");
            new Fl_Box(t_x+10+t_w-40,t_y+25+10+65+30, 20, 25, "m");
            new Fl_Box(t_x+10+t_w-40,t_y+25+10+65+60, 20, 25, "m");
            new Fl_Box(t_x+10+t_w-40,t_y+25+10+65+90, 20, 25, "m"); 
            for (int i = 0; i < RAOS_MAX_NUM_SOURCES; i++) {
                snprintf(name_str, 20, "%d", i+1);
                dlg_w.source_num->add(name_str);
            }
            dlg_w.source_num->value(0); // default one
            for (int i = 0; i < dlg_w.source_num->value()+1; i++) {
                snprintf(name_str, 20, "%d", i+1);
                dlg_w.source_sel->add(name_str);
            }
            dlg_w.source_sel->value(0);
            dlg_w.source_x->labelsize(16);
            dlg_w.source_y->labelsize(16);
            dlg_w.source_z->labelsize(16);
            dlg_w.source_x->type(FL_HOR_NICE_SLIDER);
            dlg_w.source_y->type(FL_HOR_NICE_SLIDER);
            dlg_w.source_z->type(FL_HOR_NICE_SLIDER);
            dlg_w.source_x->align(Fl_Align(FL_ALIGN_LEFT));
            dlg_w.source_y->align(Fl_Align(FL_ALIGN_LEFT));
            dlg_w.source_z->align(Fl_Align(FL_ALIGN_LEFT)); 
            dlg_w.arena_w->callback(cb_change_src_pos_bounds, (void*)dlg_w.source_x);
            dlg_w.arena_l->callback(cb_change_src_pos_bounds, (void*)dlg_w.source_y);
            dlg_w.arena_h->callback(cb_change_src_pos_bounds, (void*)dlg_w.source_z);
            dlg_w.source_num->callback(cb_change_src_num, (void*)&dlg_w);
            dlg_w.source_sel->callback(cb_change_src_sel, (void*)&dlg_w);
            dlg_w.source_x->callback(cb_change_src_pos_x, (void*)dlg_w.source_sel);
            dlg_w.source_y->callback(cb_change_src_pos_y, (void*)dlg_w.source_sel);
            dlg_w.source_z->callback(cb_change_src_pos_z, (void*)dlg_w.source_sel);
        }
        scenario->end();
        // Tab Flow
        Fl_Group *flow = new Fl_Group(t_x,t_y+25,t_w,t_h-25,"Flow");
        {
            // color of this tab
            flow->color(0xe0ffff00); // light blue
            flow->selection_color(0xe0ffff00); // light blue

            // wind model selection
            dlg_w.wind_model_sel = new Fl_Choice(t_x+t_w/3, t_y+25+10, 200, 25, "Wind Model");
            dlg_w.wind_model_sel->add("Uniform Wind Field");
            dlg_w.wind_model_sel->add("Potential Flow Field");
            dlg_w.wind_model_sel->value(0);
            dlg_w.wind_model_sel->callback(cb_change_wind_model_selection, (void*)&dlg_w);
            // Mean wind velocity
            dlg_w.wind_vel_box = new Fl_Box(t_x+10, t_y+25+10+30, t_w-20, 120,"Wind Velocity");
            dlg_w.wind_vel_box->box(FL_PLASTIC_UP_FRAME);
            dlg_w.wind_vel_box->labelsize(16);
            dlg_w.wind_vel_box->labelfont(FL_COURIER_BOLD_ITALIC);
            dlg_w.wind_vel_box->align(Fl_Align(FL_ALIGN_TOP|FL_ALIGN_INSIDE));
            // Mean wind velocity x/y/z components
            dlg_w.wind_vel_x = new Fl_Value_Slider(t_x+10+30,t_y+25+10+30+30,300,25,"X");
            dlg_w.wind_vel_y = new Fl_Value_Slider(t_x+10+30,t_y+25+10+30+60,300,25,"Y");
            dlg_w.wind_vel_z = new Fl_Value_Slider(t_x+10+30,t_y+25+10+30+90,300,25,"Z");
            dlg_w.wind_vel_x->labelsize(16);
            dlg_w.wind_vel_y->labelsize(16);
            dlg_w.wind_vel_z->labelsize(16);
            dlg_w.wind_vel_x->type(FL_HOR_NICE_SLIDER);
            dlg_w.wind_vel_y->type(FL_HOR_NICE_SLIDER);
            dlg_w.wind_vel_z->type(FL_HOR_NICE_SLIDER);
            dlg_w.wind_vel_x->align(Fl_Align(FL_ALIGN_LEFT));
            dlg_w.wind_vel_y->align(Fl_Align(FL_ALIGN_LEFT));
            dlg_w.wind_vel_z->align(Fl_Align(FL_ALIGN_LEFT));
            dlg_w.wind_vel_x->bounds(0, 10); // 0~10 m/s
            dlg_w.wind_vel_y->bounds(0, 10);
            dlg_w.wind_vel_z->bounds(0, 10);
            dlg_w.wind_vel_x->callback(cb_change_wind_velocity, (void*)0);
            dlg_w.wind_vel_y->callback(cb_change_wind_velocity, (void*)1);
            dlg_w.wind_vel_z->callback(cb_change_wind_velocity, (void*)2);
            new Fl_Box(t_x+10+30+300,t_y+25+10+30+30, 30, 25, "m/s");
            new Fl_Box(t_x+10+30+300,t_y+25+10+30+60, 30, 25, "m/s");
            new Fl_Box(t_x+10+30+300,t_y+25+10+30+90, 30, 25, "m/s");
        }
        flow->end();
        // Tab Plume
        Fl_Group *plume = new Fl_Group(t_x,t_y+25,t_w,t_h-25,"Plume");
        {
            // color of this tab
            plume->color(0xeeee0000); // light yellow+green (chlorine)
            plume->selection_color(0xeeee0000); // light yellow+green
           
            // plume selection
            dlg_w.plume_sel = new Fl_Choice(t_x+t_w/3, t_y+25+10, 200, 25, "Which to Edit");
            for (int i = 0; i < dlg_w.source_num->value()+1; i++) {
                snprintf(name_str, 20, "%d", i+1);
                dlg_w.plume_sel->add(name_str);
            }
            dlg_w.plume_sel->value(0);
            dlg_w.plume_sel->callback(cb_change_plume_sel, (void*)&dlg_w);
            // plume model selection
            dlg_w.plume_model_sel = new Fl_Choice(t_x+t_w/3, t_y+25+10+30, 200, 25, "Plume Model");
            dlg_w.plume_model_sel->add("Farrell Filament");
            dlg_w.plume_model_sel->value(0);
            dlg_w.plume_model_sel->callback(cb_change_plume_model_selection, (void*)&dlg_w);
            // plume model parameters --- Farrell
            dlg_w.plume_model_farrell_box = new Fl_Box(t_x+10, t_y+25+10+60, t_w-20, 100, "Farrell Filament Model Parameters");
            dlg_w.plume_model_farrell_box->box(FL_PLASTIC_UP_FRAME);
            dlg_w.plume_model_farrell_box->labelsize(16);
            dlg_w.plume_model_farrell_box->labelfont(FL_COURIER_BOLD_ITALIC);
            dlg_w.plume_model_farrell_box->align(Fl_Align(FL_ALIGN_TOP|FL_ALIGN_INSIDE));
            dlg_w.plume_model_farrell_pps = new Fl_Value_Input(t_x+t_w/3, t_y+25+10+90, 200, 25, "Parcels/Second");
            dlg_w.plume_model_farrell_pps->type(FL_INT_INPUT);
            dlg_w.plume_model_farrell_pps->step(1);
            dlg_w.plume_model_farrell_pps->range(1, RAOS_MODEL_UPDATE_FREQ); // the source release one parcel every update interval
            dlg_w.plume_model_farrell_lambda = new Fl_Value_Input(t_x+t_w/3, t_y+25+10+120, 200, 25, "Lambda");
            dlg_w.plume_model_farrell_lambda->type(FL_FLOAT_INPUT);
            dlg_w.plume_model_farrell_pps->callback(cb_change_plume_model_parameters, (void*)&dlg_w);
            dlg_w.plume_model_farrell_lambda->callback(cb_change_plume_model_parameters, (void*)&dlg_w);
        }
        plume->end();
        // Tab Robot
        Fl_Group *robot = new Fl_Group(t_x,t_y+25,t_w,t_h-25,"Robot");
        {
            // color of this tab
            robot->color(0xa8a8a800); // light yellow+green (chlorine)
            robot->selection_color(0xa8a8a800); // light yellow+green
        }
        robot->end();
    }
    // Make sure default tab has same color as its group
    tabs->selection_color( (tabs->value())->color() );
    tabs->end();
    
    end();
    // set value according to runtime configs
    set_value_from_configs(&dlg_w);
    show();
}

/*------- ToolBar -------*/
struct ToolBar_Widgets
{
    Fl_Button* start;   // start button
    Fl_Button* pause;   // pause button
    Fl_Button* stop;    // stop button
    Fl_Button* config;  // config button
    Fl_Choice* speed;   // speed selection
};
struct ToolBar_Handles // handles of dialogs/panels opened by corresponding buttons
{
    ConfigDlg* config_dlg; // handle of config dialog opened by config button
};
class ToolBar : public Fl_Group
{
public:
    ToolBar(int Xpos, int Ypos, int Width, int Height, void *win);
    struct ToolBar_Widgets ws;
    static struct ToolBar_Handles hs;
private:
    static void cb_button_start(Fl_Widget*, void*);
    static void cb_button_pause(Fl_Widget*, void*);
    static void cb_button_stop(Fl_Widget*, void*);
    static void cb_button_config(Fl_Widget*, void*);
    static void cb_change_speed(Fl_Widget*, void*);
    static void set_value_from_configs(ToolBar_Widgets*);
};
struct ToolBar_Handles ToolBar::hs = {NULL};

void ToolBar::cb_button_start(Fl_Widget *w, void *data)
{
    ToolBar_Widgets* widgets = (ToolBar_Widgets*)data;

    // if pause button is pressed, meaning that the initialization has been carried out, so just restore and continue
    if (widgets->pause->value()) {
        // release pause button
        widgets->pause->activate(); widgets->pause->clear();
        // continue running
        RAOS_model_thread_resume();
    }
    else {
        // if pause button is not pressed, then check start button state
        if (((Fl_Button*)w)->value()) // if start button is pressed down
        {
            // lock config button
            widgets->config->deactivate();

            // start simulation
            RAOS_model_thread_create();
        }
        else {
            // user is trying to release start button when pause is not pressed
            ((Fl_Button*)w)->value(1);
        }
    }
}

void ToolBar::cb_button_pause(Fl_Widget *w, void *data)
{
    ToolBar_Widgets* widgets = (ToolBar_Widgets*)data;
    // if start button pressed, release it, and pause simulation
    if (widgets->start->value()) {
        widgets->start->value(0); // release start button
        widgets->pause->deactivate(); // make pause button unclickable
        // pause simulation...
        RAOS_model_thread_pause();
    }
    else {
    // if start button not pressed, pause button will not toggle and no code action will be took
        widgets->pause->clear();
    }
}

void ToolBar::cb_button_stop(Fl_Widget *w, void *data)
{
    // release start and pause buttons
    struct ToolBar_Widgets *widgets = (struct ToolBar_Widgets*)data;
    widgets->start->clear();
    widgets->pause->activate(); widgets->pause->clear();

    /* stop simulation */
    RAOS_model_thread_destroy();

    // unlock config button
    widgets->config->activate(); 
}

void ToolBar::cb_button_config(Fl_Widget *w, void *data)
{
    if (hs.config_dlg != NULL)
    {
        if (hs.config_dlg->shown()) // if shown, do not open again
        {}
        else
        {
            hs.config_dlg->show(); 
        }
    }
    else // first press this button
    {// create config dialog
        Fl_Window* window=(Fl_Window*)data;
        hs.config_dlg = new ConfigDlg(window->x()+20, window->y()+20, 
            400, 400, "Settings");
    }
}

void ToolBar::cb_change_speed(Fl_Widget *w, void *data)
{
    RAOS_config_t* configs = RAOS_config_get_settings(); // get runtime configs
    configs->common.speed = ((Fl_Choice*)w)->value();
}

void ToolBar::set_value_from_configs(ToolBar_Widgets *ws)
{
    RAOS_config_t* configs = RAOS_config_get_settings(); // get runtime configs
    ws->speed->value(configs->common.speed);
}

ToolBar::ToolBar(int Xpos, int Ypos, int Width, int Height, void *win) :
Fl_Group(Xpos, Ypos, Width, Height)
{
    begin();
    Fl_Box *bar = new Fl_Box(FL_UP_BOX, 0, 0, Width, Height, "");
    Ypos += 2; Height -= 4; Xpos += 3; Width = Height;
    // widgets of this toolbar
    // instances of buttons belong to tool bar
    ws.start = new Fl_Button(Xpos, Ypos, Width, Height); Xpos += Width + 5;
    ws.pause = new Fl_Button(Xpos, Ypos, Width, Height); Xpos += Width + 5;
    ws.stop = new Fl_Button(Xpos, Ypos, Width, Height); Xpos += Width + 5;
    ws.config = new Fl_Button(Xpos, Ypos, Width, Height); Xpos += Width + 5;
    ws.speed = new Fl_Choice(Xpos, Ypos, 4*Width, Height); Xpos += 4*Width + 5;
    Fl_Box *bar_rest = new Fl_Box(FL_DOWN_BOX, Xpos, Ypos, bar->w()-Xpos, Height, "");
    resizable(bar_rest); // protect buttons from resizing
    // icons
    Fl_Pixmap *icon_start = new Fl_Pixmap(pixmap_icon_play);
    Fl_Pixmap *icon_pause = new Fl_Pixmap(pixmap_icon_pause);
    Fl_Pixmap *icon_stop = new Fl_Pixmap(pixmap_icon_stop);
    Fl_Pixmap *icon_config = new Fl_Pixmap(pixmap_icon_config);
    // link icons to buttons
    ws.start->image(icon_start);
    ws.pause->image(icon_pause);
    ws.stop->image(icon_stop);
    ws.config->image(icon_config);
    // tips for buttons
    ws.start->tooltip("Start Simulation");
    ws.pause->tooltip("Pause Simulation");
    ws.stop->tooltip("Stop Simulation");
    ws.config->tooltip("Settings");
    ws.speed->tooltip("Simulation Speed");
    // speed candidates
    ws.speed->add("Auto Highest");
    char name_str[20];
    for (int i = 0; i < 100; i++) {
        snprintf(name_str, 20, "%dx Speed", i+1);
        ws.speed->add(name_str);
    }
    ws.speed->value(0); // default auto highest
    // types of buttons
    ws.start->type(FL_TOGGLE_BUTTON); // start & pause are mutually exclusive
    ws.pause->type(FL_TOGGLE_BUTTON);
    // link call backs to buttons
    ws.start->callback(cb_button_start, (void*)&ws);
    ws.pause->callback(cb_button_pause, (void*)&ws);
    ws.stop->callback(cb_button_stop, (void*)&ws);
    ws.config->callback(cb_button_config, (void*)win);
    ws.speed->callback(cb_change_speed, (void*)&ws);
    // restore values from configs
    set_value_from_configs(&ws);
    end();
}

/* =============================================
 * ================  UI  =======================
 * ============================================= */
void RAOS_UI::cb_close(Fl_Widget* w, void* data) {
    // close RAOS
    if (Fl::event() == FL_CLOSE) {
        // stop simulation
        RAOS_model_thread_destroy();

        // close main window
        ((Fl_Window*)w)->hide();
    }
}

/*------- Creation function of User Interface  -------*/
RAOS_UI::RAOS_UI(int width, int height, const char* title=0)
{
    /* Main Window, control panel */
    Fl_Double_Window *panel = new Fl_Double_Window(width, height, title);
    panel->resizable(panel);
   
    // Add tool bar, it's width is equal to panel's
    ToolBar *tool = new ToolBar(0, 0, width, 34, (void*)panel);
    tool->clear_visible_focus(); //just use mouse, no TABs
    // protect buttons from resizing
    Fl_Box *r = new Fl_Box(FL_NO_BOX, width, tool->h(), 0, height-tool->h(), "right_border");
    r->hide();
    panel->resizable(r);

    /* Add simulator view */
    panel->show(); // glut will die unless parent window visible
    /* begin adding children */
    panel->begin(); 
    glutInitWindowSize(width-10, height-tool->h()-10);// be consistent with SimView_init
    glutInitWindowPosition(panel->x()+5, tool->h()+5); // place it inside parent window
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutCreateWindow("Simulation viewer");
    /* end adding children */
    panel->end();
    panel->resizable(glut_window);
    panel->callback(cb_close, &ws);
 
    // init RAOS simulation viewer
    RAOS_view_init(width-10, height-tool->h()-10);// pass gl window size
};
/* End of RAOS_UI.cxx */
