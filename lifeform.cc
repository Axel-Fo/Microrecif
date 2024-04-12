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

//Classe Entite.......................................................................
//constructeur par défaut :
Lifeform::Lifeform(){}

//Classe Corail.......................................................................

void Corail::testSeg() const {
    for (long unsigned int i(0); i < segments.size(); i++) {
        unsigned int longeur = segments[i].getLongeur();
        // on teste si la longeur du segment est bien dans l'intervalle
        if (longeur < l_repro - l_seg_interne or longeur >= l_repro) {
            cout << message::segment_length_outside(id, longeur);
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

int Scavenger::getcorIdCible() const {
    return cor_id_cible;
}



bool Scavenger::getStatutSca() const {
    return statut_sca;
}

//Classe Algue........................................................................

Algue::Algue(istringstream& data) {
    data >> pos.x >> pos.y >> age;
}

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