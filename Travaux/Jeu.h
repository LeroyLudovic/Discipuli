#ifndef _JEU
#define _JEU

#include "TableauDynamique.h"
#include "Vecteur.h"
#include "Terrain.h"
#include "Tour.h"
#include "Ennemi.h"


class Jeu{

    private :
        Terrain ter;
        TableauDynamique tabE;
        TableauDynamique tabT;
        int fonds
        int vague
        int nbVagueFort

    public :

    Jeu();

    ~Jeu();

    void ajoutTour(Vecteur,int);

    void Examen();

    Ennemi Attaque(Ennemi,Tour);

    int GainFonds(Ennemi,int);
};

#endif