#ifndef SIMULATION_H_INCLUDED
#define SIMULATION_H_INCLUDED

#include <string>
#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>//pour ouvrir et lire fichiers
#include <sstream> 
#include "lifeform.h"
#include "message.h"
// sstream permet de gérer les strings comme flux de donées
//pour pouvoir les manipuler,changer leur types, effacer 
//en extraire des trucs etc (comme ca que je l'ai compris)

enum Etat_lecture
{
    NBA, ALG ,
    NBC, COR, 
    NBS, SCA 
};

class Simulation {
private: 
    std::vector<Corail> coraux;
    std::vector<Scavenger> scavengers;
    std::vector<Algue> algues;
    unsigned int etat_lecture;
    unsigned int compteur;
    unsigned int nbAlg;
    unsigned int nbCor;
    unsigned int nbSca;
    void switch_lecture(std::istringstream& data);
public :
    void lecture(std::string file);
};


#endif // SIMULATION_H_INCLUDED