/*
* Fichier : lifeform.h
* Auteurs : Nestor Guibentif et Axel Fouet
* Version : V2
*/

#ifndef LIFEFORM_H_INCLUDED
#define LIFEFORM_H_INCLUDED

#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "constantes.h"
#include "message.h"
#include "shape.h"

class Lifeform {
protected:
    S2d pos;
    unsigned int age;

public:
    Lifeform();
    Lifeform(S2d pos, unsigned int age = 1);
    virtual ~Lifeform();
    
    unsigned int getAge()const;
    S2d getPos() const;
    std::string lifeform_to_string() const;
    void step_age(); 
};


class Corail : public Lifeform {
private:
    int id;
    Statut_cor vie_cor;
    Dir_rot_cor sens_rota;
    Statut_dev statut_dev;
    unsigned int nb_seg;
    std::vector<Segment> segments;
    S2d extremite;
    bool testSeg() const;

public:
    // constructeur
    Corail(std::istringstream& data);

    void ajout_seg(std::istringstream& data);
    void mortCorail();
    void rotaCorail(double angle);
    void change_sens();
    void tailleCorAugmente(double delta_longueur);
    bool testCorail() const;
    std::string cor_to_string() const;

    int getId() const;
    Statut_cor getVieCor() const;
    Dir_rot_cor getSensRota() const;
    Statut_dev getStatutDev() const;
    unsigned int getNbSeg() const;
    std::vector<Segment> getSegments() const;
    Segment getDernierSeg() const;
    S2d getExtremite() const;
};

class Scavenger : public Lifeform{
private:
    Statut_sca statut_sca;
    double rayon;
    int cor_id_cible;
    bool testRayon() const;

public:
    Scavenger(std::istringstream& data);
    
    bool testScavenger() const;
    std::string sca_to_string() const;
    void scaMouvement(S2d direction, double distance);
    
    int getCorIdCible() const;
    Statut_sca getStatutSca() const;
    double getRayon() const;
};

class Algue : public Lifeform{

public:
    Algue(std::istringstream& data);
    Algue(S2d pos);
    
    bool testAlgue() const;
};
#endif  // LIFEFORM_H_INCLUDED