#ifndef GRAPHIC_H
#define GRAPHIC_H


enum Couleur{blanc, bleu, rouge, vert, gris, noir};

void dessin_ligne(double x1, double y1,double x2, double y2,
                  Couleur couleur,double largeur);
void dessin_carre(double xc, double yc, double arrete,Couleur couleur,double largeur);
void dessin_cercle(double xc, double yc, double rayon,Couleur couleur,double largeur);

#endif // GRAPHIC_H