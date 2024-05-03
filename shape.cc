/*
* Fichier : shape.cc
* Auteurs : Nestor Guibentif(~40) et Axel Fouet(~60)
* Version : V2
*/
#include "shape.h"
#include <iostream>


//Classe Segment......................................................................

//Methodes private Segment:
double Segment::norme(S2d pt1, S2d pt2) const {
    return sqrt(pow(pt1.x - pt2.x, 2) + pow(pt1.y - pt2.y, 2));
}

int Segment::orientation(S2d p, S2d q, S2d r, Etat_epsil_zero etat) const {
    //pour savoir si les point p,q,r sont alignés
    double comparaison(0.);
    
    if (etat) {// si on est mode detection d'erreur on ne veut pas comparer avec epsil
        comparaison = epsil_zero;
    }

    double normepq = norme(p, q);
    double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    val = val / normepq;
    if (abs(val) <= comparaison)
        return 0; // alignés

    return (val > 0) ? 1 : 2; //retourne 1 ou 2 pour avoir le signe de l'orientation
}

bool Segment::onSegment(S2d p, S2d q, S2d r, Etat_epsil_zero etat) const {
    //pour verifier si le point r est sur le segement pq
    double comparaison(0.);
    if (etat) {
        comparaison = epsil_zero;
    }

    double prod_scl = p.x * q.x + p.y * q.y;
    double pr = norme(p, r);
    double proj = prod_scl / pr;
    if (proj >= -comparaison && proj <= (comparaison + pr))
        return true;
    return false;
}

//Methodes publiques Segment..........................................................

//Constructeur
Segment::Segment(S2d point, double a, double l) 
                : point(point), angle(a), longueur(l) {}

Segment::Segment(S2d point1, S2d point2 ): point(point1){
                    longueur = norme(point1, point2);
                    angle = atan2((point2.y - point1.y ), (point2.x - point1.x ));
                }

bool Segment ::intersect(Segment autre, Etat_epsil_zero etat) const {
    S2d p1 = point;
    S2d p2 = autre.autre_pt();
    S2d q1 = autre_pt();
    S2d q2 = autre.point;

    int o1 = orientation(p1, q1, p2, etat);
    int o2 = orientation(p1, q1, q2, etat);
    int o3 = orientation(p2, q2, p1, etat);
    int o4 = orientation(p2, q2, q1, etat);

    // Cas général
    if (o1 != o2 && o3 != o4)
        return true;

    // cas speciaux
    if (o1 == 0 && onSegment(p1, p2, q1, etat))
        return true;

    if (o2 == 0 && onSegment(p1, q2, q1, etat))
        return true;

    if (o3 == 0 && onSegment(p2, p1, q2, etat))
        return true;

    if (o4 == 0 && onSegment(p2, q1, q2, etat))
        return true;

    return false;  // si l'on est dans aucun des cas
}

double Segment::ecart_ang(Segment autre) const {
    double ang1 = angle;
    double ang2 = autre.angle;
    double ang_ecart = M_PI + (ang1 - ang2);

    // pour s'assurer que l'angle d'ecart est bien entre pi et -pi
    if (ang_ecart > M_PI) {
        ang_ecart = ang_ecart - 2 * M_PI;
    }
    if (ang_ecart <= -M_PI) {
        ang_ecart = ang_ecart + 2 * M_PI;
    }

    return ang_ecart;
}

bool Segment::intersect_mm(Segment autre) const {
    if (this->ecart_ang(autre) == 0) {
        return true;
    }
    return false;
}

S2d Segment::autre_pt() const {
    S2d autre;
    autre.x = point.x + longueur * cos(angle);
    autre.y = point.y + longueur * sin(angle);
    return autre;
}

void Segment::affiche(Couleur couleur, double largeur)const{
    S2d point2 = autre_pt();
    dessin_ligne(point.x,point.y, point2.x, point2.y, couleur, largeur);
}

void Segment::ajout_angle(double delta_angle){
    angle = angle + delta_angle;
}

//Getteurs et setteurs pour Segment ...................................................

double Segment::getAngle() const {
    return angle;
}

double Segment::getLongueur() const {
    return longueur;
}

S2d Segment::getPoint() const {
    return point;
}

//Méthodes publiques Cercle...........................................................
Cercle::Cercle(S2d centre, double rayon) : centre(centre), rayon(rayon){}

void Cercle::affiche(Couleur couleur, double largeur) const{

    dessin_cercle(centre.x, centre.y, rayon, couleur, largeur);
}

//Méthodes publiques Carre...........................................................
Carre::Carre(S2d centre, double arete):centre(centre), arete(arete){}

void Carre::affiche(Couleur couleur, double largeur) const{
                              
    dessin_carre(centre.x, centre.y, arete, couleur, largeur);
}