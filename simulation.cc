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
        //on a plus besoin du compteur car les lignes sont forcement des donnees de scavenger.
            break;
        }
        default: cout<< "Erreur, on est arrivés dans le default du switch de lecture" << endl;
    }   
}
