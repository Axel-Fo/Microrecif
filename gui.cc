#include "gui.h"

//les deux  classes ont besoin de pouvoir acceder a simulation
static Simulation _simulation;

static void orthographic_projection(const Cairo::RefPtr<Cairo::Context>& cr, 
									Frame frame);
// default Model Framing and window parameters
static Frame default_frame = {-1 ,dmax +2, -1, dmax +2, 1, 30, 30}; 

MyArea::MyArea() {
    setFrame(default_frame);
	set_content_width(default_frame.width);
	set_content_height(default_frame.height);
    set_draw_func(sigc::mem_fun(*this, &MyArea::on_draw));
}
MyArea::~MyArea() {}

static void orthographic_projection(const Cairo::RefPtr<Cairo::Context>& cr, 
								    Frame frame)
{
	// déplace l'origine au centre de la fenêtre
	cr->translate(frame.width/2, frame.height/2);
  
	// normalise la largeur et hauteur aux valeurs fournies par le cadrage
	// ET inverse la direction de l'axe Y
	cr->scale(frame.width/(frame.xMax - frame.xMin), 
             -frame.height/(frame.yMax - frame.yMin));
  
	// décalage au centre du cadrage
	cr->translate(-(frame.xMin + frame.xMax)/2, -(frame.yMin + frame.yMax)/2);
}
void MyArea::adjustFrame(int width, int height)
{
	frame.width  = width;
	frame.height = height;

	// Preventing distorsion by adjusting the frame (cadrage)
	// to have the same proportion as the graphical area
	
    // use the reference framing as a guide for preventing distortion
    double new_aspect_ratio((double)width/height);
    if( new_aspect_ratio > default_frame.asp)
    { // keep yMax and yMin. Adjust xMax and xMin
	    frame.yMax = default_frame.yMax ;
	    frame.yMin = default_frame.yMin ;	
	  
	    double delta(default_frame.xMax - default_frame.xMin);
	    double mid((default_frame.xMax + default_frame.xMin)/2);
        // the new frame is centered on the mid-point along X
	    frame.xMax = mid + 0.5*(new_aspect_ratio/default_frame.asp)*delta ;
	    frame.xMin = mid - 0.5*(new_aspect_ratio/default_frame.asp)*delta ;		  	  
    }
    else
    { // keep xMax and xMin. Adjust yMax and yMin
	    frame.xMax = default_frame.xMax ;
	    frame.xMin = default_frame.xMin ;
	  	  
 	    double delta(default_frame.yMax - default_frame.yMin);
	    double mid((default_frame.yMax + default_frame.yMin)/2);
        // the new frame is centered on the mid-point along Y
	    frame.yMax = mid + 0.5*(default_frame.asp/new_aspect_ratio)*delta ;
	    frame.yMin = mid - 0.5*(default_frame.asp/new_aspect_ratio)*delta ;		  	  
    }
}

void MyArea::setFrame(Frame f)
{
	if((f.xMin <= f.xMax) and (f.yMin <= f.yMax) and (f.height > 0))
	{
		f.asp = f.width/f.height;
		frame = f;
	}
	else
		std::cout << "incorrect Model framing or window parameters" << std::endl;
}

void MyArea::on_draw(const Cairo::RefPtr<Cairo::Context> &cr,
                     int width, int height)
{

    graphic_set_context(cr);
    adjustFrame(width, height);
    orthographic_projection(cr, frame); // set the transformation MODELE to GTKmm
    
    _simulation.affiche();
    dessin_carre(dmax/2,dmax/2, dmax + 1,gris,1);

}
void MyArea::refresh()
{
	queue_draw();
}
void distortion(){


}
MyWindow::MyWindow(Simulation& simulation):
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
    _simulation = simulation;
    set_title("Microrécif");
    set_child(m_main_box);
    set_default_size(500, 500);
	maj_info_box();

    // Box
	m_area.set_expand(true);
	m_main_box.append(m_control_box);
	m_main_box.append(m_area);
	m_control_box.append(m_button_box);
	m_control_box.append(m_info_box);
    //box a part pour le check button pour acitver les naissances
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
    //pour lier evenement bouton clické a la fonction
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
void MyWindow::maj_info_box()
{
	m_label_maj.set_text("mises à jour: " );// a faire;
	m_label_algues.set_text("algues: " + std::to_string(_simulation.getNbAlg()));
	m_label_corails.set_text("corails: " + std::to_string(_simulation.getNbCor()));
	m_label_charognards.set_text("charognards: " + std::to_string(_simulation.getNbSca()));
	
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
        ////
    }else{
        m_button_start_stop.set_label("start");
        ////
    }

}
void MyWindow::on_button_clicked_step()
{
    ///

}