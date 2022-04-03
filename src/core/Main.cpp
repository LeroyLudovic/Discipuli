#include "Vecteur.h"
#include "Terrain.h"
#include "Jeu.h"
#include <iostream>

using namespace std;

int main(){
    Terrain t;
    Jeu jeu;
    Vecteur a(2,1);
   for(int x=0;x<jeu.ter.getX();++x){
		for(int y=0;y<jeu.ter.getY();++y){
			cout<<jeu.ter.getCase(x,y);}}
    
    return 0;
}   