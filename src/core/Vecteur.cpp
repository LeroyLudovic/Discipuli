#include "Vecteur.h"


Vecteur::Vecteur (){
    x = 0;
    y = 0;
}

Vecteur::Vecteur (int x, int y){
    this->x = x;
    this->y = y;
}

Vecteur::~Vecteur (){
    //std::cout<<"Vecteur supprimé"<<std::endl;
}

const Vecteur Vecteur::operator + (const Vecteur& op){
    Vecteur res;    

    res.x = res.x + op.x;
    res.y = res.y + op.y;

    return res;
}

const Vecteur Vecteur::operator = (const Vecteur& op){   

    x = op.x;
    y = op.y;

    return *this;
}

const Vecteur Vecteur::operator * (const int& op){   

    x = x*op;
    y = y*op;

    return *this;
}

std::ostream& operator << (std::ostream& flux, const Vecteur& d){
    std::cout<<'('<<d.x<<','<<d.y<<')';
    return flux;
}