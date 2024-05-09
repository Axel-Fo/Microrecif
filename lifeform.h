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
    bool miam;

public:
    // constructeur
    Corail(std::istringstream& data);
    Corail(Corail parent, int _id);

    void ajout_seg(std::istringstream& data);
    void ajout_seg(Segment seg);
    void mortCorail();
    void rotaCorail(double angle);
    void change_sens();
    void tailleCorChange(double delta_longueur);
    bool testCorail() const;
    std::string cor_to_string() const;
    void majExtremite();
    void change_statut_dev();

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
    Scavenger(S2d pos); //rayon par défaut sur r_sca pour eviter qu'un donne un rayon 
                        //non autorisé ( > r_sca_repro)

    bool testScavenger() const;
    std::string sca_to_string() const;
    void scaMouvement(S2d direction, double distance);
    void scaGrandit(int delta_r);
    void sca_statut_change();
    void resetTaille();
    
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