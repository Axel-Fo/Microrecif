#include "lifeform.h"

using namespace std;

Corail::Corail(istringstream &data)
{ 
    data >> proprietes.pos.x >> proprietes.pos.y >> proprietes.age >> id >> 
            vie_cor >> sens_rota >> statut_dev >> nb_seg;
    for(int i(0);i <= nb_seg; ++i)
    {
        S2d base(proprietes.pos);
        double angle;
        unsigned int longueur;
        data >> angle >> longueur;
        Segment new_segment(proprietes.pos,angle,longueur);
        segments.push_back(new_segment);
        base = new_segment.autre_pt(new_segment);  
    }
}

Scavenger::Scavenger(istringstream &data)
{   
    data >> proprietes.pos.x >> proprietes.pos.y >> proprietes.age
         >> rayon >> statut_sca;
    if (statut_sca)
    {
        data >> cor_id_cible;
    }
}

Algue::Algue(istringstream &data)
{
    data >> proprietes.pos.x >> proprietes.pos.y >> proprietes.age;
}