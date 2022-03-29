#ifndef _TOUR
#define _TOUR

#include <iostream>

class Tour {

    private :

    int type;   
    int degat;
    float vitesse;
    int portee;
    int prix;

    public :

    Tour(int);

    ~Tour();

    void Amelioration();

    int Vendre();

};

#endif