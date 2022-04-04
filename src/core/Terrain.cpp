#include "Terrain.h"

#include <iostream>
using namespace std;

const char m_terrain1[5][20] = {
00000000000000000000,
00000000000000000000,
00000000000000000000,
00000000000000000000,
00000000000000000000,
};

Terrain::Terrain(){
    for(int x=0;x<Largeur;++x)
		for(int y=0;y<Longeur;++y)
			tab[x][y] = 'O';
}

Terrain::~Terrain(){
    cout<<"Terrain détruit"<<endl;
}

void Terrain::generation(){
    for(int i=0;i<Longeur/2;i++){
        tab[2][i] = ' ';
    }

    for(int i=(Longeur/2)-1;i<Longeur;i++){
        tab[3][i] = ' ';
    }
}

Vecteur Terrain::prochaineCase(Vecteur v){
    Vecteur test;
    if(tab[v.x][v.y + 1] == ' '){Vecteur a(0,1);return a;}

    for (int i=0;i<Largeur;i++){
        if(tab[i][v.y+1] == ' '){test = Vecteur(i,v.y+1);}
    }
    if(test.x > v.x){
        if(tab[v.x + 1][v.y] == ' '){Vecteur a(1,0);return a;}
    }else{
        if(tab[v.x - 1][v.y] == ' '){Vecteur a(1,0);return a;}
    }
    Vecteur n(0,0);
    return n;
}

char Terrain::getCase(int x, int y){
    return char(tab[x][y]);
}

int Terrain::getX(){
    return Largeur;
}

int Terrain::getY(){
    return Longeur;
}