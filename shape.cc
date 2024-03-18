#include "shape.h"
#include <cmath>
#include <iostream>
using namespace std;

Segment::Segment(S2d point,double a, double l)
    :point(point)
{
    setLongeur(l);
    setAngle(a);
}
// les fonctions set
void Segment::setAngle(double a)
{
    if(a <= M_PI and a > -M_PI)
    {
        angle = a;
    }

}


void Segment::setLongeur(double l)
{
    if(l>0)
    {
        longeur = l;
    }

}
//pour avoir le deuxième pt du segment
S2d Segment::autre_pt(Segment seg)
{
    S2d point;
    point.x = seg.point.x + seg.longeur*cos(seg.angle);
    point.y = seg.point.y + seg.longeur*sin(seg.angle);
    return point;
}
double norme(S2d pt1, S2d pt2)
{
    return sqrt(pow(pt1.x-pt2.x,2)+pow(pt1.y-pt2.y,2));   
}
// Given three collinear points p, q, r, the function checks if 
// point q lies on line segment 'pr' 
bool onSegment(S2d p, S2d q, S2d r) 
{ 
    double prod_scl = p.x * q.x + p.y * q.y;
    double pr = norme(p,r);
    double proj = prod_scl/pr;
    if(proj>= -epsil_zero && proj<= (epsil_zero + pr))
        return true;
    return false; 
} 
int orientation(S2d p, S2d q, S2d r) 
{ 
    double normepq = norme(p,q);
    double val = (q.y - p.y) * (r.x - q.x) - 
              (q.x - p.x) * (r.y - q.y); 
    val = val/normepq;
    if (abs(val) < epsil_zero) return 0;  // collinear 
  
    return (val > 0)? 1: 2; // clock or counterclock wise 
} 
bool Segment ::intersect(Segment autre)
{   S2d p1 = point;
    S2d p2 = autre_pt(*this);
    S2d q1 = autre.point;
    S2d q2 = autre_pt(autre);
    // Find the four orientations needed for general and 
 
    int o1 = orientation(p1, q1, p2); 
    int o2 = orientation(p1, q1, q2); 
    int o3 = orientation(p2, q2, p1); 
    int o4 = orientation(p2, q2, q1); 
  
    // General case 
    if (o1 != o2 && o3 != o4) 
        return true; 
  
    // Special Cases 
    if (o1 == 0 && onSegment(p1, p2, q1)) return true; 
  
    if (o2 == 0 && onSegment(p1, q2, q1)) return true; 
  
    if (o3 == 0 && onSegment(p2, p1, q2)) return true; 
  
    if (o4 == 0 && onSegment(p2, q1, q2)) return true; 
  
    return false; // Doesn't fall in any of the above cases 
    
}


double Segment::ecart_ang(Segment autre)
{
    double ang1 = angle;
    double ang2 = autre.angle;
    double ang_ecart = ang1 -ang2;// demander assi quel sense est positif
    
    // pour s'assurer que l'angle d'ecart est bien entre pi et -pi
    if(ang_ecart > M_PI) 
    {
        ang_ecart = ang_ecart - 2*M_PI;
    }
    if(ang_ecart < -M_PI)
    {
        ang_ecart = ang_ecart + 2*M_PI;
    }

    return ang_ecart;
}
 bool Segment:: intersect_mm(Segment autre)
{
    
    //a faire

}