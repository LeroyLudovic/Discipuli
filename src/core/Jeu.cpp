#include "Jeu.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // WIN32

Jeu::Jeu(){
    fonds = 50;
    vague = 1;
    nbVagueFort = 0;
}

Jeu::~Jeu(){
    
}

void Jeu::ajoutTour(Vecteur a,int b){
    Tour t(a,b);
    tabT.push_back(t);
    fonds-=50;
}

void Jeu::creerVague(){

    Vecteur pos(2,0);
    Ennemi ad(pos,0);
    tabE.push_back(ad);
}

void Jeu::Attaque(Ennemi &E,Tour T){
    E.vie -= T.degat;
}

int Jeu::GainFonds(Ennemi E){
    int res = 5*(vague + 1);
    return res;
}


void Jeu::actionsAutomatiques (){
    Vecteur direction;

    if(int(tabE.size()) < vague+2){
        creerVague();
        #ifdef _WIN32
        		Sleep(500);
		#else
				usleep(500000);
        #endif // WIN32
    }

    for(int i=0;i<int(tabE.size());i++){
        if(tabE[i].position.y == ter.getY()){
            tabE.erase(tabE.begin() + i);
        }
    }
}


bool Jeu::actionClavier(const char touche){
    
} 