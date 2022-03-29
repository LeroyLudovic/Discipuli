#include "Tour.h"


Tour::Tour(Vecteur v,int t){
    type = t;
    position = v;
    switch (t)
    {
    case 0 :    
        degat = 25;
        vitesse = 1.0;
        portee = 5;
        prix = 50;
        break;
    }
}

Tour::~Tour(){
    std::cout<<"Tour vendu"<<std::endl;
}

void Tour::Amelioration(){
}

int Tour::Vendre(){
    return 0;
}