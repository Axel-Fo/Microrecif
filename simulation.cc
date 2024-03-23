#include "simulation.h"


using namespace std;
//on traite le fichier ligne par ligne

void Simulation::lecture(string fichier_entree)
{
    string line;
    
    ifstream fichier(fichier_entree); 
    if(fichier.fail()) 
    {
        etat_lecture = NBA;
        compteur = 0 ;
        nbAlg = 0;
        nbSca = 0;
        nbCor = 0;
        while(getline(fichier >> ws,line)) 
		{	
			if(line[0]=='#')  
                continue;  
       
			istringstream data(line);
            switch_lecture(data);
        }
        cout << "fin de la lecture" << endl;
	}
	else cout <<"erreur lgn 22 simu"<<endl;
}

void Simulation::switch_lecture(istringstream &data)
{
    switch (etat_lecture)
    {
        case NBA:
        {
            data >> nbAlg;
            if (nbAlg == 0)
                etat_lecture = NBC;
            else
                etat_lecture = ALG;
            break;
        }
        case ALG:
        {
            Algue new_alg(data);
            //test_age();
            algues.push_back(new_alg);
            ++compteur;
            if (compteur == nbAlg)
                etat_lecture = NBC;
            //test d'erreur ici avec un if ?
            break;
        }
        case NBC:
        {
            data >> nbCor;
            if (nbCor == 0)
                etat_lecture = NBS;
            else
                etat_lecture = COR;
            break;
        }
        case COR:
        {
            compteur = 0;
            Corail new_corail(data);
            coraux.push_back(new_corail);
            ++compteur;
            if (compteur == nbCor)
                etat_lecture = NBS;
            //test d'erreur ici avec un if ?
            break;
        }
        case NBS:
        {
            data >> nbSca;
            if (nbSca == 0)
                etat_lecture = NBS;
            else
                etat_lecture = SCA;
            break;
        }
        case SCA:
        {
            Scavenger new_sca(data);
            scavengers.push_back(new_sca);
            //plus besoin du compteur forcement des donnees de scavenger.
            break;
        }
        default: cout<< "Erreur, on est arrivés dans le default du switch de lecture" 
                << endl;
    }   
}
void test_age(Entite entite)
{
    int age = entite.getAge();
    //pas de test avec des valeurs negatives pour l'age
    if(age==0)
    {
        cout <<message::lifeform_age(age);
        std ::exit(EXIT_FAILURE);
    }
}

/*void test_pos(Entite entite)
{
    S2d pos = entite.getPosition();
    bool x = pos.x< 1 or pos.x> constantes::max -1;///jsp pas commmmmmment faire pour max
    bool y = pos.y< 1 or pos.y> constantes::max -1;
    if(x or y)
    {
        cout <<message::lifeform_center_outside(1, constantes::max  -1);
        std ::exit(EXIT_FAILURE);
    }
}*/
void test_id(std::vector<Corail> coraux,Corail corail)
{
    for(long unsigned int i(0); i< coraux.size();i++)
    {
        if(coraux[i].getId() == corail.getId())
        {
        cout <<message::lifeform_duplicated_id(corail.getId());
        std ::exit(EXIT_FAILURE);
        }
    }
}
void test_seg(Corail corail)
{   
    std::vector<Segment> segments = corail.getSegments();
    for(long unsigned int i(0);i < segments.size();i++)
    {
        unsigned int longeur = segments[i].getLongeur();
        int id = corail.getId();
        if(longeur< l_repro-l_seg_interne or longeur>=l_repro)
        {
        
        cout <<message::segment_length_outside(id,longeur);
        std ::exit(EXIT_FAILURE);

        }
        double angle = segments[i].getAngle();
        if(angle< -M_PI or angle > M_PI)
        {
        
        cout <<message::segment_angle_outside(id,angle);
        std ::exit(EXIT_FAILURE);

        if (i != 0)
        {
            if(segments[i].intersect_mm(segments[i-1]))
            {
                cout <<message::segment_superposition(id, i-1, i);
                std ::exit(EXIT_FAILURE);
            }

        }
        }
    }
}