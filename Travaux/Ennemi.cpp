#include "Ennemi.h"
#include <ctime>

Ennemi::Ennemi(){

}

Ennemi::~Ennemi(){

}

void Ennemi::DevienFort(){
    int test = rand() % 100 + 1;
    if (test <= 1) {

    }
    else {

    }
}

Vecteur Ennemi::Deplacement(Vecteur v){

}

void Ennemi::BoostVitesse(float n){
    vitesse = vitesse * n;
}