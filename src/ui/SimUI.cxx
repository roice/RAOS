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
#include <FL/Fl_Light_Button.H>
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
#include "ui/SimUI.h"
#include "ui/icons/icons.h" // pixmap icons used in Tool bar
#include "ui/SimView.h" // 3D RAO view
#include "SimConfig.h" // runtime RAOS configs
#include "SimRecord.h"

/*------- Configuration Dialog -------*/
struct ConfigDlg_widgets { // for parameter saving
    // arena widith/length/height
    Fl_Value_Input *arena_w;
    Fl_Value_Input *arena_l;
    Fl_Value_Input *arena_h;
    // source position xyz
    Fl_Value_Slider *source_x;
    Fl_Value_Slider *source_y;
    Fl_Value_Slider *source_z;
};
class ConfigDlg : public Fl_Window
{
public:
    ConfigDlg(int xpos, int ypos, int width, int height, const char* title);
private:
    // widgets
    struct ConfigDlg_widgets dlg_w;
    // callback funcs
    static void cb_dlg(Fl_Widget*, void*);
    static void cb_switch_tabs(Fl_Widget*, void*);
    static void cb_change_src_pos_bounds(Fl_Widget*, void*);
    // function to save current value of widgets to runtime configs
    static void save_value_to_configs(ConfigDlg_widgets*);
    // function to get runtime configs to set value of widgets
    static void set_value_from_configs(ConfigDlg_widgets*);
};

void ConfigDlg::cb_dlg(Fl_Widget* w, void* data) {
    if (Fl::event() == FL_CLOSE) {
        struct ConfigDlg_widgets *ws = (struct ConfigDlg_widgets*)data;
        // save widget values to RAOS runtime configs when closing the dialog window
        save_value_to_configs(ws);
        ((Fl_Window*)w)->hide();
    }
}

void ConfigDlg::cb_switch_tabs(Fl_Widget *w, void *data)
{
    Fl_Tabs *tabs = (Fl_Tabs*)w; 
    // When tab changed, make sure it has same color as its group
    tabs->selection_color( (tabs->value())->color() );
}

// change source position bounds according to arena size
void ConfigDlg::cb_change_src_pos_bounds(Fl_Widget* arena_wlh, void* src_xyz) {
    ((Fl_Value_Slider*)src_xyz)->minimum(-((Fl_Valuator*)arena_wlh)->value()/2.0);
    ((Fl_Value_Slider*)src_xyz)->maximum(((Fl_Valuator*)arena_wlh)->value()/2.0);
}

void ConfigDlg::save_value_to_configs(ConfigDlg_widgets* ws) {
    SimConfig_t* configs = SimConfig_get_configs(); // get runtime configs
    // save arena size
    configs->arena.w = ws->arena_w->value();
    configs->arena.l = ws->arena_l->value();
    configs->arena.h = ws->arena_h->value();
    // save source pos
    configs->source.x = ws->source_x->value();
    configs->source.y = ws->source_y->value();
    configs->source.z = ws->source_z->value();
}

void ConfigDlg::set_value_from_configs(ConfigDlg_widgets* ws) {
    SimConfig_t* configs = SimConfig_get_configs(); // get runtime configs
    // set arena size
    ws->arena_w->value(configs->arena.w);
    ws->arena_l->value(configs->arena.l);
    ws->arena_h->value(configs->arena.h);
    // set source pos & maximum
    ws->source_x->value(configs->source.x);
    ws->source_y->value(configs->source.y);
    ws->source_z->value(configs->source.z);
    ws->source_x->minimum(-configs->arena.w/2.0);
    ws->source_y->minimum(-configs->arena.l/2.0);
    ws->source_z->minimum(-configs->arena.h/2.0);
    ws->source_x->maximum(configs->arena.w/2.0);
    ws->source_y->maximum(configs->arena.l/2.0);
    ws->source_z->maximum(configs->arena.h/2.0);
}

