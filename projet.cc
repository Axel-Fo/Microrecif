/*
* Fichier : projet.cc
* Auteurs : Nestor Guibentif et Axel Fouet
* Version : V1
*/

#include <iostream>
#include <gtkmm/application.h>
#include "simulation.h"
#include "gui.h"

using namespace std;

int main(int argc, char* argv[]) {
    
    Simulation simulation;
    if (argc != 2) {
        cout << "Error : il faut mettre un nom de fichier." << endl;
    }
    simulation.lecture(argv[1]);

    auto myApp = Gtk::Application::create();
    //Shows the window and returns when it is closed.
    return myApp->make_window_and_run<MyWindow>(1,argv,simulation);
}