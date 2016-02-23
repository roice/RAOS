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
#include <FL/Fl_Box.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Pixmap.H>
#include <FL/Fl_Tabs.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_PNG_Image.H>
/* OpenGL */
#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>
#include <FL/glut.H>
/* RAOS */
#include "SimUI.h"
#include "icons/icons.h" // pixmap icons used in Tool bar
#include "SimView.h" // 3D view of RAO



/*------- Class declarations -------*/
struct ToolBar_Widgets
{
    Fl_Button* start; // start button
    Fl_Button* pause; // pause button
    Fl_Button* stop; // stop button
    Fl_Button* config; // config button
    Fl_Light_Button* record; // record button
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

/*------- Creation function of User Interface  -------*/
SimUI::SimUI(int width, int height, const char* title=0)
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
    glutCreateWindow("Simulation view");
    /* end adding children */
    panel->end();
    panel->resizable(glut_window); 
 
    // config callbacks for glut
    // these functions will not be called immediately
    glutReshapeFunc(SimView_reshape);
    glutDisplayFunc(SimView_redraw);
    glutVisibilityFunc(SimView_visible);

    // init Sim view
    SimView_init(width-10, height-tool->h()-10);// pass gl window size
};

/*------- ToolBar -------*/
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
    Fl_Box *bar_rest = new Fl_Box(FL_DOWN_BOX, Xpos, Ypos, bar->w()-Xpos, Height, "rest");
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

/*------- Configuration Dialog -------*/
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

/* End of SimUI.cxx */
