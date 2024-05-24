/*
* Fichier : gui.cc
* Auteurs : Nestor Guibentif(~40) et Axel Fouet(~60)
* Version : V3
*/
#include "gui.h"

using namespace std;


//les deux  classes ont besoin de pouvoir accéder à simulation le plus simple est de 
//mettre notre simulation en static
static Simulation _simulation;

static void orthographic_projection(const Cairo::RefPtr<Cairo::Context>& cr, 
									Frame frame); 

// Frame par defaut et paramètres de la fenêtre
static Frame default_frame = {-1 ,dmax +2, -1, dmax +2, 1, 
	                          taille_dessin, taille_dessin}; 


//Classe MyArea.......................................................................


static void orthographic_projection(const Cairo::RefPtr<Cairo::Context>& cr, 
								    Frame frame){
	
	// déplace l'origine au centre de la fenêtre
	cr->translate(frame.width/2, frame.height/2);
  
	// normalise la largeur et hauteur aux valeurs fournies par le cadrage
	// ET inverse la direction de l'axe Y
	cr->scale(frame.width/(frame.xMax - frame.xMin), 
             -frame.height/(frame.yMax - frame.yMin));
  
	// décalage au centre du cadrage
	cr->translate(-(frame.xMin + frame.xMax)/2, -(frame.yMin + frame.yMax)/2);
}

//Méthodes publiques MyArea:
MyArea::MyArea(){
    setFrame(default_frame);
	set_content_width(default_frame.width);
	set_content_height(default_frame.height);
    set_draw_func(sigc::mem_fun(*this, &MyArea::on_draw));
}

MyArea::~MyArea() {}

void MyArea::setFrame(Frame f){
	if((f.xMin <= f.xMax) and (f.yMin <= f.yMax) and (f.height > 0))
	{
		f.asp = f.width/f.height;
		frame = f;
	}
	else
		std::cout << "incorrect Model framing or window parameters" << std::endl;
}

void MyArea::adjustFrame(int width, int height){
	// Met à jour la largeur et la hauteur du cadre
	frame.width  = width;
	frame.height = height;

    // Pour éviter la distorsion quand on change la taille de la fenêtre
    // afin de conserver les mêmes proportions que la zone graphique

    // Utilise le cadre de référence comme guide pour éviter la distorsion
    double new_aspect_ratio((double)width/height);
    if( new_aspect_ratio > default_frame.asp){ 
		// Garde yMax et yMin. Ajuste xMax et xMin
	    frame.yMax = default_frame.yMax ;
	    frame.yMin = default_frame.yMin ;	
	  
	    double delta(default_frame.xMax - default_frame.xMin);
	    double mid((default_frame.xMax + default_frame.xMin)/2);
       // Le nouveau cadre est centré sur le point médian le long de X
	    frame.xMax = mid + 0.5*(new_aspect_ratio/default_frame.asp)*delta ;
	    frame.xMin = mid - 0.5*(new_aspect_ratio/default_frame.asp)*delta ;		  	  
    }
    else{ 
		// Garde xMax et xMin. Ajuste yMax et yMin
	    frame.xMax = default_frame.xMax ;
	    frame.xMin = default_frame.xMin ;
	  	  
 	    double delta(default_frame.yMax - default_frame.yMin);
	    double mid((default_frame.yMax + default_frame.yMin)/2);
       // Le nouveau cadre est centré sur le point médian le long de y
	    frame.yMax = mid + 0.5*(default_frame.asp/new_aspect_ratio)*delta ;
	    frame.yMin = mid - 0.5*(default_frame.asp/new_aspect_ratio)*delta ;		  	  
    }
}

void MyArea::maj_drawing(){
	queue_draw();
}

//methodes Protected MyArea:

void MyArea::on_draw(const Cairo::RefPtr<Cairo::Context> &cr,
                     int width, int height){

    graphic_set_context(cr);
    adjustFrame(width, height);
	
	//applique la frame ajuster a la drawing area pour eviter la distorsion
    orthographic_projection(cr, frame); 
    
    //affiche la limite du monde de la simulation
    dessin_carre(dmax/2,dmax/2, dmax + 1,gris,1);

	_simulation.affiche();

}

//Classe MyWindow.....................................................................

