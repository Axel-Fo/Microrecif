/*
* Fichier : simulation.cc
* Auteurs : Nestor Guibentif(~60) et Axel Fouet(~40)
* Version : V2
*/
#include "simulation.h"

using namespace std;

//Classe Simulation...................................................................

//Méthodes private :

bool Simulation::idExist(int id) {
    for (long unsigned int i(0); i < coraux.size(); i++) {
        if (coraux[i].getId() == id) {
            return true;
        }
    }
    return false;
}

bool Simulation::testId(Corail corail) {
    if (idExist(corail.getId())) {
        cout << message::lifeform_duplicated_id(corail.getId());
        return true;
    }
    return false;
}

bool Simulation::testIdMange(Scavenger scav) {
    if (scav.getStatutSca()) {
        if (!idExist(scav.getCorIdCible())) {
            cout << message::lifeform_invalid_id(scav.getCorIdCible());
            return true;
        }
    }
    return false;
}

bool Simulation::testCollision(Corail corail){
    vector<Segment> segs = corail.getSegments();
    // test de collision avec les autres coraux
    for (unsigned int i(0); i < coraux.size(); i++) {
        for (unsigned int j(0); j < (coraux[i].getSegments()).size(); j++) {
            for (unsigned int k(0); k < segs.size(); k++) {
                if (!(coraux[i].getId() == corail.getId() and (k == j+1 or 
                                                               k == j-1 or k == j)))
                /*on ne veut pas tester la collision entre
                deux segments qui se précèdent sur le mm corail mais 
                on teste avec le else si ils ne sont pas repliés l'un sur l'autre*/
                {
                    if (segs[k].intersect((coraux[i].getSegments())[j], NOT_EPSIL)) {
                        cout << message::segment_collision(coraux[i].getId(), 
                                                            j, corail.getId(), k);
                        return true;
                    }
                }else{
                    if(k != j){
                        if (segs[k].intersect_mm((coraux[i].getSegments())[j])) {
                        unsigned int id = coraux[i].getId();
                        cout << message::segment_superposition(id, k - 1, k);
                        return true;
                        }
                    }
                    
                }
            }
        }
    }
    return false;
}

void Simulation::switch_lecture(istringstream& data) {
    switch (etat_lecture) {
        case NBA: {
            data >> nbAlg;
            if (nbAlg == 0)
                etat_lecture = NBC;
            else
                etat_lecture = ALG;
            break;
        }
        case ALG: {
            Algue new_alg(data);
            erreur = new_alg.testAlgue();
            algues.push_back(new_alg);
            ++compteur;
            if (compteur == nbAlg) {
                etat_lecture = NBC;
                compteur = 0;
            }
            break;
        }
        case NBC: {
            data >> nbCor;
            if (nbCor == 0)
                etat_lecture = NBS;
            else
                etat_lecture = COR;
            break;
        }
        case COR: {
            Corail new_corail(data);
            erreur = testId(new_corail);
            coraux.push_back(new_corail);
            ++compteur;
            nbSeg = new_corail.getNbSeg();
            etat_lecture = SEG;
            break;
        }
        case SEG:  // on ajoute au dernier corail du vecteur un segment
        {
            coraux.back().ajout_seg(data);
            compteur_seg++;
            if (compteur_seg == nbSeg) {
                if(coraux.back().testCorail() or testCollision(coraux.back()))
                    erreur = true;
                if (compteur == nbCor) {
                    etat_lecture = NBS;
                    break;
                }
                compteur_seg = 0;
                etat_lecture = COR;
            }
            break;
        }
        case NBS: {
            data >> nbSca;
            if (nbSca == 0)
                etat_lecture = NBS;
            else
                etat_lecture = SCA;
            break;
        }
        case SCA: {
            Scavenger new_sca(data);
            if(new_sca.testScavenger() or testIdMange(new_sca))
                erreur = true;

            scavengers.push_back(new_sca);
            // plus besoin du compteur car forcement des donnees de scavenger.
            break;
        }
        default:
            cout <<"Erreur, on est arrivé dans le default du switch de lecture"<<endl;      
    }
}

void Simulation::step_algues(){ 
    
    for(unsigned int i(0); i < algues.size(); i++){
        algues[i].step();
        if(algues[i].getAge() == max_life_alg){
            swap(algues[i], algues[algues.size()-1]);
            algues.pop_back();
            i -- ;//pour verifier le dernier element qu'on vient de mettre a la place i
        }
    }
}

