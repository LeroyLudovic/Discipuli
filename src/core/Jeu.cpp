#include "Jeu.h"
#include "../txt/winTxt.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // WIN32

#include <string>

Jeu::Jeu(){
    tourSel = 1;
    fonds = 800;
    vague = 0;
    nbVagueFort = 0;
    diplome = 5;
    kill = 0;
    delaiInv = 0;
    genE = false;
    curseur.x = -1;
    curseur.y = -1;
}

Jeu::~Jeu(){
    
}

void Jeu::ajoutTour(Vecteur a,int b){
    if (ter.getCase(a.x,a.y) == 'O') {
        switch (tourSel){
            case 1 :
                if(fonds>=50){
                Tour t(a,b);
                tabT.push_back(t);
                fonds-=50;
                ter.tab[a.x][a.y] = '#';}
                break;
            case 2 :
                if(fonds>=65){
                Tour t(a,b);
                tabT.push_back(t);
                fonds-=65;
                ter.tab[a.x][a.y] = '#';}
                break;
            case 3 :
                if(fonds>=55){
                Tour t(a,b);
                tabT.push_back(t);
                fonds-=55;
                ter.tab[a.x][a.y] = '#';}
                break;
            case 4 :
                if(fonds>=75){
                Tour t(a,b);
                tabT.push_back(t);
                fonds-=75;
                ter.tab[a.x][a.y] = '#';}
                break;
        }
    }
    else if (ter.getCase(a.x,a.y) == '#'){
        
    }
}

bool Jeu::DevienFort(){
    bool fort;
    int test = rand() % 100 + 1;
    if (test <= 1) {
        fort = true;
    }
    else {
        fort = false;
    }
    return fort;
}

void Jeu::creerVague(int a){
    Vecteur pos(ter.depart,-1);
    Ennemi ad(pos,a,DevienFort());
    ad.lvlUp(vague);
    tabE.push_back(ad);
    switch(a){
        case 1 :
            delaiInv = 40;
            break;
        case 2 :
            delaiInv = 10;
            break;
        case 3 :
            delaiInv = 30;
            break;
        case 4 :
            delaiInv = 8;
            break;
    }
}

bool Jeu::Range(Ennemi E,Tour T){
    if(E.getX()  <= T.getX() + T.portee && E.getX() >= T.getX() - T.portee &&
        E.getY()  <= T.getY() + T.portee && E.getY()  >= T.getY() - T.portee){return true;}
    return false;
}

void Jeu::Attaque(Ennemi &E,Tour T){
    E.vie -= T.degat;
}

void Jeu::GainFonds(Ennemi E){
    switch (E.type) {
        case 1:
            fonds += 15;
            break;
        case 2:
            fonds += 15;
            break;
        case 3:
            fonds += 15;
            break;
        case 4:
            fonds += 15;
            break;

    }
}


void Jeu::actionsAutomatiques (){
    int reste = vague+1-(kill+tabE.size());


    if(reste > 0 && genE == true && delaiInv <= 0){
        creerVague(rand() % 4 +1);
    }
    if(reste > 0 && genE == true && delaiInv > 0){
        delaiInv--;
    }

    if(tabE.size() == 0 && genE == false){
        genE = true;
        kill = 0;
        vague++;
    }
    else if (reste == 0 && genE == true) {
        genE = false;
    }	

    for(int x=0;x<int(tabT.size());++x){
        if(tabT[x].Charg()){
            for(int y=0;y<int(tabE.size());++y){
                if(Range(tabE[y],tabT[x])){ Attaque(tabE[y],tabT[x]); if(tabT[x].type != 3){y=int(tabE.size());}}	
            }
        }
	}
    std::cout<<vague<<std::endl;
}

void Jeu::Infos(){
	cout<<endl<<endl<<"vague : "<<vague<<endl;
    cout<<"Diplome : "<<diplome<<" "<<endl;
	cout<<"fonds : "<<fonds<<" "<<endl;
    cout<<"c : creer une tour"<<endl;
    cout<<"w : fermer le programme"<<endl;
}

bool Jeu::actionClavier(const char touche){
    switch(touche) {
		case 'a' :
				tourSel=1;
				break;
		case 'z' :
				tourSel=2;
				break;
		case 'e' :
				tourSel=3;
				break;
		case 'r' :
				tourSel=4;
				break;
	}
    return false;
}

bool Jeu::actionSouris(const char souris){
    switch(souris) {
        case 'g' :
            break;
    }
    return false;
}