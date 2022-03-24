#ifndef _TERRAIN
#define _TERRAIN

#include "Vecteur.h"

class Terrain{
    private :

        const int Longeur = 10;
        const int Largeur = 10;
        int tab[][];
    
    public :
    
        Terrain();

        ~Terrain();

        Vecteur prochaineCase(Vecteur v);

        void generation();
};

    
#endif