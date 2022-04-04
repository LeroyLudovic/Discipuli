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
    int 
    bool newVague;

    if(int(tabE.size()) == 0){
        creerVague();
    }

    for(int i=0;i<int(tabE.size());i++){
        if(tabE[i].position.y == ter.getY()-1){
            tabE.erase(tabE.begin() + i);
        }
    }
}


bool Jeu::actionClavier(const char touche){
    if (touche == 't') {

    }
}