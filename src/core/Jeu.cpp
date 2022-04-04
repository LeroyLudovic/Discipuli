#include "Jeu.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // WIN32

#include <string>

Jeu::Jeu(){
    fonds = 50;
    vague = 1;
    nbVagueFort = 0;
}

Jeu::~Jeu(){
    
}

void Jeu::creerTour(){
    bool create = false;

    while(create == false){

    }
}

void Jeu::ajoutTour(Vecteur a,int b){
    Tour t(a,b);
    tabT.push_back(t);
    fonds-=50;
}

void Jeu::creerVague(){
    for(int i=0;i<vague+2;i++){
        Vecteur pos(2,0);
        Ennemi ad(pos,0);
        tabE.push_back(ad);
    }
}

bool Jeu::Range(Ennemi E,Tour T){
    if(E.PosX()  <= T.PosX() + T.portee && E.PosX() >= T.PosX() - T.portee &&
        E.PosY()  <= T.PosY() + T.portee && E.PosY()  >= T.PosY() - T.portee){return true;}
    return false;
}

void Jeu::Attaque(Ennemi &E,Tour T){
    E.vie -= T.degat;
}

int Jeu::GainFonds(Ennemi E){
    int res = 5*(vague + 1);
    return res;
}


void Jeu::actionsAutomatiques (){
    Vecteur direction;
    bool genE = false;
    int reste = vague+2-tabE.size();

    if(int(tabE.size()) == 0 && genE == false){
        genE = true;
    }
    else if (tabE.size() > 0 && reste > 0){
        genE = true; 
    }

    if(int(tabE.size()) == 0){
        creerVague();
    }
    
    for(int x=0;x<int(tabT.size());++x){
		for(int y=0;y<int(tabE.size());++y){
			if(Range(tabE[y],tabT[x])){ Attaque(tabE[y],tabT[x]); }	
		}
	}
}


bool Jeu::actionClavier(const char touche){
    if (touche == 'c') {
        int a,b;
        cout<<endl<<"quelle coordonné X?"<<endl;
        cin>>a;
        cout<<endl<<"quelle coordonné Y?"<<endl;
        cin>>b;
        
        Vecteur v(a,b);

        ajoutTour(v,0);
    }
    return false;
}