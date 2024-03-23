#include "lifeform.h"

using namespace std;

S2d Entite::getPosition() const
{
    return pos;
}

unsigned int Entite::getAge() const
{
    return age;
}
void Entite::setPosition(double newX, double newY)
{ 
    pos.x = newX; pos.y = newY; 
}
void Entite::setAge(unsigned int newAge)
{
    age = newAge; 
}

Corail::Corail(istringstream &data)
{ 
    double x,y;
    int age;
    data >> x >> y >> age >> id >> 
            vie_cor >> sens_rota >> statut_dev >> nb_seg;
    
    proprietes.setPosition(x, y);
    proprietes.setAge(age);

    S2d base(proprietes.getPosition());

    // on regarde les propriétés de chaque segment pour les entrer :
    for(unsigned i(0);i <= nb_seg; ++i)
    {
        double angle;
        unsigned int longueur;
        data >> angle >> longueur;
        Segment new_segment(base,angle,longueur);
        segments.push_back(new_segment);

        base = new_segment.autre_pt(new_segment);  
    }
}

Scavenger::Scavenger(istringstream &data)
{   
    double x, y;
    unsigned int age;
    data >> x >> y >> age >> rayon >> statut_sca;
    
    proprietes.setPosition(x, y);
    proprietes.setAge(age);

    if (statut_sca)
    {
        data >> cor_id_cible;
    }
}

Algue::Algue(istringstream &data)
{
    double x,y;
    int age;
    data >> x >> y >> age;
    
    proprietes.setPosition(x, y);
    proprietes.setAge(age);

}

Entite Algue::getEntite() const
{
    return proprietes;
}

Entite Scavenger::getEntite() const
{
    return proprietes;
}
//.....................................................................................
//definition des geteurs pour le corail

Entite Corail::getEntite() const
{
    return proprietes;
}

int Corail::getId() const 
{ 
    return id; 
}

bool Corail::getVieCor() const 
{ 
    return vie_cor; 
}
bool Corail::getSensRota() const 
{ 
    return sens_rota; 
}
bool Corail::getStatutDev() const 
{ 
    return statut_dev; 
}
unsigned int Corail::getNbSeg() const 
{ 
    return nb_seg; 
}
std::vector<Segment> Corail::getSegments() const 
{ 
    return segments; 
}