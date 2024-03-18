#ifndef LIFEFORM_H_INCLUDED
#define LIFEFORM_H_INCLUDED


#include <string>
#include <sstream>
#include <iostream>
#include "shape.h"
#include "constantes.h"

class Entite {
    private :
    S2d pos;
    unsigned int age;
}

class Scavenger{
    private :
    Entite proprietes;
    bool etat; //0 pour LIBRE et 1 pour MANGE(peut être à changer)
    bool statut_sca
    double rayon;
    int cor_id_cible;
    public :
    Scavenger(std::istringstream& data);
};

class Corail{
    private :
    Entite proprietes;
    int id;
    bool statut_cor; //plutot que statut vie pour avoir noms diff entre les trucs
    bool sens_rota; //par ex 1 pour trigo, 0 pour inv trigo, eventuellement changer en string ou enum ?
    bool statut_dev;//0 pour extend, 1 pour repro
    unsigned int nb_seg;
    
    public :
    //constructeur
    Corail(std::istringstream& data);

}

class Algue{
    private:
    Entite proprietes;
    public :
    Algues(std::istringstream& data);
}
#endif // LIFEFORM_H_INCLUDED