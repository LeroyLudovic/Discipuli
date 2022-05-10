#include "Tour.h"


Tour::Tour(Vecteur v,int t){
    type = t;
    position = v;
    chargement = 0;
    switch (t)
    {
    case 1 :    
        degat = 50;
        vitesse = 5.0;
        portee = 2;
        prix = 50;
        break;
    case 2 :    
        degat = 200;
        vitesse = 1.0;
        portee = 2;
        prix = 65;
        break;
    case 3 :    
        degat = 100;
        vitesse = 1.0;
        portee = 3;
        prix = 55;
        break;
    case 4 :    
        degat = 0;
        vitesse = 0.5;
        portee = 1;
        prix = 75;
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

bool Tour::Charg(){
    chargement+=vitesse;
    if(chargement > 100){
        chargement = 0;
        return true;
    }
    return false;
}

int Tour::Vendre(){
    return 0;
}

int Tour::getX(){
    return position.x;
}

int Tour::getY(){
    return position.y;
}