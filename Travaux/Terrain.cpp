#include "Terrain.h"

#include <iostream>
using namespace std;

const int m_terrain1[10][10] = {
0000000000,
0000000000,
0000000000,
0000000000,
0000000000,
0000000000,
0000000000,
0000000000,
0000000000,
0000000000,



};

Terrain::Terrain(){
    Longeur = 10;
    Largeur = 10;
    for(int x=0;x<Longeur;++x)
		for(int y=0;y<Largeur;++y)
			tab[x][y] = m_terrain1[Longeur-1-y][x];
}

Terrain::~Terrain(){
    cout<<"Terrain détruit"<<endl;
}

void Terrain::generation(){
    for(int i=0;i<Longeur;i++){
        tab[5][i] = 1;
    }
}