#include "lifeform.h"

using namespace std;

Corail::Corail(istringstream &data)
{ 
    data >> proprietes.pos.x >> proprietes.pos.y >> proprietes.age >> id >> vie_cor >> sens_rota >> statut_dev >> nb_seg;
}

Scavenger::SScavenger(istringstream &data)
{   
    data >> proprietes.pos.x >> proprietes.pos.y >> proprietes.age
         >> rayon >> statut_sca;
    if (statut_sca)
    {
        data >> cor_id_cible;
    }
}