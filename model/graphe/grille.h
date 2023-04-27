//
// Created by kevin on 21/03/23.
//

#ifndef CODE_GRILLE_H
#define CODE_GRILLE_H

#include "graphe.h"



class Grille : public Graphe {
public:
    Grille(int width, int height, typeCellule c);
    Grille(int width, int height, typeCellule c, double lambda);
    Grille(int width, int height, typeCellule c, double lambda, double* preCalcul);

    Cellule *getCellule(int i, int j);

    void affichageGrille();

    void MAJ();

    void setVoisinage(VoisinageClassique v);
    void setBordure(Bordure b);

    int getWidth();
    int getHeight();
    VoisinageClassique getVoisinage();

private:
    int width{};
    int height{};
    VoisinageClassique v;
    Bordure b;

    void Moore8();
    void Moore9();
    void VonNeumann();
    void Toom();
};


#endif //CODE_GRILLE_H
