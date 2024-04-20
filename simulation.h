/*
* Fichier : simulation.h
* Auteurs : Nestor Guibentif et Axel Fouet
* Version : V1
*/

#ifndef SIMULATION_H_INCLUDED
#define SIMULATION_H_INCLUDED

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <random> 

#include "lifeform.h"
#include "message.h"

enum Etat_lecture {
    NBA,
    ALG,  
    NBC, 
    COR,
    SEG,  
    NBS,
    SCA
};  

class Simulation {
private:
    std::vector<Corail> coraux;
    std::vector<Scavenger> scavengers;
    std::vector<Algue> algues;
    unsigned int etat_lecture;
    unsigned int compteur;
    unsigned int nbSeg;
    unsigned int compteur_seg;
    unsigned int nbAlg;
    unsigned int nbCor;
    unsigned int nbSca;
    // pour la sequence random
    std::default_random_engine e;
    std::bernoulli_distribution random_algue;
    std::uniform_int_distribution<unsigned> random_pos;
    
    void switch_lecture(std::istringstream& data);
    bool idExist(int id);
    void testId(Corail corail);
    void testIdMange(Scavenger scav);
    void testCollision(Corail corail);

public:
    Simulation();
    void lecture(std::string file);
    unsigned int getNbAlg()const;
    unsigned int getNbCor()const;
    unsigned int getNbSca()const;
    void affiche()const;
    std::string data_to_string();
    void step(bool naissance);
};

#endif  // SIMULATION_H_INCLUDED