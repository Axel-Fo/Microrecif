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

class Lifeform {
protected:
    S2d pos;
    unsigned int age;

public:
    Lifeform();
    Lifeform(S2d pos, unsigned int age = 1);
    void step();
    virtual ~Lifeform();
    unsigned int getAge()const;
    S2d getPos() const;
    std::string lifeform_to_string() const; 
};


class Corail : public Lifeform {
private:
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
    std::string cor_to_string() const;
    int getId() const;
    bool getVieCor() const;
    bool getSensRota() const;
    bool getStatutDev() const;
    unsigned int getNbSeg() const;
    std::vector<Segment> getSegments() const;
    
};

class Scavenger : public Lifeform{
private:
    bool statut_sca;
    bool vie_sca;
    double rayon;
    int cor_id_cible;
    void testRayon() const;

public:
    Scavenger(std::istringstream& data);
    
    void testScavenger() const;
    std::string sca_to_string() const;
    int getcorIdCible() const;
    bool getStatutSca() const;
    double getRayon() const;
};

class Algue : public Lifeform{

public:
    Algue(std::istringstream& data);
    Algue(S2d pos);
    
    void testAlgue() const;
};
#endif  // LIFEFORM_H_INCLUDED