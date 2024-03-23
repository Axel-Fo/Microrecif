#include "simulation.h"


using namespace std;
//on traite le fichier ligne par ligne

void Simulation::lecture(string fichier_entree)
{
    string line;
    
    ifstream fichier(fichier_entree); 
    if(!fichier.fail()) 
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
        cout <<message::success();
	}
	else cout <<"erreur lgn 22 simu"<<endl;
}
bool idExist(std::vector<Corail> coraux,int id)
{
    for(long unsigned int i(0); i< coraux.size();i++)
    {
        if(coraux[i].getId() == id)
        {
            return true;
        }
    }
    return false;
}
void test_id(std::vector<Corail> coraux, Corail corail)
{
    if(idExist(coraux,corail.getId()))
    {
        cout <<message::lifeform_duplicated_id(corail.getId());
        std ::exit(EXIT_FAILURE);
    }

}
/*void testIdMange(std::vector<Corail> coraux, Scavenger scav)
{
    if(! idExist(coraux,scav.getcorIdCible()))
    {
        cout <<message::lifeform_duplicated_id(corail.getId());
        std ::exit(EXIT_FAILURE);
        
    }
}*/
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
            new_alg.testAlgue();
            algues.push_back(new_alg);
            ++compteur;
            if (compteur == nbAlg)
                etat_lecture = NBC;
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
            new_corail.testCorail();
            test_id(coraux,new_corail);
            coraux.push_back(new_corail);
            ++compteur;
            if (compteur == nbCor)
                etat_lecture = NBS;
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
            new_sca.testScavenger();
            scavengers.push_back(new_sca);
            //plus besoin du compteur forcement des donnees de scavenger.
            break;
        }
        default: cout<< "Erreur, on est arrivés dans le default du switch de lecture" 
                << endl;
    }   
}