/*
* Fichier : simulation.h test push
* Auteurs : Nestor Guibentif et Axel Fouet
* Version : V2
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
    unsigned int nbMaj;
    bool erreur;
    
    // pour la sequence random
    std::default_random_engine e;
    std::bernoulli_distribution random_algue;
    std::uniform_int_distribution<unsigned> random_pos;
    
    void switch_lecture(std::istringstream& data);
    bool id_exist(int id);
    bool test_id(Corail corail);
    bool test_id_mange(Scavenger scav);
    bool test_coll_seg(Segment seg, bool lecture ,unsigned int index, int id);
    bool test_collision(Corail corail);
    
    void step_algues();
    
    void step_coraux();
    bool candidat_mange(Corail& cor, double& delta_ang,int& indexAlgCandidat);
    bool test_collision_simu(Corail& cor, double del_ang, bool mange);
    
    void step_scav();
    void mort_alg(int index);
    void scaMange(Scavenger sca, int id);


public:
    Simulation();
    void lecture(std::string file);
    void reset();
    
    unsigned int getNbAlg() const;
    unsigned int getNbCor() const;
    unsigned int getNbSca() const;
    unsigned int getNbMaj() const;
    
    void affiche() const;
    std::string data_to_string();
    void step(bool naissance);
};

#endif  // SIMULATION_H_INCLUDED