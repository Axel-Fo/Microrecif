/*
* Fichier : projet.cc
* Auteurs : Nestor Guibentif(~50) et Axel Fouet(~50)
* Version : V2
*/

#include <iostream>
#include <gtkmm/application.h>
#include "simulation.h"
#include "gui.h"

using namespace std;

int main(int argc, char* argv[]) {
    
    Simulation simulation;
    if (argc == 2) {
        simulation.lecture(argv[1]);
    } else if (argc == 1) {
        simulation.lecture("0 0 0"); //on donne un string avec 0 entite de chaque
    }else{
        cout<< "Erreur dans le nombre d'arguments donnés dans le main" << endl;
    }


    auto myApp = Gtk::Application::create();
    //Shows the window and returns when it is closed.
    return myApp->make_window_and_run<MyWindow>(1,argv,simulation);
}