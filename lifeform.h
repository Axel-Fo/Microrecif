#ifndef LIFEFORM_H_INCLUDED
#define LIFEFORM_H_INCLUDED


#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include "shape.h"
#include "constantes.h"

class Entite
{
private:
    S2d pos;
    unsigned int age;
public:
    // Setters
    void setPosition(double newX, double newY);
    void setAge(unsigned int newAge);

    // Getters
    S2d getPosition() const;
    unsigned int getAge() const; 
};

class Scavenger{
public :
    Entite proprietes;
    bool statut_sca; //0 pour LIBRE et 1 pour MANGE
    bool vie_sca;
    double rayon;
    int cor_id_cible;
    Scavenger(std::istringstream& data);
};

class Corail{
private :
    Entite proprietes;
    int id;
    bool vie_cor; 
    bool sens_rota; 
    bool statut_dev;
    unsigned int nb_seg;
    std::vector<Segment> segments;
    
public :
    //constructeur
    Corail(std::istringstream& data);

};

class Algue{
public:
    Entite proprietes;
    
    Algue(std::istringstream& data);
};
#endif // LIFEFORM_H_INCLUDED