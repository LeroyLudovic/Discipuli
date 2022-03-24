#include "Vecteur.h"

Vecteur::Vecteur(){
    x = 0;
    y = 0;
}

Vecteur::Vecteur(int x, int y){
    this.x -> x;
    this.y -> y;
}

Vecteur::~Vecteur(){
    cout<<"Vecteur supprimé"<<endl;
}

Vecteur::const oparator + (const Vecteur& op){
    Vecteur res;

    res.x = x + op.x;
    res.y = y + op.y;

    return res;
}

Vecteur::friend std::ostream& operator << (std::ostream& flux, const Date& d){
    
}