/*
* Fichier : simulation.cc
* Auteurs : Nestor Guibentif(~60) et Axel Fouet(~40)
* Version : V2
*/
#include "simulation.h"

using namespace std;

//Classe Simulation...................................................................

//Méthodes private :

bool Simulation::id_exist(int id) {
    for (long unsigned int i(0); i < coraux.size(); i++) {
        if (coraux[i].getId() == id) {
            return true;
        }
    }
    return false;
}

bool Simulation::test_id(Corail corail) {
    if (id_exist(corail.getId())) {
        cout << message::lifeform_duplicated_id(corail.getId());
        return true;
    }
    return false;
}

bool Simulation::test_id_mange(Scavenger scav) {
    if (scav.getStatutSca()) {
        if (!id_exist(scav.getCorIdCible())) {
            cout << message::lifeform_invalid_id(scav.getCorIdCible());
            return true;
        }
    } 
    return false;
}
bool Simulation::test_coll_seg(Segment seg,bool lecture,unsigned int index, int id){
    //le booleen lecture est la pour ne plus cout les erreurs de collision si on est 
    //en mode simulation on veut juste recuperer le booleen test collision
    
    Etat_epsil_zero etat = NOT_EPSIL;
    if(!lecture) etat = IS_EPSIL;
    
    for (unsigned int i(0); i < coraux.size(); i++) {
        for (unsigned int j(0); j < coraux[i].getSegments().size(); j++) {  
            
            /*on ne veut pas tester la collision entre deux segments qui se précèdent 
            sur le mm corail mais on teste avec le else si ils ne sont pas repliés 
            l'un sur l'autre*/
            if (coraux[i].getId() != id or !(index == j+1 or index == j-1 or 
                                                             index == j)){
                if (seg.intersect((coraux[i].getSegments())[j], etat)) {
                    
                    if(lecture){
                        cout << message::segment_collision(coraux[i].getId(), 
                                                           j, id, index);
                    }
                    return true;                    
                }
            }
        }
    }
    return false;
}
bool Simulation::test_collision(Corail corail){
    
    vector<Segment> segs = corail.getSegments();
    
    for (unsigned int i(0); i < segs.size(); i++) {
        
        if(test_coll_seg(segs[i],true,i, corail.getId())) return true;
        
        //on test la superposition avec le segement suivant si il existe
        if(i + 1 < segs.size()){
            if (segs[i].intersect_mm(segs[i+1])) {
                cout << message::segment_superposition(corail.getId(),i,i+1);
                return true;
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
            erreur = test_id(new_corail);
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
                if(coraux.back().testCorail() or test_collision(coraux.back()))
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
            if(new_sca.testScavenger() or test_id_mange(new_sca))
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
        algues[i].step_age();
        if(algues[i].getAge() == max_life_alg){
            mort_alg(i);            
            i -- ;//pour verifier le dernier element qu'on vient de mettre a la place i
        }
    }
}

void Simulation::step_coraux(){//a rétrécir pcq trop longue + voir si il faut tester
                               //le cas ou on a pas de scavenger dans la simulation quand mort corail
    
    //pour gérer le cas ou plusieurs coraux meurent en même temps :
    /*vector<int> index_dead_cor;*/
    
    for(unsigned int i(0); i < coraux.size(); i++){
        coraux[i].step_age();//le corail mort sera quand même incrémenté en age :/
        
        if(coraux[i].getAge() == max_life_cor) {
           coraux[i].mortCorail();
           coraux[i].majExtremite();
        }

        if (coraux[i].getVieCor() == ALIVE){// il mange que si il est vivant
            
           if(coraux[i].getDernierSeg().getLongueur() >= l_repro){

                dev_corail(coraux[i]);
            
            }else{
                double delta_ang(0);
                if(coraux[i].getSensRota() == TRIGO){
                    delta_ang  = delta_rot;
                }else{//INVTRIGO
                    delta_ang  = -delta_rot;
                }
                int indexAlgCandidat(-1); // initialiser a un index qui n'existe pas
                
                // met aussi a jour l'angle et indexAlgCandidat
                bool aManger = candidat_mange(coraux[i], delta_ang, indexAlgCandidat);
                
                if(test_collision_simu(coraux[i],delta_ang,aManger)){
                    coraux[i].change_sens();
                }else{
                    coraux[i].rotaCorail(delta_ang);
                    if(aManger){
                        mort_alg(indexAlgCandidat);
                        coraux[i].tailleCorChange(delta_l);
                    }
                }

            }
        }
    }
}

void Simulation::dev_corail(Corail& cor){
    if(cor.getStatutDev() == EXTEND){
        cor.change_statut_dev();
        cor.tailleCorChange(-(double)(l_repro-l_seg_interne));
        Segment new_seg(cor.getExtremite(),cor.getDernierSeg().getAngle()
                                        ,(double)(l_repro-l_seg_interne));
        cor.ajout_seg(new_seg);
    }else{//REPRO
        cor.change_statut_dev();
        cor.tailleCorChange(-(double)(l_repro/2));
        Corail new_cor(cor, 1);// change id a refaire
        coraux.push_back(new_cor);

    }
}
bool Simulation::candidat_mange(Corail& cor, double& delta_ang,int& indexAlgCandidat){

    
    for(unsigned int j(0); j < algues.size(); j++){

        // on utilise des segments pour pouvoir réutiliser les fct d'angles de shape     
        Segment dernierSegCor(cor.getDernierSeg());
        Segment corailAlgue(dernierSegCor.getPoint(), algues[j].getPos());
                
        if ((corailAlgue.getLongueur() <= dernierSegCor.getLongueur()) and 
            (abs(dernierSegCor.ecart_ang_mm_pt(corailAlgue)) < abs(delta_ang)) and
            (dernierSegCor.ecart_ang_mm_pt(corailAlgue)*delta_ang > 0)){
            // pour que l'angle soit bon il doit être plus petit que delta rot en val 
            //absolue et de même signe
            indexAlgCandidat = j;
            delta_ang = dernierSegCor.ecart_ang_mm_pt(corailAlgue);
        }
    }
    /*on est obligé de sortire aussi l'index de l'algue et le delta ang par ref car on 
    ne sait pas encore si le corail peut la manger, on n'a pas encore tester les 
    collisions*/
    if(indexAlgCandidat != -1){// si l'index n'est plus a -1 il y a une algue a manger
        return true;
    }else{
        return false;
    }
}

bool Simulation::test_collision_simu(Corail& cor, double del_ang, bool mange){
    
    bool collision = false;
    if(mange){
        cor.tailleCorChange(delta_l);
    }
    double ecart_av = 0;
    if(cor.getNbSeg() >=2 )
        ecart_av = cor.getDernierSeg().ecart_ang(cor.getSegments()[cor.getNbSeg()-2]);
    
    cor.rotaCorail(del_ang);
    if(cor.getNbSeg() >=2 ){
        double ecart_ap = 
                cor.getDernierSeg().ecart_ang(cor.getSegments()[cor.getNbSeg()-2]);
    //si l'ecart angulaire change de signe et est autour de 0 il est repiler sur lui mm
        if(ecart_av*ecart_ap < 0 and abs(ecart_av) < M_PI/2) collision = true;

    }





    
    if(test_coll_seg(cor.getDernierSeg(),false,cor.getNbSeg()-1,cor.getId())) {
        collision = true;
    }
        
            // on annule des deplacements après avoir fais les tests
    cor.rotaCorail(-del_ang);
    if(mange){
        cor.tailleCorChange(-(double)delta_l);
        //on doit mettre en double pour qu'il puisse être negatif
    }
    return collision;
}

void Simulation::step_scav(){
    
    for(unsigned int i(0); i < scavengers.size(); i++){
        scavengers[i].step_age();
        if(scavengers[i].getAge() == max_life_sca){
            swap(scavengers[i], scavengers[scavengers.size()-1]);
            scavengers.pop_back();
            i -- ;//pour verifier le dernier element qu'on vient de mettre à la place i
        }else if(scavengers[i].getStatutSca() == MANGE){
                scaMange(scavengers[i], scavengers[i].getCorIdCible());
        }
    }

}

void Simulation::scaMange(Scavenger sca, int id){
    int index;
    for(unsigned int i(0); i < coraux.size(); i++){
        if(coraux[i].getId() == id){
            index = i;
            break;
        }
    }
    if ((sca.getRayon() + delta_r_sca) < r_sca_repro ){
        sca.scaGrandit(delta_r_sca);
        sca.scaMouvement(coraux[index].getDernierSeg().getPoint(), delta_l);
        coraux[index].tailleCorChange(-delta_l);
    }else{//le scavenger se reproduit alors
        //on créé un scavenger a la pos actuelle puis on se déplace:
        Scavenger new_sca(sca.getPos());
        scavengers.push_back(new_sca);
        sca.resetTaille();
        sca.scaMouvement(coraux[index].getDernierSeg().getPoint(), delta_l);
    }
    //si le corail est mangé il disparait pour le prochain step :
    if (coraux[index].getSegments()[0].getLongueur() == 0 ){
        sca.sca_statut_change();
        swap(coraux[index], coraux[coraux.size()-1]);
        coraux.pop_back();
    }
}

void Simulation::mort_alg(int index){
    swap(algues[index], algues[algues.size()-1]);
    algues.pop_back();
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
    step_coraux(); 
    step_scav(); 
    ++nbMaj;
    /*important de mettre naissance avant pour ne pas decaler random. Si on avait 
    commencé par random_algue(e) on lirait un bit de e a chaque mise a jour 
    meme si la check box etait désactivée*/
    if(naissance and random_algue(e)){
        S2d pos;
        pos.x = random_pos(e);
        pos.y = random_pos(e);
        Algue new_alg(pos);
        algues.push_back(new_alg);
    }
}
