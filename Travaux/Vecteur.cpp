#include "Vecteur.h"

Vecteur::Vecteur (){
    x = 0;
    y = 0;
}

Vecteur::Vecteur (int x, int y){
    this.x -> x;
    this.y -> y;
}

Vecteur::~Vecteur (){
    cout<<"Vecteur supprimé"<<endl;
}

const Vecteur::operator + (const Vecteur& op){
    Vecteur res;    

    res.x = x + op.x;
    res.y = y + op.y;

    return res;
}

friend std::ostream& Vecteur::operator << (std::ostream& flux, const Vecteur& d){
    std::cout<<d.x<<d.y<<std::endl;
}