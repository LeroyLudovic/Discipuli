#ifndef _TERRAIN
#define _TERRAIN

#include "Vecteur.h"

class Terrain{
    private :

        int Largeur;
        int Longeur;
    
    public :

        int tab[5][20];
    
        Terrain();

        ~Terrain();

        Vecteur prochaineCase(Vecteur v);

        void generation();
};

    
#endif