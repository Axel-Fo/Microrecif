#include <iostream>
#include "simulation.h"

using namespace std;

int main(int argc, char* argv[]) {
    Simulation simulation;
    if (argc != 2) {
        cout << "il faut mettre un nom de fichier." << endl;
    }
    simulation.lecture(argv[1]);
}