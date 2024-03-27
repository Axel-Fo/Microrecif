/*
* Fichier : projet.cc
* Auteurs : Nestor Guibentif et Axel Fouet
* Version : V1
*/

#include <iostream>
#include "simulation.h"

using namespace std;

int main(int argc, char* argv[]) {
    Simulation simulation;
    if (argc != 2) {
        cout << "Error : il faut mettre un nom de fichier." << endl;
    }
    simulation.lecture(argv[1]);
}