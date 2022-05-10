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
        int nbVagueFort;
        bool genE;

    public :

        int kill;
        int fonds;
        int vague; 
        int tourSel;
        int diplome;
        int delaiInv;
        Terrain ter;
        vector<Ennemi> tabE;
        vector<Tour> tabT;
        Vecteur curseur;

        Jeu();

        ~Jeu();

        void ajoutTour(Vecteur,int);

        bool DevienFort();

        void creerVague(int);

        void Examen();

        bool Range(Ennemi,Tour);

        void Attaque(Ennemi&,Tour);

        void GainFonds(Ennemi);

        void actionsAutomatiques ();

        void Infos();

        bool actionClavier(const char touche); 

        bool actionSouris(const char souris);
};

#endif