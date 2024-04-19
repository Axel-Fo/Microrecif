#ifndef SHAPE_H_INCLUDED
#define SHAPE_H_INCLUDED

#include <cmath>
#include "graphic.h"
constexpr double epsil_zero(0.5);

enum Etat_epsil_zero { NOT_EPSIL, IS_EPSIL };

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

    void afficheSeg(Couleur couleur, double largeur)const;

    void setAngle(double a);
    void setLongeur(double l);

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
    void afficheCecle(Couleur couleur, double largeur) const;
};

class Carre{
private:
    S2d centre;
    double arrete;
   

public:
    Carre(S2d centre, double arrete);
    void afficheCarre(Couleur couleur, double largeur) const;
};

#endif  // SHAPE_H_INCLUDED