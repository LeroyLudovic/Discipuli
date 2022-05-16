#include "Tour.h"


Tour::Tour(Vecteur v,int t){
    type = t;
    position = v;
    chargement = 0;
    switch (t)
    {
    case 1 :    
        degat = 50;
        vitesse = 3;
        portee = 2;
        prix = 50;
        prixUpgrade = 100;
        upgrade = 0;
        break;
    case 2 :    
        degat = 200;
        vitesse = 1;
        portee = 2;
        prix = 65;
        prixUpgrade = 130;
        upgrade = 0;
        break;
    case 3 :    
        degat = 20;
        vitesse = 2.0;
        portee = 3;
        prix = 55;
        prixUpgrade = 110;
        upgrade = 0;
        break;
    case 4 :    
        degat = 0;
        vitesse = 0.5;
        portee = 1;
        prix = 75;
        prixUpgrade = 150;
        upgrade = 0;
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
    if(chargement > 70){
        chargement = 0;
        //std::cout<<chargement<<std::endl;
        return true;
    }
    //std::cout<<chargement;
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