#ifndef _TOUR
#define _TOUR

#include <iostream>

class Tour {

    private :

    const Vecteur position;
    int type;   
    int degat;
    float vitesse;
    int portee;
    int prix;

    public :

    Tour(Vecteur,int);

    ~Tour();

    void Amelioration();

    int Vendre();

};

#endif