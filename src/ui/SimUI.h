#ifndef SimUI_H
#define SimUI_H

struct SimUI_Widgets {
    void*   toolbar;
};

class SimUI
{
public:
    SimUI(int width, int height, const char* title);
    SimUI_Widgets ws;
private:
    static void cb_close(Fl_Widget *w, void *data);
};

#endif
