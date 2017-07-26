#ifndef RAOS_UI_H
#define RAOS_UI_H

#include "FL/Fl_Widget.H"

struct RAOS_UI_Widgets {
    void*   toolbar;
};

class RAOS_UI
{
public:
    RAOS_UI(int width, int height, const char* title);
    RAOS_UI_Widgets ws;
private:
    static void cb_close(Fl_Widget *w, void *data);
};

#endif
