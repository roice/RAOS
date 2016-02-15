/*
 * User Interface of Simulator
 *
 * Author: Roice (LUO Bing)
 * Date: 2016-02-01 create this file
 */

#include "SimUI.h"

/**********************************************************
 **************** Class declarations *********************/
struct ToolBar_Widgets
{
    Fl_Button* start; // start button
    Fl_Button* pause; // pause button
    Fl_Button* stop; // stop button
    Fl_Button* config; // config button
};
class ToolBar : public Fl_Group
{
public:
    ToolBar(int Xpos, int Ypos, int Width, int Height, void *win);
    struct ToolBar_Widgets tb_widgets;
    static void cb_button_start(Fl_Widget*, void*);
    static void cb_button_pause(Fl_Widget*, void*);
    static void cb_button_stop(Fl_Widget*, void*);
    static void cb_button_config(Fl_Widget*, void*);
};

class ConfigDlg : public Fl_Window
{
public:
    ConfigDlg(int xpos, int ypos, int width, int height, const char* title);
};

/**********************************************************
 **************** SimUI **********************************/
SimUI::SimUI(int width, int height, const char* title=0)
{
    /* Main Window, control panel */
    Fl_Double_Window *panel = new Fl_Double_Window(width, height, title);
    // Make the window resizable
    panel->resizable(panel);
    // Set color of window
    panel->color(FL_WHITE);
    /* begin adding children */
    panel->begin();

    // Add tool bar, it's width is equal to panel's
    ToolBar *tool = new ToolBar(0, 0, panel->w(), 30, (void*)panel);
    tool->clear_visible_focus(); //just use mouse, no TABs
    // Make menubar resizable
    panel->resizable(tool);

    panel->end();
    // Display the window
    panel->show();
};


/**********************************************************
 **************** Widgets Implementations ****************/

/******** ToolBar ********/


static const char *xpm_config[] = {
"16 16 9 1",
" c None",
". c #000000",
"+ c #0000FF",
"@ c #000080",
"# c #A0A0A0",
"$ c #0000C0",
"% c #FFFFFF",
"& c #C0C0FF",
"* c #DCDCDC",
"................",
".+@##########@+.",
".$@%%%%%%%%%%@$.",
".+@%%%%%%%%%%@+.",
".+@%########%@+.",
".+@%%%%%%%%%%@+.",
".+@%########%@+.",
".+@&%%%%%%%%&@+.",
".++@@@@@@@@@@++.",
".++++++++++++++.",
".++$......@@$++.",
".++.******.+@++.",
".++.*@+***.+@++.",
".++.*@+***.+@++.",
".@+.******.+@++.",
" ..............."};

void ToolBar::cb_button_start(Fl_Widget *w, void *data)
{
    fl_alert("Start Button pressed!");
}

void ToolBar::cb_button_pause(Fl_Widget *w, void *data)
{
    fl_alert("Pause Button pressed!");
}

void ToolBar::cb_button_stop(Fl_Widget *w, void *data)
{
    struct ToolBar_Widgets *widgets = (struct ToolBar_Widgets*)data;
    widgets->start->clear();
    widgets->pause->clear();
}

void ToolBar::cb_button_config(Fl_Widget *w, void *data)
{
    // Open Configuration dialog
    Fl_Window* window=(Fl_Window*)data;
    ConfigDlg *config = new ConfigDlg(window->x()+20, window->y()+20, 
            400, 400, "Settings");
}

ToolBar::ToolBar(int Xpos, int Ypos, int Width, int Height, void *win) :
Fl_Group(Xpos, Ypos, Width, Height)
{
    box(FL_UP_BOX);
    Ypos += 2; Height -= 4; Xpos += 3; Width = Height;
    // widgets of this toolbar
    //struct ToolBar_Widgets tb_widgets;
    // instances of buttons belong to tool bar
    tb_widgets.start = new Fl_Button(Xpos, Ypos, Width, Height); Xpos += Width + 5;
    tb_widgets.pause = new Fl_Button(Xpos, Ypos, Width, Height); Xpos += Width + 5;
    tb_widgets.stop = new Fl_Button(Xpos, Ypos, Width, Height); Xpos += Width + 5;
    tb_widgets.config = new Fl_Button(Xpos, Ypos, Width, Height); Xpos += Width + 5;
    // icons
    tb_widgets.start->label("@>"); // start icon
    tb_widgets.pause->label("@||"); // pause icon
    tb_widgets.stop->label("@square"); // stop icon
    Fl_PNG_Image* png = new Fl_PNG_Image("../share/icons/16x16/settings.png");
    //Fl_PNG_Image png("settings.png");
    // link icons to buttons
    tb_widgets.config->image(png);
    // tips for buttons
    tb_widgets.start->tooltip("Start Simulation");
    tb_widgets.pause->tooltip("Pause Simulation");
    tb_widgets.stop->tooltip("Stop Simulation");
    tb_widgets.config->tooltip("Settings");
    // types of buttons
    tb_widgets.start->type(FL_RADIO_BUTTON); // start & pause are mutually exclusive
    tb_widgets.pause->type(FL_RADIO_BUTTON);
    // link call backs to buttons
    tb_widgets.start->callback(cb_button_start);
    tb_widgets.pause->callback(cb_button_pause);
    //  start & pause buttons will be released when stop button is pressed
    tb_widgets.stop->callback(cb_button_stop, (void*)&tb_widgets);
    tb_widgets.config->callback(cb_button_config, (void*)win);
}

/******* Configuration Dialog *******/

void cb_tabs_ConfigDlg(Fl_Widget *w, void*)
{
    Fl_Tabs *tabs = (Fl_Tabs*)w;
    // When tab changed, make sure it has same color as its group
    tabs->selection_color( (tabs->value())->color() );
}

ConfigDlg::ConfigDlg(int xpos, int ypos, int width, int height, 
        const char* title=0):Fl_Window(xpos,ypos,width,height,title)
{
    // begin adding children
    begin();

    // Tabs
    Fl_Tabs *tabs = new Fl_Tabs(5, 5, w()-10, h()-10);
    {
        tabs->callback(cb_tabs_ConfigDlg); // callback func when switch tabs
        // Tab Flow
        Fl_Group *flow = new Fl_Group(20, 30, w()-10-20, h()-10-30,"Flow");
        {
            // color of this tab
            flow->color(9);
            flow->selection_color(9);
            /*
            Fl_Button *b1 = new Fl_Button(x(), y()+40, 90,25,"Button A1");
            b1->color(88+1);
            Fl_Button *b2 = new Fl_Button(x(), y()+70, 90,25,"Button A2");
            b2->color(88+2);
            Fl_Button *b3 = new Fl_Button(x(), y()+100, 90,25,"Button A3");
            b3->color(88+3);
            */
        }
        flow->end();
        // Tab Plume
        Fl_Group *plume = new Fl_Group(20, 30, w()-10-20, h()-10-30,"Plume");
        {
            // color of this tab
            plume->color(8);
            plume->selection_color(8);
        }
        plume->end();
    }
    // Make sure default tab has same color as its group
    tabs->selection_color( (tabs->value())->color() );
    tabs->end();
    
    end();
    show();
}
