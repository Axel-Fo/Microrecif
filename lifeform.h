#ifndef LIFEFORM_H_INCLUDED
#define LIFEFORM_H_INCLUDED


#include <string>
#include <sstream>
#include <cmath>
#include <iostream>
#include <vector>
#include "shape.h"
#include "constantes.h"
#include "message.h"

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
private :
    Entite proprietes;
    bool statut_sca; //0 pour LIBRE et 1 pour MANGE
    double rayon;
    int cor_id_cible;
public :
    Scavenger(std::istringstream& data);
    int getcorIdCible() const;
    Entite getEntite() const;
    void testScavenger() const;
    bool getStatutSca()const;

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
    S2d extremite;
    
public :
    //constructeur
    Corail(std::istringstream& data);
    Entite getEntite() const;
    int getId() const;
    bool getVieCor() const;
    bool getSensRota() const;
    bool getStatutDev() const;
    unsigned int getNbSeg() const;
    std::vector<Segment> getSegments() const;
    void ajout_seg(std::istringstream& data);
    void testCorail() const;
};

class Algue{
private:
    Entite proprietes;
public:
    Algue(std::istringstream& data);
    Entite getEntite() const;
    void testAlgue() const;

};
#endif // LIFEFORM_H_INCLUDED