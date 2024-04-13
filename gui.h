#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED
#include <gtkmm/drawingarea.h>
#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/label.h>
#include <gtkmm/box.h>
#include <cairomm/context.h>
#include <iostream>
#include <string>
#include "graphic_gui.h"

class MyArea : public Gtk::DrawingArea
{
public:
    MyArea();
    virtual ~MyArea();
    void refresh();

protected:
    // Override default signal handler:
    void on_draw(const Cairo::RefPtr<Cairo::Context> &cr,int width, int height);
};

class MyWindow : public Gtk::Window
{
public:
    MyWindow();
protected:
    MyArea m_area;
    // Box
    Gtk::Box m_main_box;
    Gtk::Box m_control_box;
    Gtk::Box m_button_box;
    Gtk::Box m_naissance_box;
    Gtk::Box m_info_box;

    // Button widgets de button_box et titre des bouttons:
    Gtk::Label m_label_subtitle;
    Gtk::Button m_button_exit;
    Gtk::Button m_button_open;
    Gtk::Button m_button_save;
    Gtk::Button m_button_start_stop;
    Gtk::Button m_button_step;
    Gtk::Label m_label_naissance;
    Gtk::CheckButton m_check_button_naissance;

    // Label de info box:
    Gtk::Label m_label_info_subtitle;
    Gtk::Label m_label_maj;
    Gtk::Label m_label_algues;
    Gtk::Label m_label_corails;
    Gtk::Label m_label_charognards;

    //action des boutons
    void on_button_clicked_exit();
	void on_button_clicked_open();
	void on_button_clicked_save();
	void on_button_clicked_start_stop();
	void on_button_clicked_step();
};





#endif // GUI_H_INCLUDED