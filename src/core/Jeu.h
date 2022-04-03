#ifndef _JEU
#define _JEU

#include "Vecteur.h"
#include "Terrain.h"
#include "Tour.h"
#include "Ennemi.h"

#include <vector>

using namespace std;


class Jeu{

    private :
        int fonds;
        int vague;  
        int nbVagueFort;

    public :

        Terrain ter;
        vector<Ennemi> tabE;
        vector<Tour> tabT;

        Jeu();

        ~Jeu();

        void ajoutTour(Vecteur,int);

        void Examen();

        void Attaque(Ennemi&,Tour);

        int GainFonds(Ennemi);
};

#endif