#include "lifeform.h"

using namespace std;

Corail::Corail(istringstream &data)
{ 
    data >> proprietes.pos.x >> proprietes.pos.y >> proprietes.age >> id >> statut_cor >> sens_rota >> statut_dev >> nb_seg;
}

Algue::Algue(istringstream &data)
{
    data >> proprietes.pos.x >> proprietes.pos.y >> proprietes.age;
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