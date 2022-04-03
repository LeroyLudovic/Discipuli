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
        Terrain ter;
        vector<Ennemi> tabE;
        vector<Tour> tabT;
        int fonds;
        int vague;  
        int nbVagueFort;

    public :

    Jeu();

    ~Jeu();

    void ajoutTour(Vecteur,int);

    void Examen();

    void Attaque(Ennemi&,Tour);

    int GainFonds(Ennemi);
};

#endif