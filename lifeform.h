#ifndef LIFEFORM_H_INCLUDED
#define LIFEFORM_H_INCLUDED

#include <string>



class Prop_entite {
    private :
    S2d pos;
    unsigned int age;
}

enum Etat_vie{

    DEAD, ALIVE

};
enum Etat_rot{

    INVTRIGO, TRIGO

};
enum Etat_dev{

    EXTEND, REPRO

};
class Scavenger{
    Prop_entite proprietes;
    bool etat; //0 pour LIBRE et 1 pour MANGE(peut être à changer)
    double rayon;
};

class Corail{
    Prop_entite proprietes;
    int id;
    bool sens_rota; //par ex 1 pour trigo, 0 pour inv trigo, eventuellement changer en string ou enum ?
    bool statut_dev;//0 pour extend, 1 pour repro
    bool statut_vie; //0 pour dead et 1 pour alive
    unsigned int nb_seg;
}

class Algue{
    Prop_entite proprietes;
}
#endif // LIFEFORM_H_INCLUDED