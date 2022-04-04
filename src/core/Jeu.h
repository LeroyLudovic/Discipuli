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

        void creerTour();

        void ajoutTour(Vecteur,int);

        void creerVague();

        void Examen();

        bool Range(Ennemi,Tour);
        
        void Attaque(Ennemi&,Tour);

        int GainFonds(Ennemi);

        void actionsAutomatiques ();
        bool actionClavier(const char touche); 
};

#endif