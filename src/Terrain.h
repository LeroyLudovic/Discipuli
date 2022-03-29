#ifndef _TERRAIN
#define _TERRAIN

#include "Vecteur.h"

class Terrain{
    private :

        int Largeur;
        int Longeur;
    
    public :

        int tab[5][20];
    
        Vecteur prochaineCase(Vecteur);

        Terrain();

        ~Terrain();

        void generation();
};

    
#endif