#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED
#include <gtkmm/drawingarea.h>
#include <gtkmm/window.h>
class MyWindow : public Gtk::Window
{
public:
MyWindow();
};

class MyArea : public Gtk::DrawingArea
{
public:
    MyArea();
    virtual ~MyArea();

protected:
    // Override default signal handler:
    void on_draw(const Cairo::RefPtr<Cairo::Context> &cr,
                 int width, int height);
};
#endif // GUI_H_INCLUDED