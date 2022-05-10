#ifndef _TERRAIN
#define _TERRAIN

#include "Vecteur.h"

class Terrain{
    private :

        const int Largeur = 10;
        const int Longeur = 38;
    
    public :

        char tab[10][38];
        int depart;

        Terrain();

        ~Terrain();

        void generation();

        Vecteur prochaineCase(Vecteur);

        char getCase(int,int);

        int getX();

        int getY();
};

    
#endif