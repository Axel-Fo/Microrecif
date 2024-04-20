/*
* Fichier : lifeform.cc
* Auteurs : Nestor Guibentif et Axel Fouet
* Version : V1
*/
#include "lifeform.h"

using namespace std;

//Prototypes des fonctions utilisées par les methodes de classe:
void testPos(S2d pos);
void testAge(unsigned int age);
string seg_to_string(Segment seg);

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
    return "\t" + to_string(pos.x) + " " + to_string(pos.y) + " " + to_string(age);
}

void Lifeform::step(){
    age++;
}
//Classe Corail.......................................................................

void Corail::testSeg() const {
    for (long unsigned int i(0); i < segments.size(); i++) {
        unsigned int longueur = segments[i].getLongueur();
        // on teste si la longueur du segment est bien dans l'intervalle
        if (longueur < l_repro - l_seg_interne or longueur >= l_repro) {
            cout << message::segment_length_outside(id, longueur);
            std ::exit(EXIT_FAILURE);

        }// on teste si l'angle est dans le bon intervalle
        double angle = segments[i].getAngle();
        if (angle < -M_PI or angle > M_PI) {
            cout << message::segment_angle_outside(id, angle);
            std ::exit(EXIT_FAILURE);
        }
        // on teste si l'extremité du segment est bien dans le cadre
        S2d autre = segments[i].autre_pt();
        if (autre.x < 0 or autre.x > dmax or autre.y < 0 or autre.y > dmax) {
            cout << message::lifeform_computed_outside(id, autre.x, autre.y);
            std ::exit(EXIT_FAILURE);
        }
    }
}

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

void Corail::testCorail() const {
    testAge(age);
    testPos(pos);
    testSeg();
}

string Corail::cor_to_string() const{
    string stringSeg;
    for (size_t i(0); i < nb_seg; ++i){
        stringSeg += seg_to_string(segments[i]);
        stringSeg += "\n";
    }

    return lifeform_to_string() + to_string(id) + " " + to_string(vie_cor) + " " 
            + to_string(sens_rota) + " " + to_string(statut_dev) + " " 
            + to_string(nb_seg) + " " + stringSeg ;
}

// definition des geteurs pour le corail


int Corail::getId() const {
    return id;
}

bool Corail::getVieCor() const {
    return vie_cor;
}

bool Corail::getSensRota() const {
    return sens_rota;
}
bool Corail::getStatutDev() const {
    return statut_dev;
}

unsigned int Corail::getNbSeg() const {
    return nb_seg;
}

vector<Segment> Corail::getSegments() const {
    return segments;
}

//Classe Scavenger....................................................................

void Scavenger::testRayon() const {
    if (rayon < r_sca or rayon >= r_sca_repro) {
        cout << message::scavenger_radius_outside(rayon);
        std ::exit(EXIT_FAILURE);
    }
}

Scavenger::Scavenger(istringstream& data) {

    data >> pos.x >> pos.y >> age >> rayon >> statut_sca;

    if (statut_sca) {
        data >> cor_id_cible;
    }
}

void Scavenger::testScavenger() const {
    testAge(age);
    testPos(pos);
    testRayon();
}

string Scavenger::sca_to_string() const {
    string statut_et_cible("");
    //on veut convertir l'id en string uniquement si le scavenger MANGE
    if (statut_sca){
        statut_et_cible += to_string(statut_sca) + " " + to_string(cor_id_cible);
    }
    return lifeform_to_string() + " " + to_string(rayon) + " " + statut_et_cible;
}
int Scavenger::getcorIdCible() const {
    return cor_id_cible;
}



bool Scavenger::getStatutSca() const {
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

void Algue::testAlgue() const {
    testAge(age);
    testPos(pos);
}

//....................................................................................
//Definition des fonctions utilisées par plusieurs classes :

void testAge(unsigned int age) {
    // pas de test avec des valeurs negatives pour l'age
    if (age == 0) {
        cout << message::lifeform_age(age);
        std ::exit(EXIT_FAILURE);
    }
}

void testPos(S2d pos) { 

    if (pos.x < 1 or pos.x > dmax - 1 or pos.y < 1 or pos.y > dmax - 1) {
        cout << message::lifeform_center_outside(pos.x, pos.y);
        std ::exit(EXIT_FAILURE);
    }
}

string seg_to_string(Segment seg) {
    return to_string(seg.getAngle()) + " " + to_string(seg.getLongueur());
}