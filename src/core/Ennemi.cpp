#include "Ennemi.h"
#include <ctime>

Ennemi::Ennemi(Vecteur v, int t, bool fort){
    type = t;
    position = v;
    switch (t){
        case 0 :
            vie = 100;
            vitesse = 1;
            if (fort){
                vie *= 2;
                vitesse *= 2;
                typeE = type;
            }
            break;
    }
    
    
}

Ennemi::~Ennemi(){

}

void Ennemi::lvlUp(int vague){
    vie = vie*(1+vague/10);
}

void Ennemi::Deplacement(Vecteur v){
    position = position + v;
}

void Ennemi::BoostVitesse(float n){
    vitesse = vitesse * n; 
}

int Ennemi::PosX(){
    return position.x;
}

int Ennemi::PosY(){
    return position.y;
}