void Simulation::step_coraux(){
    for(unsigned int i(0); i < coraux.size(); i++){
        coraux[i].step();

        if(coraux[i].getAge() == max_life_cor){
           coraux[i].mortCorail();
        }
    }
}

void Simulation::step_scav(){
    
    for(unsigned int i(0); i < scavengers.size(); i++){
        scavengers[i].step();
        if(scavengers[i].getAge() == max_life_sca){
            swap(scavengers[i], scavengers[scavengers.size()-1]);
            scavengers.pop_back();
            i -- ;//pour verifier le dernier element qu'on vient de mettre à la place i
        }
    }
}

//...................................................................................
//Methodes publiques :

Simulation::Simulation():erreur(false),random_algue(alg_birth_rate), 
                                                                random_pos(1,dmax-1){}

void Simulation::lecture(string fichier_entree) {
    
    string line;

    ifstream fichier(fichier_entree);
    if (!fichier.fail()) {
        reset();
        erreur = false;// si on le met dans reset on aura l'erreur suivie de correct 
        //file car quand on detecte l'erreur on appel reset
        while (getline(fichier >> ws, line)) {
            if (line[0] == '#')
                continue;

            istringstream data(line);
            switch_lecture(data);
            
            if(erreur){
                reset();//on met tout à 0 et on sort de la lecture
                break;
            }
        }
        if(!erreur){
            cout << message::success();
        }
    }
}

void Simulation::reset(){
    coraux.clear();
    scavengers.clear();
    algues.clear();
    e.seed(1); // reset la fonction random pour l'ouverture d'un nouveau fichier
    etat_lecture = NBA;
    nbMaj = 0;
    compteur = 0;
    compteur_seg = 0;
    nbAlg = 0;
    nbSca = 0;
    nbCor = 0;
}

//Getteurs............................................................................
unsigned int Simulation::getNbAlg()const{
    return algues.size();
}

unsigned int Simulation::getNbCor()const{
    return coraux.size();
}

unsigned int Simulation::getNbSca()const{
    return scavengers.size();
}

unsigned int Simulation::getNbMaj()const{
    return nbMaj;
}


//....................................................................................
void Simulation::affiche() const{

    for (const auto& corail : coraux) { // à voir si c'est mieux d'avoir variable Couleur ou plutot 2 fois le mm code avec des if
        const auto& segments = corail.getSegments();
        Carre carre(segments[0].getPoint(),d_cor);
        Couleur couleur_corail(bleu);// bleu ( = vivant) par défault
        if(!corail.getVieCor()){
            couleur_corail = noir; // noir (= mort) 
        }
        carre.affiche(couleur_corail, 1);
        for (const auto& seg : segments) {           
            seg.affiche(couleur_corail, 1);
        }
    }

    for(const auto& scav : scavengers){
        Cercle cercle(scav.getPos(),scav.getRayon());
        cercle.affiche(rouge, 1);
    }

    for(const auto& algue : algues){
        Cercle cercle(algue.getPos(),r_alg);
        cercle.affiche(vert, 1);
    }
}

string Simulation::data_to_string(){
    
    string stringAlg(to_string(algues.size()) + "\n");
    for (size_t i(0); i<algues.size();++i){
        stringAlg += algues[i].lifeform_to_string() + "\n";
        //une algue n'a pas d'attributs de classe en plus que lifeform donc 
        //la méthode lifeform_to_string suffit
    }

    string stringCor(to_string(coraux.size()) + "\n");
    for (size_t i(0); i < coraux.size(); ++i){
        stringCor += coraux[i].cor_to_string() + "\n";
    }

    string stringSca(to_string(scavengers.size()) + "\n");
    for (size_t i(0); i < scavengers.size(); ++i){
        stringSca += scavengers[i].sca_to_string() + "\n";
    }
    
    return stringAlg + "\n" + stringCor + "\n" + stringSca;
}

void Simulation::step(bool naissance){
    step_algues();
    step_coraux(); //pour le rendu 3
    step_scav(); //pour le rendu 3
    ++nbMaj;
    /*important de mettre naissance avant pour ne pas decaler random. Si on avait 
    commencer par random_algue(e) on lirait un bit de e a chaque mise a jour 
    meme si la check box etait désactivée*/
    if(naissance and random_algue(e)){
        S2d pos;
        pos.x = random_pos(e);
        pos.y = random_pos(e);
        Algue new_alg(pos);
        algues.push_back(new_alg);
    }
}
