//
// Created by kevin on 13/03/23.
//

#ifndef CODE_CELLULE_H
#define CODE_CELLULE_H

#include "vector"
#include <cstdlib>
#include <cmath>
#include <iostream>
#include "../struct/struct.h"

using namespace std;

typedef enum{DEFAILANTE,ALERTE,NORMAL} Etat;

class Cellule{
    public:
        Cellule();

        void addVoisin(Cellule* c);
        Cellule* getVoisin(int i);
        int countVoisin(Etat e);
        int nbVoisin();
        void resetVoisin();

        Etat getEtat();
        void setEtat(Etat e);

        void setNbVoisinMax(Voisinage v);

        virtual void transition();
        void nextT();

    protected:
        Etat etat = NORMAL;
        Etat etatSuivant = etat;
        vector<Cellule*> voisins;
        int nbVoisinMax;
};

#endif //CODE_CELLULE_H