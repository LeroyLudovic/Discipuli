#ifndef _TERRAIN
#define _TERRAIN

#include "Vecteur.h"

class Terrain{
    private :

        const int Largeur = 5;
        const int Longeur = 20;
        int tab[5][20];
    
    public :

        Terrain();

        ~Terrain();

        void generation();

        Vecteur prochaineCase(Vecteur);

        int getCase(int,int);

        int getX();

        int getY();
};

    
#endif