#include "Terrain.h"

#include <iostream>
using namespace std;

Terrain::Terrain(){
    int test[Longeur][Longeur];
    for(int i;i<Longeur;i++){
        for(int j;j<Largeur;j++){
            test[i][j] = 0;
            
        }
        this->tab[][]= test;
    }
}

Terrain::~Terrain(){
    cout<<"Terrain détruit"<<endl;
}

void Terrain::generation(){
    for(int i=0;i<Longeur;i++){
        tab[5][i] = 1;
    }
}