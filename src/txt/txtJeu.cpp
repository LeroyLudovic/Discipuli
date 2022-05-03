#include <iostream>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // WIN32
#include "winTxt.h"
#include "../core/Vecteur.h"

#include "txtJeu.h"

void txtAff(WinTXT & win, Jeu & jeu) {
	win.clear();
    
// Affichage du terrain
	for(int x=0;x<jeu.ter.getX();++x){
		for(int y=0;y<jeu.ter.getY();++y){
			win.print(y,x,jeu.ter.getCase(x,y));}}

    for(int x=0;x<int(jeu.tabE.size());++x){
        win.print(jeu.tabE[x].getY(),jeu.tabE[x].getX(),'!');
    }

    for(int x=0;x<int(jeu.tabT.size());++x){
        win.print(jeu.tabT[x].getY(),jeu.tabT[x].getX(),'#');
    }

	win.print(jeu.curseur.y,jeu.curseur.x,'+');

	win.draw();
}

void txtBoucle (Jeu & jeu) {
	// Creation d'une nouvelle fenetre en mode texte
	// => fenetre de dimension et position (WIDTH,HEIGHT,STARTX,STARTY)
    WinTXT win (jeu.ter.getY(),jeu.ter.getX());

	bool ok = true;
	bool create = false;
	int c,d;
	jeu.ter.generation();
	int wait = 500;

	do {
	    txtAff(win,jeu);
		

        #ifdef _WIN32
        Sleep(1);
		#else
		usleep(1000);
        #endif // WIN32

		for(int i=0;i<int(jeu.tabE.size());i++){
				if(jeu.tabE[i].position.y == jeu.ter.getY()-1){
					jeu.diplome--;
					jeu.tabE.erase(jeu.tabE.begin() + i);
				}
				if(jeu.tabE[i].vie <= 0){
					jeu.GainFonds(jeu.tabE[i]);
					jeu.tabE.erase(jeu.tabE.begin() + i);
				}
			}
		
		if(jeu.diplome<0){ok=false;}

		if (wait == 0){
			
			

			jeu.actionsAutomatiques();
			

		//DEPLACEMENT 

		//cout<<endl<<endl<<"nombre d'ennemi : "<<jeu.tabE.size(); //debug nb ennemis
			for(int x=0;x<int(jeu.tabE.size());++x){
				Vecteur direction = jeu.ter.prochaineCase(jeu.tabE[x].position);
				jeu.tabE[x].Deplacement(direction);

				//debug pos ennemi
				//cout<<endl<<"Ennemi "<<x+1<<" : "<<jeu.tabE[x].getX()<<" "<<jeu.tabE[x].getY()<<endl;
			}
			wait = 500;
		}
		wait--;
		if (create == false){
			c = win.getCh();
			switch (c) {
				case 'c':
					create = true;
					jeu.curseur.x = 0;
					jeu.curseur.y = 0;
					break;
				case 'r':
					jeu.actionClavier('r');
					break;
				case 'e':
					jeu.actionClavier('e');
					break;
				case 'a':
					jeu.actionClavier('a');
					break;
				case 'w':
					ok = false;
					break;
			}
		}
		if (create == true){
			d = win.getCh();
			
			switch(d){
				case 'z' :
					jeu.curseur.x--;
					break;
				case 'q' :
					jeu.curseur.y--;
					break;
				case 's' :
					jeu.curseur.x++;
					break;
				case 'd' :
					jeu.curseur.y++;
					break;
				case 'c' :
					create = false;
					jeu.ajoutTour(jeu.curseur,0);
					jeu.curseur.x = -1;
					jeu.curseur.y = -1;
					break;
			}
		}
	jeu.Infos();
	} while (ok);

}
