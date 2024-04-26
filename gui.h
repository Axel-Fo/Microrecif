/*
* Fichier : gui.h
* Auteurs : Nestor Guibentif et Axel Fouet
* Version : V1
*/
#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED


#include <gtkmm/drawingarea.h>
#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/label.h>
#include <gtkmm/box.h>
#include <gtkmm/eventcontrollerkey.h>
#include <gtkmm/filechooserdialog.h>
#include <cairomm/context.h>
#include <glibmm/main.h>
#include <iostream>
#include <fstream>
#include <string>
#include "graphic_gui.h"
#include "simulation.h"

constexpr unsigned taille_dessin(500);

struct Frame { // Paramètres du modèle et de la fenêtre 
	double xMin; // frame parameters
	double xMax;
	double yMin;
	double yMax;
	double asp;  // rapport hauteur du cadre 
	int height;  
	int width;   
};

class MyArea : public Gtk::DrawingArea{
public:
    MyArea();
    virtual ~MyArea();
    void setFrame(Frame f); 
    void adjustFrame(int width, int height);
    void maj_drawing();

protected:
    void on_draw(const Cairo::RefPtr<Cairo::Context> &cr,int width, int height);
private:
    Frame frame;
};

class MyWindow : public Gtk::Window{
public:
    MyWindow(Simulation& simulation);
    void maj_info_box();
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

    //timer
    bool disconnect; //pour avoir l'etat du timer
    bool on_timeout();
    const int freq_timer; // en ms 
    //action des boutons et events clavier
    void on_button_clicked_exit();
	void on_button_clicked_open();
	void on_button_clicked_save();
	void on_button_clicked_start_stop();
	void on_button_clicked_step();

    bool on_window_key_pressed(guint keyval, guint keycode, Gdk::ModifierType state);
    
    //pour l'ouverture et l'enregistrement des fichiers :
    
    void on_file_dialog_response(int response_id, Gtk::FileChooserDialog* dialog);
    bool etat_save; //1 si on est en train de save, 0 sinon
};

#endif // GUI_H_INCLUDED