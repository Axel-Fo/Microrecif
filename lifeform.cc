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
    //tant qu'un corail ne possède pas de segments son extremite est sa base :
    extremite = proprietes.getPosition();
}

void Corail::ajout_seg(istringstream &data)
{   
    double angle;
    unsigned int longueur;
    data >> angle >> longueur;
    Segment new_segment(extremite,angle,longueur);
    segments.push_back(new_segment);
    //nouvelle extremite
    extremite = new_segment.autre_pt();
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
int Scavenger::getcorIdCible() const
{
    return cor_id_cible;
}
bool Scavenger::getStatutSca() const
{
    return statut_sca;
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

vector<Segment> Corail::getSegments() const 
{ 
    return segments; 
}

void testAge(unsigned int age)
{
    
    //pas de test avec des valeurs negatives pour l'age
    if(age==0)
    {
        cout <<message::lifeform_age(age);
        std ::exit(EXIT_FAILURE);
    }
}
void testSeg(Corail corail)
{   
    unsigned int id = corail.getId();
    std::vector<Segment> segments = corail.getSegments();
    for(long unsigned int i(0);i < segments.size();i++)
    {   // on test la longeur du segment
        unsigned int longeur = segments[i].getLongeur();

        if(longeur< l_repro-l_seg_interne or longeur>=l_repro)
        {
        
        cout <<message::segment_length_outside(id,longeur);
        std ::exit(EXIT_FAILURE);

        } //on test si l'angle est dans le bon interval
        double angle = segments[i].getAngle();
        if(angle< -M_PI or angle > M_PI)
        {
        
        cout <<message::segment_angle_outside(id,angle);
        std ::exit(EXIT_FAILURE);
        }
        //on test si le segment est replier sur le précédent si il existe
        if (i != 0)
        {
            if(segments[i].intersect_mm(segments[i-1]))
            {
                cout <<message::segment_superposition(id, i-1, i);
                std ::exit(EXIT_FAILURE);
            }
        }
        // on test si l'extremité sur segment est bien dans le cadre
        S2d autre = segments[i].autre_pt();
        if(autre.x< 0 or autre.x> ::max or autre.y< 0 or autre.y> ::max)
        {
        cout <<message::lifeform_computed_outside(id,autre.x, autre.y);
        std ::exit(EXIT_FAILURE);
        }
    }
}


void testPos(S2d pos)
{   /*pour resoudre le conflit entre la fct et la variable max 
    on spécifie avec :: le namespace global*/

    if(pos.x< 1 or pos.x> ::max -1 or pos.y< 1 or pos.y> ::max -1)
    {
        cout <<message::lifeform_center_outside(pos.x,pos.y);
        std ::exit(EXIT_FAILURE);
    }
}
void testRayon(double rayon)
{
    if(rayon <r_sca or rayon >= r_sca_repro)
    {
        cout <<message::scavenger_radius_outside(rayon);
        std ::exit(EXIT_FAILURE);
    }
}
void Corail::testCorail() const
{
    testAge(proprietes.getAge());
    testPos(proprietes.getPosition());
    testSeg(*this);

}
void Algue::testAlgue() const
{
    testAge(proprietes.getAge());
    testPos(proprietes.getPosition());

}

void Scavenger::testScavenger() const
{
    testAge(proprietes.getAge());
    testPos(proprietes.getPosition());
    testRayon(rayon);

}