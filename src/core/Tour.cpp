#include "Tour.h"


Tour::Tour(Vecteur v,int t){
    type = t;
    position = v;
    switch (t)
    {
    case 0 :    
        degat = 50;
        vitesse = 1.0;
        portee = 1;
        prix = 50;
        typeT = type;
        break;
    }
}

Tour::~Tour(){
    //std::cout<<"Tour vendu"<<std::endl;
}

void Tour::Amelioration(){
    switch (type)
    {
    case 0 :
        degat*=1.5;
        portee+=1;
    }
}

int Tour::Vendre(){
    return 0;
}

int Tour::PosX(){
    return position.x;
}

int Tour::PosY(){
    return position.y;
}