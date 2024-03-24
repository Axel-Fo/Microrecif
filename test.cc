#include <iostream>
#include "shape.h"

using namespace std;

int main()
{
    S2d point;
    double length ;
    double angle ;

    
    
    cout<<"entrez seg 1"<<endl;
    cin>>point.x>>point.y>>angle>>length;
    Segment seg1(point,angle,length);
    cout<<"entrez seg 2"<<endl;
    cin>>point.x>>point.y>>angle>>length;
    Segment seg2(point,angle,length);

    cout<<"intersection"<<endl;
    (seg1.intersect(seg2,NOT_EPSIL))? cout<<"Vrai"<<endl: cout<<"Faux"<<endl;
    cout<<"écart angulaire "<<seg1.ecart_ang(seg2)<<endl;
    S2d autre = seg1.autre_pt();
    cout<<"autre point"<<autre.x<<".."<<autre.y<<endl;
    
    return 0;
}