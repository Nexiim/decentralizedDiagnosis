//
// Created by kevin on 20/03/23.
//

#include "simulationQuoromD.h"


SimulationQuoromD::SimulationQuoromD(int *T, int nbTest, double *probaDef, Voisinage v, double threshold, int height,
                                     int width, int *lambda) : Simulation(T, nbTest, probaDef, threshold) {
    this->v = v;
    this->lambda = lambda;
    this->nbTest = nbTest;
    this->G = new Grille(width, height,typeCellue::QUOROMD);
    this->G->setVoisinage(v);
    this->listExp = nullptr;

}

void SimulationQuoromD::start() {
    int nbIter = 0;
    int succes;

    for (int i = 1; i <= T[0]; i++) {
        for (int a = 1; a <= lambda[0]; a++) {
            G->setLamba(lambda[a]);
            this->openFile("QuoromDLambda" + to_string(lambda[a]) + "T" + to_string(T[i]) + ".txt");
            this->writeFile(to_string(1));
            if (this->file) { // si l'ouverture a réussi
                for (int j = 1; j <= probaDef[0]; j++) {
                    G->Graphe::reset();
                    G->setVoisinage(v);
                    G->setCelluleDef(probaDef[i]);
                    nbIter = 0;
                    succes = 0;

                    for (int k = 0; k < nbTest; k++) {
                        while (nbIter < T[i]) {
                            G->MAJGrille();
                            if (G->seuil(threshold)) {
                                succes++;
                                break;
                            }
                            nbIter++;
                        }
                    }
                    string s = to_string(probaDef[j]) + "," + to_string((double) succes / (double) nbTest);
                    this->writeFile(s);
                }
            }
            this->closeFile();
        }
    }
}

void SimulationQuoromD::start(Focus f) {
    if (f == LAMBDA) simulationLambda();
    else if (f == TMPMAX) simulationT();
    else if (f == PROBADEF) simulationProbadef();
}

void SimulationQuoromD::simulationProbadef() {

}

void SimulationQuoromD::simulationLambda() {
    int nbIter;
    int succes;
    for (int a = 1; a <= T[0]; a++) {
        this->openFile("QuoromD" + ToString(v) + "LambdamultipleT"+to_string(T[a])+".txt");
        if (this->file) { // si l'ouverture a réussi
            this->writeFile(to_string(T[0]));
            for (int i = 1; i <= lambda[0]; i++) {
                this->writeFile(to_string(lambda[i]));
                for (int j = 1; j <= probaDef[0]; j++) {
                    succes = 0;
                    for (int k = 0; k < nbTest; k++) {
                        nbIter = 0;
                        //On réinitialise le graphe correctement
                        G->Graphe::reset();
                        G->setVoisinage(v);
                        G->setCelluleDef(probaDef[j]);
                        G->setLamba(lambda[i]);

                        while (nbIter < T[a]) {
                            G->MAJGrille();
                            if (G->seuil(threshold)) {
                                succes++;
                                break;
                            }
                            nbIter++;
                        }
                    }
                    string s = to_string(probaDef[j]) + "," + to_string((double) succes / (double) nbTest) + "," +
                               to_string(nbIter);
                    this->writeFile(s);
                }
                this->writeFile("-");
            }
        }
    }
}