ConfigDlg::ConfigDlg(int xpos, int ypos, int width, int height, 
        const char* title=0):Fl_Window(xpos,ypos,width,height,title)
{
    // add event handle to dialog window
    callback(cb_dlg, (void*)&dlg_w);   
    // begin adding children
    begin();
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
            Fl_Box *arena = new Fl_Box(t_x+10, t_y+25+10, 180, 130,"Arena");
            arena->box(FL_PLASTIC_UP_FRAME);
            arena->labelsize(16);
            arena->labelfont(FL_COURIER_BOLD_ITALIC);
            arena->align(Fl_Align(FL_ALIGN_TOP|FL_ALIGN_INSIDE));
            // Arena width/length/height
            dlg_w.arena_w = new Fl_Value_Input(t_x+10+60,t_y+25+10+30,80,25,"Width");
            dlg_w.arena_l = new Fl_Value_Input(t_x+10+60,t_y+25+10+60,80,25,"Length");
            dlg_w.arena_h = new Fl_Value_Input(t_x+10+60,t_y+25+10+90,80,25,"Height");
            new Fl_Box(t_x+10+60+80,t_y+25+10+30, 20, 25, "m");
            new Fl_Box(t_x+10+60+80,t_y+25+10+60, 20, 25, "m");
            new Fl_Box(t_x+10+60+80,t_y+25+10+90, 20, 25, "m");
            // Source
            Fl_Box *source = new Fl_Box(t_x+10+190, t_y+25+10, 180, 130,"Source Position");
            source->box(FL_PLASTIC_UP_FRAME);
            source->labelsize(16);
            source->labelfont(FL_COURIER_BOLD_ITALIC);
            source->align(Fl_Align(FL_ALIGN_TOP|FL_ALIGN_INSIDE));
            // Source pos
            dlg_w.source_x = new Fl_Value_Slider(t_x+10+210,t_y+25+10+30,140,25,"X");
            dlg_w.source_y = new Fl_Value_Slider(t_x+10+210,t_y+25+10+60,140,25,"Y");
            dlg_w.source_z = new Fl_Value_Slider(t_x+10+210,t_y+25+10+90,140,25,"Z");
            dlg_w.source_x->labelsize(16);
            dlg_w.source_y->labelsize(16);
            dlg_w.source_z->labelsize(16);
            dlg_w.source_x->type(FL_HOR_NICE_SLIDER);
            dlg_w.source_y->type(FL_HOR_NICE_SLIDER);
            dlg_w.source_z->type(FL_HOR_NICE_SLIDER);
            dlg_w.source_x->align(Fl_Align(FL_ALIGN_LEFT));
            dlg_w.source_y->align(Fl_Align(FL_ALIGN_LEFT));
            dlg_w.source_z->align(Fl_Align(FL_ALIGN_LEFT));
            new Fl_Box(t_x+10+210+140,t_y+25+10+30, 20, 25, "m");
            new Fl_Box(t_x+10+210+140,t_y+25+10+60, 20, 25, "m");
            new Fl_Box(t_x+10+210+140,t_y+25+10+90, 20, 25, "m");
            dlg_w.arena_w->callback(cb_change_src_pos_bounds, (void*)dlg_w.source_x);
            dlg_w.arena_l->callback(cb_change_src_pos_bounds, (void*)dlg_w.source_y);
            dlg_w.arena_h->callback(cb_change_src_pos_bounds, (void*)dlg_w.source_z);
        }
        scenario->end();
        // Tab Flow
        Fl_Group *flow = new Fl_Group(t_x,t_y+25,t_w,t_h-25,"Flow");
        {
            // color of this tab
            flow->color(0xe0ffff00); // light blue
            flow->selection_color(0xe0ffff00); // light blue

            // Mean wind velocity
            Fl_Box *m_wind = new Fl_Box(t_x+10, t_y+25+10, 370, 130,"Mean Wind Vel");
            m_wind->box(FL_PLASTIC_UP_FRAME);
            m_wind->labelsize(16);
            m_wind->labelfont(FL_COURIER_BOLD_ITALIC);
            m_wind->align(Fl_Align(FL_ALIGN_TOP|FL_ALIGN_INSIDE));
            // Mean wind velocity x/y/z components
            Fl_Value_Slider *m_wind_x = new Fl_Value_Slider(t_x+10+30,t_y+25+10+30,300,25,"X");
            Fl_Value_Slider *m_wind_y = new Fl_Value_Slider(t_x+10+30,t_y+25+10+60,300,25,"Y");
            Fl_Value_Slider *m_wind_z = new Fl_Value_Slider(t_x+10+30,t_y+25+10+90,300,25,"Z");
            m_wind_x->labelsize(16);
            m_wind_y->labelsize(16);
            m_wind_z->labelsize(16);
            m_wind_x->type(FL_HOR_NICE_SLIDER);
            m_wind_y->type(FL_HOR_NICE_SLIDER);
            m_wind_z->type(FL_HOR_NICE_SLIDER);
            m_wind_x->align(Fl_Align(FL_ALIGN_LEFT));
            m_wind_y->align(Fl_Align(FL_ALIGN_LEFT));
            m_wind_z->align(Fl_Align(FL_ALIGN_LEFT));
            m_wind_x->bounds(0, 10); // 0~10 m/s
            m_wind_y->bounds(0, 10);
            m_wind_z->bounds(0, 10);
            new Fl_Box(t_x+10+30+300,t_y+25+10+30, 30, 25, "m/s");
            new Fl_Box(t_x+10+30+300,t_y+25+10+60, 30, 25, "m/s");
            new Fl_Box(t_x+10+30+300,t_y+25+10+90, 30, 25, "m/s");
        }
        flow->end();
        // Tab Plume
        Fl_Group *plume = new Fl_Group(t_x,t_y+25,t_w,t_h-25,"Plume");
        {
            // color of this tab
            plume->color(0xeeee0000); // light yellow+green (chlorine)
            plume->selection_color(0xeeee0000); // light yellow+green
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

/* =================================================
 * ==== Robot panel (state viewer & controller) ====
 * =================================================*/
struct RobotPanel_Widgets { // for parameter saving
    Fl_Choice*      robot_to_display_sensor_reading; // choose which robot's reading to display
    WavePlot*      robot_sensor_reading; // reading of sensors
};
struct RobotPanel_handles {
};
class RobotPanel : public Fl_Window
{
public:
    RobotPanel(int xpos, int ypos, int width, int height, const char* title);
    static Fl_Button*  robot_button; // contain the handle of the button which open this panel in its callback
    // widgets
    struct RobotPanel_Widgets ws;
    static struct RobotPanel_handles hs;
private:
    // callback funcs
    static void cb_close(Fl_Widget*, void*);
    static void cb_robot_rc_button(Fl_Widget*, void*);
    // function to save current value of widgets to runtime configs
    static void save_value_to_configs(RobotPanel_Widgets*);
    // function to get runtime configs to set value of widgets
    static void get_value_from_configs(RobotPanel_Widgets*);
};
Fl_Button* RobotPanel::robot_button = NULL;
struct RobotPanel_handles RobotPanel::hs = {NULL};
void RobotPanel::cb_close(Fl_Widget* w, void* data) {
    if (Fl::event() == FL_CLOSE) {
        ((Fl_Window*)w)->hide();
        // and release the robot button in toolbar
        if (robot_button != NULL)
            robot_button->value(0);
    }
}
void RobotPanel::cb_robot_rc_button(Fl_Widget* w, void* data) {
    if (hs.remoter_panel != NULL) {
        if (hs.remoter_panel->shown()) {
            if (!((Fl_Button*)w)->value()) {
                hs.remoter_panel->hide();
            }
        }
        else {
            if (((Fl_Button*)w)->value()) {
                hs.remoter_panel->show();
            }
        }
    }
    else // first press this button
    {// create config dialog
        if (((Fl_Button*)w)->value()) // if pressed
        {
            Fl_Window* window = w->window(); // find the nearest parent window of this button, i.e., RobotPanel
            hs.remoter_panel = new RemoterPanel(window->x()+window->w(), window->y(), 
                300, window->h(), "RC Control");
            hs.remoter_panel->remoter_button = (Fl_Button*)w;
        }
    }
}
void RobotPanel::get_value_from_configs(RobotPanel_Widgets* ws) {
    GSRAO_Config_t* configs = GSRAO_Config_get_configs(); // get runtime configs
    
    // check whether to open remoter panel or not
    if (configs->system.remoter_panel_opened) {
        // open remoter panel
        Fl_Window* window = ws->robot_rc_button->window();
        hs.remoter_panel = new RemoterPanel(window->x()+window->w(), window->y(), 
                300, window->h(), "RC Control");
        hs.remoter_panel->remoter_button = ws->robot_rc_button;
        ws->robot_rc_button->value(1);
    }
}
RobotPanel::RobotPanel(int xpos, int ypos, int width, int height, 
        const char* title=0):Fl_Window(xpos,ypos,width,height,title)
{
    GSRAO_Config_t* configs = GSRAO_Config_get_configs(); // get runtime configs

    // add event handle to dialog window
    callback(cb_close, (void*)&ws);   
    // begin adding children
    begin();
    int t_x = 5, t_y = 5, t_w = w()-10, t_h = h()-10;
    //  robot link state, Note: only check data network (data receiving)
    Fl_Box *link = new Fl_Box(t_x, t_y, 220, 160, "Robot State");
        link->box(FL_PLASTIC_UP_FRAME);
        link->labelsize(15);
        link->labelfont(FL_COURIER_BOLD_ITALIC);
        link->align(Fl_Align(FL_ALIGN_TOP|FL_ALIGN_INSIDE));
    {
        // LED indicating data link state
        new Fl_Box(t_x, t_y+20, 80, 25, "Data Link");
        const char* robot_name[] = {"#1", "#2", "#3", "#4"};
        for (char i = 0; i < 4; i++) // 4 robots max
        {
            ws.robot_link_state[i] = new Fl_LED_Button(t_x+30, t_y+40+30*i, 30, 30, robot_name[i]);
            ws.robot_link_state[i]->selection_color(FL_DARK_GREEN);
            ws.robot_link_state[i]->labelsize(13);
            ws.robot_link_state[i]->align(Fl_Align(FL_ALIGN_LEFT)); 
        }
        // ARM/DISARM info
        new Fl_Box(t_x+90, t_y+20, 60, 25, "ARMING");
        for (char i = 0; i < 4; i++) // 4 robots max
        {
            ws.robot_arm_state[i] = new Fl_Box(t_x+90, t_y+40+30*i, 60, 25, "DISARM");
            ws.robot_arm_state[i]->labelcolor(FL_RED);
        }
        // Battery status
        new Fl_Box(t_x+160, t_y+20, 60, 25, "Battery");
        for (char i = 0; i < 4; i++) // 4 robots max
        {
            ws.robot_bat_state[i] = new Fl_Box(t_x+150, t_y+40+30*i, 60, 25, "0 V");
            ws.robot_bat_state[i]->labelcolor(FL_RED);
        }
    }
    //  robot remote control
    ws.robot_rc_button = new Fl_Button(t_x, t_y+40+30*4, 34, 34);
    Fl_Pixmap *icon_rc = new Fl_Pixmap(pixmap_icon_rc);
    ws.robot_rc_button->image(icon_rc);
    ws.robot_rc_button->tooltip("Robot remote controller, please use with care.");
    ws.robot_rc_button->type(FL_TOGGLE_BUTTON);
    ws.robot_rc_button->callback(cb_robot_rc_button);
    new Fl_Box(t_x+40, t_y+40+30*4, 120, 30, "");

    // robot choice to display sensor reading
    ws.robot_to_display_sensor_reading = new Fl_Choice(t_x+40, t_y+40+30*4+2, 180, 30);
    ws.robot_to_display_sensor_reading->add("Show sensors robot 1");
    ws.robot_to_display_sensor_reading->add("Show sensors robot 2");
    ws.robot_to_display_sensor_reading->add("Show sensors robot 3");
    ws.robot_to_display_sensor_reading->add("Show sensors robot 4");
    ws.robot_to_display_sensor_reading->value(0);

    // sensor reading plot
    Fl_Box* sr_box = new Fl_Box(t_x+225, t_y, 465, 190, "Sensor reading");
    sr_box->box(FL_PLASTIC_UP_FRAME);
    sr_box->labelsize(15);
    sr_box->labelfont(FL_COURIER_BOLD_ITALIC);
    sr_box->align(Fl_Align(FL_ALIGN_TOP|FL_ALIGN_INSIDE));
    {
        Fl_Scroll* scroll = new Fl_Scroll(t_x+230, t_y+25, 455, 165);
        ws.robot_sensor_reading = new WavePlot(t_x+230, t_y+25, 455*10, 140, ""); // *10 means 10 min length of data 
        scroll->end();
    }

    end();

    // set values from configs
    get_value_from_configs(&ws);

    show();
}

/* ================================
 * ========= Result Panel =========
 * ================================*/
struct ResultPanel_Widgets { // for parameter saving
};
struct ResultPanel_handles {
};
class ResultPanel : public Fl_Window
{
public:
    ResultPanel(int xpos, int ypos, int width, int height, const char* title);
    static Fl_Button*  result_button; // contain the handle of the button which open this panel in its callback
    // widgets
    struct ResultPanel_Widgets ws;
    static struct ResultPanel_handles hs;
private:
    // callback funcs
    static void cb_close(Fl_Widget*, void*);
    // function to save current value of widgets to runtime configs
    static void save_value_to_configs(ResultPanel_Widgets*);
    // function to get runtime configs to set value of widgets
    static void get_value_from_configs(ResultPanel_Widgets*);
};
Fl_Button* ResultPanel::result_button = NULL;
//struct ResultPanel_handles ResultPanel::hs = {NULL};
void ResultPanel::cb_close(Fl_Widget* w, void* data) {
    if (Fl::event() == FL_CLOSE) {
        ((Fl_Window*)w)->hide();
        // and release the result button in toolbar
        if (result_button != NULL)
            result_button->value(0);
    }
}
void ResultPanel::get_value_from_configs(ResultPanel_Widgets* ws) {
    SimConfig_t* configs = SimConfig_get_configs(); // get runtime configs
}
ResultPanel::ResultPanel(int xpos, int ypos, int width, int height, 
        const char* title=0):Fl_Window(xpos,ypos,width,height,title)
{
    SimConfig_t* configs = SimConfig_get_configs(); // get runtime configs

    // add event handle to dialog window
    callback(cb_close, (void*)&ws);   
    // begin adding children
    begin();
    int t_x = 5, t_y = 5, t_w = w()-10, t_h = h()-10;
    
    end();

    // set values from configs
    get_value_from_configs(&ws);

    show();
}

/* ================================
 * ========= ToolBar ==============
 * ================================*/
struct ToolBar_Widgets
{
    Fl_Button* start; // start button
    Fl_Button* pause; // pause button
    Fl_Button* stop; // stop button
    Fl_Button* config; // config button
    Fl_Light_Button* record; // record button
    Fl_Button*  robot;  // robot state&control button
    Fl_Button*  result; // result display button
    Fl_Box*     msg_zone; // message zone
};
struct ToolBar_Handles // handles of dialogs/panels opened by corresponding buttons
{
    ConfigDlg* config_dlg; // handle of config dialog opened by config button
    RobotPanel* robot_panel; // handle of robot panel opened by robot button
    ResultPanel* result_panel; // handle of result panel opened by result button
};
class ToolBar : public Fl_Group
{
public:
    ToolBar(int Xpos, int Ypos, int Width, int Height, void *win);
    struct ToolBar_Widgets ws;
    static struct ToolBar_Handles hs;
    void restore_from_configs(ToolBar_Widgets* void*);
private:
    static void cb_button_start(Fl_Widget*, void*);
    static void cb_button_pause(Fl_Widget*, void*);
    static void cb_button_stop(Fl_Widget*, void*);
    static void cb_button_config(Fl_Widget*, void*);
    static void cb_button_robot(Fl_Widget*, void*);
    static void cb_button_result(Fl_Widget*, void*);
};
struct ToolBar_Handles ToolBar::hs = {NULL, NULL, NULL};

/* ------- Repeated Tasks -------- */
static void cb_repeated_tasks_10hz(void* data)
{
    ToolBar_Handles* hs = (ToolBar_Handles*)data;

    // draw sensor reading
    if (hs->robot_panel != NULL && hs->robot_panel->shown())
    {
        hs->robot_panel->ws.robot_sensor_reading->redraw();
    }

    // reload
    Fl::repeat_timeout(0.1, cb_repeated_tasks_10hz, data);
}

void ToolBar::cb_button_start(Fl_Widget *w, void *data)
{
    SimConfig_t* configs = SimConfig_get_configs(); // get runtime configs

    ToolBar_Widgets* widgets = (ToolBar_Widgets*)data;

    // if pause button is pressed, meaning that the initialization has been carried out, so just restore and continue
    if (widgets->pause->value()) {
        // release pause button
        widgets->pause->activate(); widgets->pause->clear();
        // continue running
        
    }
    else {
    // if pause button is not pressed, then need check start button state
        if (((Fl_Button*)w)->value()) // if start button is pressed down
        {
            // lock config button
            widgets->config->deactivate();
            widgets->msg_zone->label(""); // clear message zone
            // clear robot record
            std::vector<Robot_Record_t>* robot_rec = robot_get_record();
            for (int i = 0; i < 4; i++) // 4 robots max
                robot_rec[i].clear();
        
            // Init RAO task
            //if (!method_start(METHOD_HOVER_MEASURE)) // start hover measure task
            if (!method_start(METHOD_BACK_FORTH_MEASURE)) // start back-forth measure task
            {
                widgets->msg_zone->label("Method start failed!");
                widgets->msg_zone->labelcolor(FL_RED);
                ((Fl_Button*)w)->value(0);
                // TODO: shutdown robots

                return;
            }
            // add timers for repeated tasks (such as data display)
            Fl::add_timeout(0.1, cb_repeated_tasks_10hz, (void*)&hs);
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
    // if start button pressed, release it, and pause experiment
    if (widgets->start->value()) {
        widgets->start->value(0); // release start button
        widgets->pause->deactivate(); // make pause button unclickable
        // pause experiment...

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

    // TODO: shutdown RAO tasks and robots
    Fl::remove_timeout(cb_repeated_tasks_10hz); // remove timeout callback for repeated tasks

    // clear message zone
    widgets->msg_zone->label("");
    // unlock config button
    widgets->config->activate();

    /* Save data */
    SimSaveData();
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
void ToolBar::cb_button_robot(Fl_Widget *w, void *data)
{
    if (hs.robot_panel != NULL)
    {
        if (hs.robot_panel->shown()) { // if shown, do not open again
            if (!((Fl_Button*)w)->value())
                hs.robot_panel->hide();
        }
        else {
            if (((Fl_Button*)w)->value())
                hs.robot_panel->show();
        }
    }
    else // first press this button
    {// create config dialog
        if (((Fl_Button*)w)->value()) // if pressed
        {
            Fl_Window* window=(Fl_Window*)data;
            hs.robot_panel = new RobotPanel(window->x(), window->y()+window->h()+40, 
                window->w(), 200, "Robot Panel");
            hs.robot_panel->robot_button = (Fl_Button*)w;
        }
    }
}
void ToolBar::cb_button_result(Fl_Widget *w, void *data)
{
    if (hs.result_panel != NULL)
    {
        if (hs.result_panel->shown()) { // if shown, do not open again
            if (!((Fl_Button*)w)->value())
                hs.result_panel->hide();
        }
        else {
            if (((Fl_Button*)w)->value())
                hs.result_panel->show();
        }
    }
    else // first press this button
    {// create config dialog
        if (((Fl_Button*)w)->value()) // if pressed
        {
            Fl_Window* window=(Fl_Window*)data;
            hs.result_panel = new ResultPanel(window->x()+window->w(), window->y(), 
                200, window->h(), "Result Panel");
            hs.result_panel->result_button = (Fl_Button*)w;
        }
    }
}
void ToolBar::restore_from_configs(ToolBar_Widgets* ws, void *data)
{
    SimConfig_t* configs = SimConfig_get_configs(); // get runtime configs

    // check whether to open robot panel or not
    if (configs->system.robot_panel_opened) {
        Fl_Window* window = (Fl_Window*)data;
        hs.robot_panel = new RobotPanel(window->x(), window->y()+window->h()+40, 
            window->w(), 200, "Robot Panel");
        hs.robot_panel->robot_button = ws->robot;
        ws->robot->value(1);
    }
    // check whether to open result panel or not
    if (configs->system.result_panel_opened) {
        Fl_Window* window = (Fl_Window*)data;
        hs.result_panel = new ResultPanel(window->x()+window->w(), window->y(), 
                200, window->h(), "Result Panel");
        hs.result_panel->result_button = ws->result;
        ws->result->value(1);
    }
}

ToolBar::ToolBar(int Xpos, int Ypos, int Width, int Height, void *win) :
Fl_Group(Xpos, Ypos, Width, Height)
{
    begin();
    Fl_Box *bar = new Fl_Box(FL_UP_BOX, 0, 0, Width, Height, "");
    Ypos += 2; Height -= 4; Xpos += 3; Width = Height;
    // widgets of this toolbar
    //struct ToolBar_Widgets tb_widgets;
    // instances of buttons belong to tool bar
    tb_widgets.start = new Fl_Button(Xpos, Ypos, Width, Height); Xpos += Width + 5;
    tb_widgets.pause = new Fl_Button(Xpos, Ypos, Width, Height); Xpos += Width + 5;
    tb_widgets.stop = new Fl_Button(Xpos, Ypos, Width, Height); Xpos += Width + 5;
    tb_widgets.config = new Fl_Button(Xpos, Ypos, Width, Height); Xpos += Width + 5;
    tb_widgets.record = new Fl_Light_Button(Xpos, Ypos, Width+22, Height); Xpos += Width+22+5;
    ws.robot = new Fl_Button(Xpos, Ypos, Width, Height); Xpos += Width + 5;
    ws.result = new Fl_Button(Xpos, Ypos, Width, Height); Xpos += Width + 5;
    ws.msg_zone = new Fl_Box(FL_DOWN_BOX, Xpos, Ypos, bar->w()-Xpos, Height, "");
    ws.msg_zone->align(Fl_Align(FL_ALIGN_CENTER|FL_ALIGN_INSIDE));
    resizable(ws.msg_zone); // protect buttons from resizing
    Fl_Box *bar_rest = new Fl_Box(FL_DOWN_BOX, Xpos, Ypos, bar->w()-Xpos, Height, "");
    resizable(bar_rest); // protect buttons from resizing
    // icons
    Fl_Pixmap *icon_start = new Fl_Pixmap(pixmap_icon_play);
    Fl_Pixmap *icon_pause = new Fl_Pixmap(pixmap_icon_pause);
    Fl_Pixmap *icon_stop = new Fl_Pixmap(pixmap_icon_stop);
    Fl_Pixmap *icon_config = new Fl_Pixmap(pixmap_icon_config);
    Fl_Pixmap *icon_record = new Fl_Pixmap(pixmap_icon_record);
    // link icons to buttons
    tb_widgets.start->image(icon_start);
    tb_widgets.pause->image(icon_pause);
    tb_widgets.stop->image(icon_stop);
    tb_widgets.config->image(icon_config);
    tb_widgets.record->image(icon_record);
    // tips for buttons
    tb_widgets.start->tooltip("Start Simulation");
    tb_widgets.pause->tooltip("Pause Simulation");
    tb_widgets.stop->tooltip("Stop Simulation");
    tb_widgets.config->tooltip("Settings");
    tb_widgets.record->tooltip("Recording");
    // types of buttons
    tb_widgets.start->type(FL_RADIO_BUTTON); // start & pause are mutually exclusive
    tb_widgets.pause->type(FL_RADIO_BUTTON);
    // colors
    tb_widgets.record->selection_color(FL_RED);
    // link call backs to buttons
    tb_widgets.start->callback(cb_button_start);
    tb_widgets.pause->callback(cb_button_pause);
    //  start & pause buttons will be released when stop button is pressed
    tb_widgets.stop->callback(cb_button_stop, (void*)&tb_widgets);
    tb_widgets.config->callback(cb_button_config, (void*)win);
    end();
}

/* =========================================
 * ================= UI ====================
 * =========================================*/
void SimUI::cb_close(Fl_Widget* w, void* data) { 
    // close RAOS
    if (Fl::event() == FL_CLOSE) {
        // TODO: shutdown RAO tasks and robots
        Fl::remove_timeout(cb_repeated_tasks_10hz); // remove timeout callback for repeated tasks

        // save open/close states of other sub-panels to configs
        SimConfig_t* configs = SimConfig_get_configs(); // get runtime configs
        SimUI_Widgets* ws = (SimUI_Widgets*)data;
        if (((ToolBar*)ws->toolbar)->hs.robot_panel != NULL) { // robot panel
            if (((ToolBar*)ws->toolbar)->hs.robot_panel->shown())
                configs->system.robot_panel_opened = true;
            else
                configs->system.robot_panel_opened = false;
        }
        if (((ToolBar*)ws->toolbar)->hs.result_panel != NULL) { // result panel
            if (((ToolBar*)ws->toolbar)->hs.result_panel->shown())
                configs->system.result_panel_opened = true;
            else
                configs->system.result_panel_opened = false;
        }

        // close other panels
        if (((ToolBar*)ws->toolbar)->hs.config_dlg != NULL && ((ToolBar*)ws->toolbar)->hs.config_dlg->shown()) // close config dialog
            ((ToolBar*)ws->toolbar)->hs.config_dlg->hide();
        if (((ToolBar*)ws->toolbar)->hs.robot_panel != NULL && ((ToolBar*)ws->toolbar)->hs.robot_panel->shown()) // close robot panel
            ((ToolBar*)ws->toolbar)->hs.robot_panel->hide();
        if (((ToolBar*)ws->toolbar)->hs.result_panel != NULL && ((ToolBar*)ws->toolbar)->hs.result_panel->shown()) // close result panel
            ((ToolBar*)ws->toolbar)->hs.result_panel->hide();

        // close main window
        ((Fl_Window*)w)->hide();
    }
}

/*------- Creation function of User Interface  -------*/
SimUI::SimUI(int width, int height, const char* title=0)
{
    /* Main Window, control panel */
    Fl_Double_Window *panel = new Fl_Double_Window(width, height, title);
    panel->resizable(panel); 

    /* Add simulator view */
    panel->show(); // glut will die unless parent window visible
    /* begin adding children */
    panel->begin();
    // Add tool bar, it's width is equal to panel's
    ToolBar *tool = new ToolBar(0, 0, width, 34, (void*)panel);
    ws.toolbar = tool;
    tool->clear_visible_focus(); //just use mouse, no TABs
    // protect buttons from resizing
    Fl_Box *r = new Fl_Box(FL_NO_BOX, width, tool->h(), 0, height-tool->h(), "right_border");
    r->hide();
    panel->resizable(r);
    /* Add RAO view */
    glutInitWindowSize(width-10, height-tool->h()-10);// be consistent with SimView_init
    glutInitWindowPosition(panel->x()+5, tool->h()+5); // place it inside parent window
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutCreateWindow("Simulation view");
    /* end adding children */
    panel->end();
    panel->resizable(glut_window);
    panel->callback(cb_close, &ws); // callback
 
    // init Sim view
    SimView_init(width-10, height-tool->h()-10);// pass gl window size

    // open panels according to last use info
    tool->restore_from_configs(&(tool->ws), (void*)ui);
};
/* End of SimUI.cxx */
