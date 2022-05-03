#include "Ennemi.h"
#include <ctime>

Ennemi::Ennemi(Vecteur v, int t, bool fort){
    type = t;
    position = v;
    chargement = 0;
    switch (t){
        case 0 :
            vie = 200;
            vitesse = 1;
            if (fort){
                vie *= 2.5;
                vitesse *= 1;
            }
            break;
        case 1 :
            vie = 50;
            vitesse = 3;
            if (fort){
                vie *= 1;
                vitesse *= 2;
            }
            break;
        case 2 :
            vie = 100;
            vitesse = 1;
            if (fort){
                vie *= 2;
                vitesse *= 2;
            }
            break;
        case 3 :
            vie = 50;
            vitesse = 1;
            if (fort){
                vie *= 1.5;
                vitesse *= 1.5;
            }
            break;
    }
    
    
}

Ennemi::~Ennemi(){

}

void Ennemi::lvlUp(int vague){
    vie = vie*(1+vague/10);
}

bool Ennemi::Charg(){
    chargement+=vitesse;
    if(chargement > 20){
        chargement = 0;
        return true;
    }
    return false;
}

void Ennemi::Deplacement(Vecteur v){
    position = position + v;
}

void Ennemi::BoostVitesse(float n){
    vitesse = vitesse * n; 
}

int Ennemi::getX(){
    return position.x;
}

int Ennemi::getY(){
    return position.y;
}