void SimulationQuoromD::simulationT() {
    int nbIter;
    int succes;

    for (int a = 1; a <= lambda[0]; a++) {
        //précalcule des différentes valeurs de probabilité pour QuoromD
        if (listExp != nullptr) free(listExp);
        calculeExp(lambda[a],v);
        //création de fichier
        this->openFile("QuoromD" + ToString(v) + "Lambda" + to_string(lambda[a]) + "Tmultiple.txt");
        if (this->file) { // si l'ouverture a réussi
            //on écrit le nombre de TMPMAX étudié
            this->writeFile(to_string(T[0]));
            for (int i = 1; i <= T[0]; i++) {
                //on écrit le TMPMAX étudié
                this->writeFile(to_string(T[i]));
                for (int j = 1; j <= probaDef[0]; j++) {
                    succes = 0;
                    for (int k = 0; k < nbTest; k++) {
                        //cout << "test k :" << k << " thread :" << omp_get_thread_num() << endl;
                        nbIter = 0;
                        //On réinitialise le graphe correctement
                        G->reset(probaDef[j], lambda[a], listExp);

                        while (nbIter < T[i]) {
                            G->MAJGrille();
                            if (G->seuil(threshold)) {
                                succes++;
                                break;
                            }
                            nbIter++;
                        }
                    }
                    
                    //on écrit le probabilité testé, la proba de réussite et le nombre d'itération pour la derniére simulation
                    string s = to_string(probaDef[j]) + "," + to_string((double) succes / (double) nbTest) + "," +
                               to_string(nbIter);
                    this->writeFile(s);
                }
                this->writeFile("-");
            }
        }
        this->file.close();
    }
}

void SimulationQuoromD::startDensitySim(Focus f) {
    if (f == LAMBDA) simulationDensityLambda();
    else if (f == TMPMAX) simulationDensityT();
    else if (f == PROBADEF) simulationDensityProbadef();
}

void SimulationQuoromD::simulationDensityT() {

}

void SimulationQuoromD::simulationDensityProbadef() {

}

void SimulationQuoromD::simulationDensityLambda() {

}

void SimulationQuoromD::startDensitySim() {
    for (int i = 1; i <= T[0]; i++) {
        for (int a = 1; a <= lambda[0]; a++) {
            for (int j = 1; j <= probaDef[0]; j++) {
                this->openFile("QuoromDDensity"+ ToString(v)+"Lambda" + to_string(lambda[a]) + "T" + to_string(T[i]) +"ProbaDef"+to_string(probaDef[j]) +".txt");
                this->writeFile(to_string(1));
                if (this->file) { // si l'ouverture a réussi
                    G->Graphe::reset();
                    G->setVoisinage(v);
                    G->setCelluleDef(probaDef[i]);
                    G->setLamba(lambda[a]);

                    string s = to_string(0) + "," + to_string((double)G->nbAlerte()/((double)(G->nbCellule()-G->nbDef())));
                    this->writeFile(s);

                    int nbIter = 1;
                    int cpt =11;
                    for (int k = 0; k < nbTest; k++) {
                        while (nbIter < T[i]) {
                            G->MAJGrille();
                            if (cpt < 10){
                                cpt++;
                                if (cpt == 10) nbIter = T[i];
                            }
                            else if (G->seuil(threshold)) {
                                string s = to_string(nbIter) + "," + to_string((double)G->nbAlerte()/((double)(G->nbCellule()-G->nbDef())));
                                this->writeFile(s);
                                cpt =0;
                                break;
                            }
                            string s = to_string(nbIter) + "," + to_string((double)G->nbAlerte()/((double)(G->nbCellule()-G->nbDef())));
                            this->writeFile(s);
                            nbIter++;
                        }
                    }
                }
            }
            this->closeFile();
        }
    }
}

void SimulationQuoromD::calculeExp(int lambda, Voisinage v) {
    int nbVoisin = 0;
    if (v == Voisinage::MOORE8) nbVoisin = 8;
    else if (v == Voisinage::MOORE9) nbVoisin = 9;
    else if (v == Voisinage::TOOM) nbVoisin = 3;
    else if (v == Voisinage::VONNEUMAN) nbVoisin = 4;

    this->listExp = (double*)malloc(sizeof(double) * (nbVoisin+1) * (nbVoisin+1));
    // nombre de cellules voisinnes normales
    for (int i =0; i <= nbVoisin; i++){
        //nombre de cellules voisines
        for( int j = 1; j <= nbVoisin; j++){
            double wn =  exp(lambda * ((double)i/j));
            double wad = exp(lambda * ((double)(j-i)/j));
            int position = j*(nbVoisin+1) + i;
            this->listExp[position] = wn/(wn+wad);

            //cout << "i:"<< i <<" j:" << j << " v:"<< this->listExp[(j*(nbVoisin+1)) + i]<< endl;
        }
    }
}