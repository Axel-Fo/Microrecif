#include "simulation.h"


//on traite le fichier ligne par ligne
void lecture( char * fichier_entree)
{
    string ligne;
    //la ligne du dessous appe
    ifstream fichier(fichier_entree); 
    if(!fichier.fail()) 
    {
        
        while(getline(fichier >> ws,ligne)) 
        //ws =ignorer espaces blancs
		{	
			if(line[0]=='#')  continue;  
       
			decodage_ligne(ligne);
        }
        cout << "fin de la lecture" << endl;
	}
	else cout <<"erreur lgn 22 simu"<<endl;
}

void decodage_ligne(string ligne)
{

}