//Méthodes publiques : 
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
    m_label_charognards("charognards: "),
	disconnect(false),
	freq_timer(50),
	etat_save(false)  {   

	_simulation = simulation;
    set_title("Microrécif");
    set_child(m_main_box);
	maj_info_box();

    // Box
	m_area.set_expand(true);
	m_main_box.append(m_control_box);
	m_main_box.append(m_area);
	m_control_box.append(m_button_box);
	m_control_box.append(m_info_box);
    //box a part pour le check button pour activer les naissances
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
    //pour lier l'evenement bouton clické à la bonne fonction
    m_button_exit.signal_clicked().connect(sigc::mem_fun(*this, 
										   &MyWindow::on_button_clicked_exit));
    m_button_open.signal_clicked().connect(sigc::mem_fun(*this, 
									       &MyWindow::on_button_clicked_open));
	m_button_save.signal_clicked().connect(sigc::mem_fun(*this, 
										   &MyWindow::on_button_clicked_save));
	m_button_start_stop.signal_clicked().connect(sigc::mem_fun(*this, 
										   &MyWindow::on_button_clicked_start_stop));
	m_button_step.signal_clicked().connect(sigc::mem_fun(*this, 
										   &MyWindow::on_button_clicked_step));
	//pour lier l'evenement touche appuyée à la bonne fonction
    auto controller = Gtk::EventControllerKey::create();
    controller->signal_key_pressed().connect(
                  sigc::mem_fun(*this, &MyWindow::on_window_key_pressed), false);
    add_controller(controller);
    
    m_info_box.append(m_label_info_subtitle);
	m_info_box.append(m_label_maj);
    m_info_box.append(m_label_algues);
    m_info_box.append(m_label_corails);
    m_info_box.append(m_label_charognards);
}

void MyWindow::maj_info_box(){
	
	m_label_maj.set_text("mises à jour: " + to_string(_simulation.getNbMaj()));
	m_label_algues.set_text("algues: " + to_string(_simulation.getNbAlg()));
	m_label_corails.set_text("corails: " + to_string(_simulation.getNbCor()));
	m_label_charognards.set_text("charognards: " + to_string(_simulation.getNbSca()));
}

//Methodes protected:

bool MyWindow::on_timeout(){

	if(disconnect)
	{	
		disconnect = false; // mis à false pour si un nouveau timer est créé
		return false; // fin du timer
	}
	
	//si le timer est activé on fait un step à la simulation
	_simulation.step(m_check_button_naissance.get_active());
	maj_info_box();
	m_area.maj_drawing();

	return true; 
}

void MyWindow::on_button_clicked_exit(){
    exit(EXIT_SUCCESS);
}  

void MyWindow::on_button_clicked_open(){
    
	auto dialog = new Gtk::FileChooserDialog("Please choose a file",
		  Gtk::FileChooser::Action::OPEN);
	dialog->set_transient_for(*this);
	dialog->set_modal(true);
	dialog->signal_response().connect(sigc::bind(
	sigc::mem_fun(*this, &MyWindow::on_file_dialog_response), dialog));
	
	//Ajout de boutons dans la fenêtre de dialogue
	dialog->add_button("_Cancel", Gtk::ResponseType::CANCEL);
	dialog->add_button("_Open", Gtk::ResponseType::OK);

	//Ajout de filtres pour savoir quels types de fichier on peut ouvrir
	auto filter_text = Gtk::FileFilter::create();
	filter_text->set_name("Text files");
	filter_text->add_mime_type("text/plain");
	dialog->add_filter(filter_text);
	
	auto filter_cpp = Gtk::FileFilter::create();
	filter_cpp->set_name("C/C++ files");
	filter_cpp->add_mime_type("text/x-c");
	filter_cpp->add_mime_type("text/x-c++");
	filter_cpp->add_mime_type("text/x-c-header");
	dialog->add_filter(filter_cpp);
	
	auto filter_any = Gtk::FileFilter::create();
	filter_any->set_name("Any files");
	filter_any->add_pattern("*");
	dialog->add_filter(filter_any);

	dialog->show();
} 

