/*
* Fichier : lifeform.cc
* Auteurs : Nestor Guibentif(~55) et Axel Fouet(~45)
* Version : V2
*/
#include "lifeform.h"

using namespace std;

//Prototypes des fonctions utilisées par les methodes de classe:
bool testPos(S2d pos);
bool testAge(unsigned int age);
string seg_to_string(Segment seg);

//Prototypes des fonctions utilisées pour surcharger:
std::istream& operator>>(std::istream& in, Statut_sca& statut);
std::istream& operator>>(std::istream& in, Statut_dev& statut);
std::istream& operator>>(std::istream& in, Dir_rot_cor& dir);
std::istream& operator>>(std::istream& in, Statut_cor& statut);

//Classe Lifeform.....................................................................
//constructeur par défaut :
Lifeform::Lifeform(){}
Lifeform::Lifeform(S2d pos, unsigned int age):pos(pos), age(age){}

Lifeform::~Lifeform(){}

unsigned int Lifeform::getAge()const{
    return age;
}

S2d Lifeform::getPos() const {
    return pos;
}

string Lifeform::lifeform_to_string() const {
    return "    " + to_string(pos.x) + " " + to_string(pos.y) + " " + to_string(age);
}

void Lifeform::step(){
    age++;
}

//Classe Corail.......................................................................

bool Corail::testSeg() const {
    for (long unsigned int i(0); i < segments.size(); i++) {
        unsigned int longueur = segments[i].getLongueur();
        // on teste si la longueur du segment est bien dans l'intervalle
        if (longueur < l_repro - l_seg_interne or longueur >= l_repro) {
            cout << message::segment_length_outside(id, longueur);
            return true;

        }// on teste si l'angle est dans le bon intervalle
        double angle = segments[i].getAngle();
        if (angle < -M_PI or angle > M_PI) {
            cout << message::segment_angle_outside(id, angle);
            return true;
        }
        // on teste si l'extremité du segment est bien dans le cadre
        S2d autre = segments[i].autre_pt();
        if (autre.x < 0 or autre.x > dmax or autre.y < 0 or autre.y > dmax) {
            cout << message::lifeform_computed_outside(id, autre.x, autre.y);
            return true;
        }
    }
    return false;
}

//Methodes publiques : 
Corail::Corail(istringstream& data) {

    data >> pos.x >> pos.y >> age >> id >> vie_cor 
         >> sens_rota >> statut_dev >> nb_seg;

    // tant qu'un corail ne possède pas de segments son extremite est sa base :
    extremite = pos;
}

//Méthodes publiques corail:
void Corail::ajout_seg(istringstream& data) {
    double angle;
    unsigned int longueur;
    data >> angle >> longueur;
    Segment new_segment(extremite, angle, longueur);
    segments.push_back(new_segment);
    // nouvelle extremite
    extremite = new_segment.autre_pt();
}

void Corail::mortCorail(){
    vie_cor = DEAD;
}

bool Corail::testCorail() const {
    if(testAge(age) or testPos(pos) or testSeg()){
        return true;
    }
    return false;
}

string Corail::cor_to_string() const{
    string stringSeg;
    
    for (size_t i(0); i < nb_seg; ++i){
        stringSeg += "\n";
        stringSeg += seg_to_string(segments[i]);
    }

    return lifeform_to_string() + " " + to_string(id) + " " + to_string(vie_cor) + " " 
            + to_string(sens_rota) + " " + to_string(statut_dev) + " " 
            + to_string(nb_seg) + " " + stringSeg ;
}

// Définition des geteurs pour le corail :

int Corail::getId() const {
    return id;
}

Statut_cor Corail::getVieCor() const {
    return vie_cor;
}

Dir_rot_cor Corail::getSensRota() const {
    return sens_rota;
}
Statut_dev Corail::getStatutDev() const {
    return statut_dev;
}

unsigned int Corail::getNbSeg() const {
    return nb_seg;
}

vector<Segment> Corail::getSegments() const {
    return segments;
}

//Classe Scavenger....................................................................

bool Scavenger::testRayon() const {
    if (rayon < r_sca or rayon >= r_sca_repro) {
        cout << message::scavenger_radius_outside(rayon);
        return true;
    }
    return false;
}

Scavenger::Scavenger(istringstream& data) {

    data >> pos.x >> pos.y >> age >> rayon >> statut_sca;

    if (statut_sca) {
        data >> cor_id_cible;
    }
}

bool Scavenger::testScavenger() const {
    if(testAge(age) or testPos(pos) or testRayon()){
        return true;
    }
    return false;
    
}

string Scavenger::sca_to_string() const {
    
    if (statut_sca){ //l'id du corail cible est là uniquement si le scavenger MANGE
        return lifeform_to_string() + " " + to_string(rayon) + " " 
            + to_string(statut_sca) + " " + to_string(cor_id_cible);
    }

    return lifeform_to_string() + " " + to_string(rayon) + " " + to_string(statut_sca);
}

int Scavenger::getCorIdCible() const {
    return cor_id_cible;
}

Statut_sca Scavenger::getStatutSca() const {
    return statut_sca;
}
double Scavenger::getRayon() const {
    return rayon;
}


//Classe Algue........................................................................

Algue::Algue(istringstream& data) {
    data >> pos.x >> pos.y >> age;
}

Algue::Algue(S2d pos):Lifeform(pos) {} 

bool Algue::testAlgue() const {
    if(testAge(age) or testPos(pos)){
        return true;
    }
    return false;
}

//....................................................................................
//Definition des fonctions utilisées par plusieurs classes :

bool testAge(unsigned int age) {
    // pas de test avec des valeurs negatives pour l'age
    if (age == 0) {
        cout << message::lifeform_age(age);
        return true;
    }
    return false;
}

bool testPos(S2d pos) { 

    if (pos.x < 1 or pos.x > dmax - 1 or pos.y < 1 or pos.y > dmax - 1) {
        cout << message::lifeform_center_outside(pos.x, pos.y);
        return true;
    }
    return false;
}


string seg_to_string(Segment seg) {
    return "        " + to_string(seg.getAngle()) + " "
                      + to_string(seg.getLongueur());
}

//................on surcharge l'operateur >>........................................//
//pour pouvoir dirrectement utiliser l'opérateur >> avec les types: Statut_sca, 
//Statut_dev, Dir_rot_cor, Statut_cor dans les different constructeurs
std::istream& operator>>(std::istream& in, Statut_sca& statut) {
    bool mange;
    in>>mange;
    if(mange){
        statut = MANGE;
    }else{
        statut = LIBRE;
    }
    return in;
}

std::istream& operator>>(std::istream& in, Statut_dev& statut) {
    bool repro;
    in>>repro;
    if(repro){
        statut = REPRO;
    }else{
        statut = EXTEND;
    }
    return in;
}

std::istream& operator>>(std::istream& in, Dir_rot_cor& dir) {
    bool inv;
    in>>inv;
    if(inv){
        dir = INVTRIGO;
    }else{
        dir = TRIGO;
    }
    return in;
}

std::istream& operator>>(std::istream& in, Statut_cor& statut) {
    bool alive;
    in>>alive;
    if(alive){
        statut = ALIVE;
    }else{
        statut = DEAD;
    }
    return in;
}