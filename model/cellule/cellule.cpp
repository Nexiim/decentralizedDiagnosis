//
// Created by kevin on 13/03/23.
//
#include "cellule.h"

/*Fonction lié au voisin de la cellule*/

Cellule::Cellule() {}

void Cellule::addVoisin(Cellule* c) {
    this->voisins.emplace_back(c);
}

Cellule* Cellule::getVoisin(int i){
    return this->voisins.at(i);
}


int Cellule::countVoisin(Etat e) {
    int somme =0;
    for(auto & voisin : this->voisins){
        if (voisin->getEtat() == e) somme++;
    }
    return somme;
}

int Cellule::nbVoisin(){
    return voisins.size();
}

void Cellule::resetVoisin() {
    this->voisins.clear();
}

/*Foncttion lié à l'état de la cellule*/
 Etat Cellule::getEtat(){
    return this->etat;
}
void Cellule::setEtat(Etat e){
    this->etat = e;
}

void Cellule::nextT() {
    if (this->etat != DEFAILANTE) {
        this->etat = this->etatSuivant;
    }
}

void Cellule::transition() {}

void Cellule::contamination() {
    if (countVoisin(ALERTE) > 0 || countVoisin(DEFAILANTE) > 0)
        this->etatSuivant = ALERTE;
}

void Cellule::setNbVoisinMax(typeVoisinage v) {
    if (v == typeVoisinage::MOORE8) this->nbVoisinMax = 8;
    else if (v == typeVoisinage::MOORE9) this->nbVoisinMax = 9;
    else if (v == typeVoisinage::TOOM) this->nbVoisinMax = 3;
    else if (v == typeVoisinage::VONNEUMAN) this->nbVoisinMax = 5;
    else if (v == typeVoisinage::VONNEUMAN4) this->nbVoisinMax = 4;
    else if (v == typeVoisinage::PLUSPROCHE) this->nbVoisinMax = this->nbVoisin();;
}





