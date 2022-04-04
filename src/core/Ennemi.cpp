#include "Ennemi.h"
#include <ctime>

Ennemi::Ennemi(Vecteur v, int t){
    type = t;
    position = v;
    switch (t){
        case 0 :
            vie = 100;
            vitesse = 1;
            break;
    }
    
    
}

Ennemi::~Ennemi(){

}

void Ennemi::DevienFort(){
    int test = rand() % 100 + 1;
    if (test <= 1) {
        //crée un ennemi fort
    }
    else {
        //crée un ennemi normal
    }
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