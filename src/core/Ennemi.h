#ifndef _ENNEMI
#define _ENNEMI

#include "Vecteur.h"

class Ennemi {

    private :
    
    float vitesse;
    float chargement;

    public :


    unsigned int type;
    Vecteur position;
    double vie;

    Ennemi(Vecteur, int, bool);

    ~Ennemi();

    void lvlUp(int vague);

    bool Charg();

    void Deplacement (Vecteur v);

    void BoostVitesse(float n);

    int getX();

    int getY();

};

#endif