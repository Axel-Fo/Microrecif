#ifndef SIMULATION_H_INCLUDED
#define SIMULATION_H_INCLUDED

#include <string>
#include <vector>
#include <iostream>
#include <fstream>//pour ouvrir et lire fichiers
#include <sstream> 
#include "lifeform.h"
// sstream permet de gérer les strings comme flux de donées
//pour pouvoir les manipuler,changer leur types, effacer 
//en extraire des trucs etc (comme ca que je l'ai compris)

enum Etat_lecture
{
    NBA, ALGUE ,
    NBC, CORAIL, 
    NBS, SCAVENGER 
}

Classe Donnees
{
    std::vector<Corail> coraux;
    std::vector<Scavenger> scavengers;
    std::vector<Algue> algues;
};

void switch_lecture(istringstream& donnees)

#endif // SIMULATION_H_INCLUDED