#include "Jeu.h"
#include "../txt/winTxt.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // WIN32

#include <string>

Jeu::Jeu(){
    fonds = 50;
    vague = 0;
    nbVagueFort = 0;
    diplome = 5;
    genE = false;
    curseur.x = -1;
    curseur.y = -1;
}

Jeu::~Jeu(){
    
}

void Jeu::ajoutTour(Vecteur a,int b){
    if(fonds>=50){
        Tour t(a,b);
        tabT.push_back(t);
        fonds-=50;
    }
}

void Jeu::creerVague(){
        Vecteur pos(2,-1);
        Ennemi ad(pos,0);
        tabE.push_back(ad);
}

bool Jeu::Range(Ennemi E,Tour T){
    if(E.PosX()  <= T.PosX() + T.portee && E.PosX() >= T.PosX() - T.portee &&
        E.PosY()  <= T.PosY() + T.portee && E.PosY()  >= T.PosY() - T.portee){return true;}
    return false;
}

void Jeu::Attaque(Ennemi &E,Tour T){
    E.vie -= T.degat;
}

void Jeu::GainFonds(Ennemi E){
    switch (E.type) {
        case 0:
            fonds += 15;
            break;
    }
}


void Jeu::actionsAutomatiques (){
    int reste = vague+1-tabE.size();

    if(reste > 0 && genE == true){
        creerVague();
    }

    if(int(tabE.size()) == 0 && genE == false){
        genE = true;
        for(int y=0;y<int(tabE.size());++y){
			tabE[y].lvlUp();
		}
        vague++;
    }
    else if (reste == 0 && genE == true) {
        genE = false;
    }

    for(int x=0;x<int(tabT.size());++x){
		for(int y=0;y<int(tabE.size());++y){
			if(Range(tabE[y],tabT[x])){ Attaque(tabE[y],tabT[x]); y=int(tabE.size()); }	
		}
	}
}

void Jeu::Infos(){
	cout<<endl<<endl<<"vague : "<<vague<<endl;
    cout<<"Diplome : "<<diplome<<" "<<endl;
	cout<<"fonds : "<<fonds<<" "<<endl;
    cout<<"c : creer une tour"<<endl;
    cout<<"w : fermer le programme"<<endl;
}

bool Jeu::actionClavier(const char touche){
    if (touche == 'c') {
        
    }
    return false;
}