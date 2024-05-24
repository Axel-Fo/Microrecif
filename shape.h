/*
* Fichier : shape.h
* Auteurs : Nestor Guibentif et Axel Fouet
* Version : V3
*/
#ifndef SHAPE_H_INCLUDED
#define SHAPE_H_INCLUDED

#include <cmath>
#include "graphic.h"

enum Etat_epsil_zero { NOT_EPSIL, IS_EPSIL };

constexpr double epsil_zero(0.5);

struct S2d {
    double x = 0.;
    double y = 0.;
};

class Segment {
private:
    S2d point;
    double angle;
    double longueur;

    double norme(S2d pt1, S2d pt2) const;
    int orientation(S2d p, S2d q, S2d r, Etat_epsil_zero etat) const;
    bool onSegment(S2d p, S2d q, S2d r, Etat_epsil_zero etat) const;

public:
    Segment(S2d point, double a, double l);
    Segment(S2d point1, S2d point2);

    bool intersect(Segment autre, Etat_epsil_zero etat) const;
    //angle du segment avec l'horizontale - angle du seg "autre" avec l'horiz. + pi :
    double ecart_ang(Segment autre) const;
    //angle entre les 2 segments de même base :
    double ecart_ang_mm_pt(Segment autre) const; 
    bool intersect_mm(Segment autre) const;
    S2d autre_pt() const;

    void affiche(Couleur couleur, double largeur)const;

    void ajout_angle(double delta_angle);
    void ajout_longueur(double delta_longueur);

    double getAngle() const;
    double getLongueur() const;
    S2d getPoint() const;
};

class Cercle{
private:
    S2d centre;
    double rayon;

public:
    Cercle(S2d centre, double rayon);
    void affiche(Couleur couleur, double largeur) const;
};

class Carre{
private:
    S2d centre;
    double arete;
   
public:
    Carre(S2d centre, double arete);
    void affiche(Couleur couleur, double largeur) const;
};

#endif  // SHAPE_H_INCLUDED