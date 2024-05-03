/*
* Fichier : shape.h
* Auteurs : Nestor Guibentif et Axel Fouet
* Version : V2
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

    bool intersect(Segment autre, Etat_epsil_zero etat) const;
    double ecart_ang(Segment autre) const;
    bool intersect_mm(Segment autre) const;
    S2d autre_pt() const;

    void affiche(Couleur couleur, double largeur)const;

    void ajout_angle(double delta_angle);

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