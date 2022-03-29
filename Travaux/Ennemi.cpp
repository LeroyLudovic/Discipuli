#include "Ennemi.h"
#include <ctime>

Ennemi::Ennemi(){

}

Ennemi::~Ennemi(){

}

void Ennemi::DevienFort(){
    int test = rand() % 100 + 1;
    if (test <= 1) {
        //crée un ennemi fort
    }
    else {
        //crée un ennemei normal
    }
}

Vecteur Ennemi::Deplacement(Vecteur v){

}

void Ennemi::BoostVitesse(float n){
    vitesse = vitesse * n; 
}