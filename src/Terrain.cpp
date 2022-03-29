#include "Terrain.h"

#include <iostream>
using namespace std;

const int m_terrain1[5][20] = {
00000000000000000000,
00000000000000000000,
00000000000000000000,
00000000000000000000,
00000000000000000000,
};

Terrain::Terrain(){
    Largeur = 5;
    Longeur = 20;
    for(int x=0;x<Largeur;++x)
		for(int y=0;y<Longeur;++y)
			tab[x][y] = m_terrain1[x][y];
}

Terrain::~Terrain(){
    cout<<"Terrain détruit"<<endl;
}

void Terrain::generation(){
    for(int i=0;i<Longeur/2;i++){
        tab[2][i] = 1;
    }

    for(int i=(Longeur/2)-1;i<Longeur;i++){
        tab[3][i] = 1;
    }
}