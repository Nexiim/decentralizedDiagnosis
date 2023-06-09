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
#include <random>


using namespace std;



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

        void setNbVoisinMax(typeVoisinage v);

        virtual void transition();
        virtual void contamination();
        void nextT();
        
        Etat etat = NORMAL;
    protected:
        
        Etat etatSuivant = etat;
        vector<Cellule*> voisins;
        int nbVoisinMax;
};

#endif //CODE_CELLULE_H