void MyWindow::on_button_clicked_save(){
	
	string boutonEtat = m_button_start_stop.get_label();
	if(boutonEtat == "stop"){
		//si la simulation est en cours on arrête le timer pour eviter les problèmes 
		//lors de l'écriture du fichier de sauvegarde
		m_button_start_stop.set_label("start");
		disconnect  = true;
	}
	
    etat_save = true;
	auto dialog = new Gtk::FileChooserDialog("Please choose a file",
		                                     Gtk::FileChooser::Action::SAVE);
	dialog->set_transient_for(*this);
	dialog->set_modal(true);
	dialog->signal_response().connect(sigc::bind(
	sigc::mem_fun(*this, &MyWindow::on_file_dialog_response), dialog));
	
	//Ajout de boutons dans la fenêtre de dialogue
	dialog->add_button("_Cancel", Gtk::ResponseType::CANCEL);
	dialog->add_button("_Save", Gtk::ResponseType::OK);
	
	//Ajout de filtres pour savoir quels types de fichier on peut ouvrir
	auto filter_text = Gtk::FileFilter::create();
	filter_text->set_name("Text files");
	filter_text->add_mime_type("text/plain");
	dialog->add_filter(filter_text);
	
	auto filter_cpp = Gtk::FileFilter::create();
	filter_cpp->set_name("C/C++ files");
	filter_cpp->add_mime_type("text/x-c");
	filter_cpp->add_mime_type("text/x-c++");
	filter_cpp->add_mime_type("text/x-c-header");
	dialog->add_filter(filter_cpp);
	
	auto filter_any = Gtk::FileFilter::create();
	filter_any->set_name("Any files");
	filter_any->add_pattern("*");
	dialog->add_filter(filter_any);
	dialog->show();
}

void MyWindow::on_button_clicked_start_stop(){
    std::string boutonEtat = m_button_start_stop.get_label();

    if(boutonEtat == "start"){
        m_button_start_stop.set_label("stop");
		// Crée un slot pour appeler la fonction membre on_timeout() de MyWindow
		sigc::slot<bool()> my_slot = sigc::bind(sigc::mem_fun(*this,
		                                        &MyWindow::on_timeout));
												
		// Connecte le slot à la fonction signal_timeout() de Glib
		auto conn = Glib::signal_timeout().connect(my_slot,freq_timer);
			
    }else{
        m_button_start_stop.set_label("start");
		disconnect  = true;  
    }

}

void MyWindow::on_button_clicked_step(){ 
	//On veut pouvoir step seulement si la simulation n'est pas en cours
	string boutonEtat = m_button_start_stop.get_label();
	if(boutonEtat == "start"){
    	on_timeout(); //un step c'est comme un tic du timer
	}

}

bool MyWindow::on_window_key_pressed(guint keyval, guint, Gdk::ModifierType state){	
	switch(gdk_keyval_to_unicode(keyval)){
		case 's':
			//on veut faire la même chose que si le bouton start/stop est clické
			on_button_clicked_start_stop();
			return true;
		case '1':
			//on veut faire la même chose que si le bouton step est clické
			on_button_clicked_step();
			return true;
	}
    // Au cas où l'événement n'a pas été géré
    return false;
}

void MyWindow::on_file_dialog_response(int response_id, 
										    Gtk::FileChooserDialog* dialog){
	switch (response_id){
		case Gtk::ResponseType::OK:{
			if(etat_save){ 
				//on veut créer le fichier à enregistrer et l'enregistrer
		    	auto filename = dialog->get_file()->get_path();
				ofstream fichier;
				fichier.open(filename, ofstream::trunc);
				if (!fichier.fail()){
					fichier << _simulation.data_to_string() << endl;
					fichier.close();
				}else{
					cout << "Echec de l'ouverture du fichier" << endl;
				}

			}else{
				//cette fois on veut juste lancer la simulation avec
				//le fichier qu'on ouvre en effacant la simulation en cours
				auto filename = dialog->get_file()->get_path();
				_simulation.reset();
				_simulation.lecture(filename);
				maj_info_box();
				m_area.maj_drawing();

			}
		    break;
		}
		case Gtk::ResponseType::CANCEL:{
		    cout << "Cancel clicked." << endl;
		    break;
		}
		default:{
		    cout << "Unexpected button clicked." << endl;
		    break;
		}
	}
	etat_save = false;
	delete dialog;
}
