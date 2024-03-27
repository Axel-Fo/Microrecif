/*
* Fichier : lifeform.h
* Auteurs : Nestor Guibentif et Axel Fouet
* Version : V1
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

//Classe Entite qui sera une Super Classe pour les prochains rendus.
class Entite {
private:
    S2d pos;
    unsigned int age;

public:
    Entite();
    Entite(S2d pos, unsigned int age);
    // Getters
    S2d getPosition() const;
    unsigned int getAge() const;
};


class Corail {
private:
    Entite proprietes;
    int id;
    bool vie_cor;
    bool sens_rota;
    bool statut_dev;
    unsigned int nb_seg;
    std::vector<Segment> segments;
    S2d extremite;
    void testSeg() const;

public:
    // constructeur
    Corail(std::istringstream& data);

    void ajout_seg(std::istringstream& data);
    void testCorail() const;

    Entite getEntite() const;
    int getId() const;
    bool getVieCor() const;
    bool getSensRota() const;
    bool getStatutDev() const;
    unsigned int getNbSeg() const;
    std::vector<Segment> getSegments() const;
};

class Scavenger {
private:
    Entite proprietes;
    bool statut_sca;
    bool vie_sca;
    double rayon;
    int cor_id_cible;
    void testRayon() const;

public:
    Scavenger(std::istringstream& data);
    
    void testScavenger() const;
    int getcorIdCible() const;
    Entite getEntite() const;
    bool getStatutSca() const;
};

class Algue {
private:
    Entite proprietes;

public:
    Algue(std::istringstream& data);
    
    void testAlgue() const;
    Entite getEntite() const;
    
};
#endif  // LIFEFORM_H_INCLUDED