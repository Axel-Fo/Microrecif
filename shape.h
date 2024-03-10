
constexpr double epsil_zero(0.5);

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
 bool idoIntersect(Segment autre);
 double ecart_ang(Segment autre);
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
 

