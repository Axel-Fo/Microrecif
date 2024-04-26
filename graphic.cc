
#include "graphic_gui.h"
#include <vector>
#include <iostream>
#include <cmath>

static const Cairo::RefPtr<Cairo::Context>* ptcr(nullptr);

// pas dans graphic.h pour eviter trop de dependance dans le modelon ne veut pas que 
//notre model puisse avoir accès au Rgb il doit utiliser l'enum Couleur
struct Rgb{
    double r;
    double g;
    double b;
};
// le code des couleur en Rgb de blanc,bleu,rouge,vert,gris,noir
// pour passer de l'enum Couleur a du Rgb ce que demande gtkmm
std::vector<Rgb> couleur_rgb = {Rgb{1,1,1},Rgb{0,0,1},Rgb{1,0,0},
                                Rgb{0,1,0},Rgb{0.5,0.5,0.5},Rgb{0,0,0}};

void graphic_set_context( const Cairo::RefPtr<Cairo::Context>& cr){
    ptcr = &cr;
}

void dessin_ligne(double x1, double y1,double x2, double y2,
                                                Couleur couleur, double largeur){
    (*ptcr)->set_line_width(largeur);
    (*ptcr)->set_source_rgb(couleur_rgb[couleur].r,couleur_rgb[couleur].g,
                                                          couleur_rgb[couleur].b);
    (*ptcr)->move_to(x1,y1);
    (*ptcr)->line_to(x2,y2);

    (*ptcr)->stroke();
}

void dessin_carre(double xc, double yc, double arete, Couleur couleur, double largeur){
    (*ptcr)->set_line_width(largeur);
    (*ptcr)->set_source_rgb(couleur_rgb[couleur].r, couleur_rgb[couleur].g,
                                                    couleur_rgb[couleur].b);
    (*ptcr)->rectangle(xc-arete/2,yc-arete/2,arete,arete);

    (*ptcr)->stroke();
}

void dessin_cercle(double xc, double yc, double rayon, 
                                        Couleur couleur, double largeur){
    (*ptcr)->set_line_width(largeur);
    (*ptcr)->set_source_rgb(couleur_rgb[couleur].r,couleur_rgb[couleur].g,
                                            couleur_rgb[couleur].b);
    (*ptcr)->arc(xc, yc, rayon, 0.0, 2.0 * M_PI);
    (*ptcr)->stroke();

}