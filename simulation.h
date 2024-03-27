#ifndef SIMULATION_H_INCLUDED
#define SIMULATION_H_INCLUDED

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

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
    void switch_lecture(std::istringstream& data);

   public:
    void lecture(std::string file);
};

#endif  // SIMULATION_H_INCLUDED