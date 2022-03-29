#ifndef _TERRAIN
#define _TERRAIN

#include "Vecteur.h"

class Terrain{
    private :

        int Longeur;
        int Largeur;
        int tab[10][10];
    
    public :
    
        Terrain();

        ~Terrain();

        Vecteur prochaineCase(Vecteur v);

        void generation();
};

    
#endif