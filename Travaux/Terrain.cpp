#include "Terrain.h"

#include <iostream>
using namespace std;

Terrain::Terrain(){
    for(int i;i<longeur;i++){
        for(int i;i<Largeur;i++){
            tab[i][j] = 0;
        }
    }
}

Terrain::~Terrain(){
    cout<<"Terain détruit"<<endl;
}

Terrain::generation(){
    for(int i=0;i<longeur;i++){
        tab[5][i] = 1;
    }
}