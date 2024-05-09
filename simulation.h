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
    std::vector<Segment> bords;
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
    bool id_exist(int id) const;
    bool test_id(Corail corail) const;
    bool test_id_mange(Scavenger scav) const;
    bool test_coll_seg(Segment seg, bool lecture ,unsigned int index, int id) const;
    bool test_collision(Corail corail) const;
    
    void step_algues();
    void mort_alg(int index);

    void step_coraux();
    void dev_corail(Corail& cor);
    unsigned int new_id() const;
    bool candidat_mange_alg(Corail& cor, double& delta_ang,int& indexAlg);
    bool test_collision_simu(Corail& cor, double del_ang, bool mange);
    bool test_autocollision_simu(Corail& cor, double del_ang);
    bool test_collision_bord(Corail& cor);
    
    void step_scav();
    void scaMange(Scavenger& sca, int id);
    void rechercheCorail();


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