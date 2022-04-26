#include "Tour.h"


Tour::Tour(Vecteur v,int t){
    type = t;
    position = v;
    switch (t)
    {
    case 0 :    
        degat = 50;
        vitesse = 3.0;
        portee = 2;
        prix = 50;
        break;
    }
    case 1 :    
        degat = 200;
        vitesse = 1.0;
        portee = 2;
        prix = 65;
        break;
    }
    case 2 :    
        degat = 100;
        vitesse = 1.0;
        portee = 3;
        prix = 55;
        break;
    }
    case 3 :    
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

int Tour::Vendre(){
    return 0;
}

int Tour::getX(){
    return position.x;
}

int Tour::getY(){
    return position.y;
}