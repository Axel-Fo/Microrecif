#ifndef LIFEFORM_H_INCLUDED
#define LIFEFORM_H_INCLUDED


#include <string>
#include <sstream>
#include <iostream>
#include "shape.h"
#include "constantes.h"

class Entite {
    public:
    S2d pos;
    unsigned int age;
};

class Scavenger{
    Entite proprietes;
    bool statut_scaetat; //0 pour LIBRE et 1 pour MANGE
    bool vie_sca;
    double rayon;
    int cor_id_cible;
    Scavenger(std::istringstream& data);
};

class Corail{//il faut ajouter un truc pour stocker tout les segments d'un corail
   
    Entite proprietes;
    int id;
    bool vie_cor; 
    bool sens_rota; 
    bool statut_dev;
    unsigned int nb_seg;
    
    
    //constructeur
    Corail(std::istringstream& data);

};

class Algue{
    
    Entite proprietes;
    
    Algue(std::istringstream& data)
    {};
};
#endif // LIFEFORM_H_INCLUDED