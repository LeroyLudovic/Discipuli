#include "Terrain.h"

#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

const char m_terrain1[10][38] = {
00000000000000000000000000000000000000,
00000000000000000000000000000000000000,
00000000000000000000000000000000000000,
00000000000000000000000000000000000000,
00000000000000000000000000000000000000,
00000000000000000000000000000000000000,
00000000000000000000000000000000000000,
00000000000000000000000000000000000000,
00000000000000000000000000000000000000,
00000000000000000000000000000000000000,

};

Terrain::Terrain(){
    depart = 0;
    for(int x=0;x<Largeur;++x)
		for(int y=0;y<Longeur;++y)
			tab[x][y] = 'O';
}

Terrain::~Terrain(){
    cout<<"Terrain détruit"<<endl;
}

void Terrain::generation(){
    srand (time(NULL));

    int avcX = 0;
    int avcY = 0;
    int val;
    int lon;

    val = rand() % 8 + 1;
    tab[val][0] = ' ';
    depart = val;
    avcY = val;

    while(avcX < 37){
        lon = rand() % (38 - (avcX+ 1));
        val = rand() % 8 + 1;
        std::cout<<lon<<' '<<val<<' '<<avcX<<' '<<avcY<<std::endl;
        for(int i = avcX+1;i<=lon+avcX;i++){
            tab[avcY][i] = ' ';
        }
        
        avcX += lon;

        if(lon > 0){
            if( val > avcY){
                for(int i = avcY;i<=val;i++){
                    tab[i][avcX ] = ' ';
                }
            }else if ( val < avcY) {
                for(int i = avcY;i>=val;i--){
                    tab[i][avcX] = ' ';
                }
            }
            avcY = val;
        }

        
        avcX += 1;
        
        tab[avcY][avcX] = ' ';
        std::cout<<"case rempli : "<<avcX<<' '<<avcY<<endl;
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
        if(tab[v.x - 1][v.y] == ' '){Vecteur a(-1,0);return a;}
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