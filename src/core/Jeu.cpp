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

void Jeu::Attaque(Ennemi &E,Tour T){
    E.vie -= T.degat;
}

int Jeu::GainFonds(Ennemi E){
    int res = 5*(vague + 1);
    return res;
}

void Jeu::actionsAutomatiques (){
    Vecteur direction;

    for(int x=0;x<int(tabE.size());++x){
        direction = ter.prochaineCase(tabE[x].position);
        tabE[x].Deplacement(direction);
    }

}


bool Jeu::actionClavier(const char touche){
    
} 