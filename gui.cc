#include "gui.h"


MyArea::MyArea() {

    set_draw_func(sigc::mem_fun(*this, &MyArea::on_draw));
}
MyArea::~MyArea() {}

void MyArea::on_draw(const Cairo::RefPtr<Cairo::Context> &cr,
                     int width, int height)
{


    cr->set_source_rgb(0.0, 0.0, 0.0); 
    cr->paint();
    int min;
 

}
void MyArea::refresh()
{
	queue_draw();
}
void distortion(){


}
MyWindow::MyWindow():
    m_main_box(Gtk::Orientation::HORIZONTAL,2),
    m_control_box(Gtk::Orientation::VERTICAL,2),
    m_button_box(Gtk::Orientation::VERTICAL,2),
    m_naissance_box(Gtk::Orientation::HORIZONTAL,2),
    m_info_box(Gtk::Orientation::VERTICAL,2),
    
	m_label_subtitle("General"),
	m_button_exit("exit"),m_button_open("open"),
	m_button_save("save"),m_button_start_stop("start"),
	m_button_step("step"),
    m_label_naissance("Naissance d'algue"),

	m_label_info_subtitle("Info : nombre de ..."),
	m_label_maj("mises à jour: "),
    m_label_algues("algues: "),
    m_label_corails("corails: "),
    m_label_charognards("charognards: ")
{
    set_title("Microrécif");
    set_child(m_main_box);
    set_default_size(500, 500);

    	// Box
	m_area.set_expand(true);
	m_main_box.append(m_control_box);
	m_main_box.append(m_area);
	m_control_box.append(m_button_box);
	m_control_box.append(m_info_box);
    m_naissance_box.append(m_check_button_naissance);
    m_naissance_box.append(m_label_naissance);

	// Ajoute les boutons dans leur box
	m_button_box.append(m_label_subtitle);
	m_button_box.append(m_button_exit);
	m_button_box.append(m_button_open);
	m_button_box.append(m_button_save);
	m_button_box.append(m_button_start_stop);
	m_button_box.append(m_button_step);
    m_button_box.append(m_naissance_box);

    m_button_exit.signal_clicked().connect(sigc::mem_fun(*this, &MyWindow::on_button_clicked_exit));
    m_button_open.signal_clicked().connect(sigc::mem_fun(*this, &MyWindow::on_button_clicked_open));
	m_button_save.signal_clicked().connect(sigc::mem_fun(*this, &MyWindow::on_button_clicked_save));
	m_button_start_stop.signal_clicked().connect(sigc::mem_fun(*this, &MyWindow::on_button_clicked_start_stop));
	m_button_step.signal_clicked().connect(sigc::mem_fun(*this, &MyWindow::on_button_clicked_step));
    
    m_info_box.append(m_label_info_subtitle);
	m_info_box.append(m_label_maj);
    m_info_box.append(m_label_algues);
    m_info_box.append(m_label_corails);
    m_info_box.append(m_label_charognards);
}
void MyWindow::on_button_clicked_exit()
{
    exit(EXIT_SUCCESS);

}  

void MyWindow::on_button_clicked_open()
{
    ///

} 

void MyWindow::on_button_clicked_save()
{
    ///

} 
void MyWindow::on_button_clicked_start_stop()
{
    std::string boutonEtat = m_button_start_stop.get_label();

    if(boutonEtat == "start"){
        m_button_start_stop.set_label("stop");
        m_area.refresh();
        ////
    }else{
        m_button_start_stop.set_label("start");

    }

}
void MyWindow::on_button_clicked_step()
{
    ///

}