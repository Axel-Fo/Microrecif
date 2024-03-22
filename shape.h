#ifndef SHAPE_H_INCLUDED
#define SHAPE_H_INCLUDED

constexpr double epsil_zero(0.5);

enum Etat_epsil_zero
{
    NOT_EPSIL, IS_EPSIL
};

struct S2d
{
    double x= 0.;
    double y= 0.;
};


class Segment
{
private:
    
    S2d point;
    double angle;
    double longeur;


public:
 
 Segment(S2d point,double a, double l);
 
 bool intersect(Segment autre, Etat_epsil_zero etat);
 double ecart_ang(Segment autre);
 bool intersect_mm(Segment autre);
 
 S2d autre_pt(Segment seg);
 
 void setAngle(double a);
 void setLongeur(double l);
};

class Cercle
{
private:
    
    S2d centre;
    double rayon;

public:
 
 //Cercle(S2d centre,double rayon);
};
 
class Carre
{
private:
    

public:
 
 //Carre();
};



#endif // SHAPE_H_INCLUDED