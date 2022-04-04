#include "Jeu.h"


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
    }

    for(int i=0;i<int(tabE.size());i++){
        if(tabE[i].position.y == ter.getY()){
            tabE.erase(tabE.begin() + i);
        }
    }
}


bool Jeu::actionClavier(const char touche){
    
} 