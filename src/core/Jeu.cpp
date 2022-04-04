#include "Jeu.h"

Jeu::Jeu(){
    fonds = 50;
    vague = 1;
    nbVagueFort = 0;
}

Jeu::~Jeu(){
    
}

void Jeu::creerTour(){
    bool create = false;

    while(create == false){

    }
}

void Jeu::ajoutTour(Vecteur a,int b){
    Tour t(a,b);
    tabT.push_back(t);
    fonds-=50;
}

void Jeu::creerVague(){
    for(int i=0;i<vague+2;i++){
        Vecteur pos(2,0);
        Ennemi ad(pos,0);
        tabE.push_back(ad);
    }
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

    if(tabE.size() < 1){
        creerVague();
    }
}


bool Jeu::actionClavier(const char touche){
    if (touche == 't') {

    }
} 