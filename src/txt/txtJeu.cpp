#include <iostream>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // WIN32

#include "winTxt.h"

#include "txtJeu.h"

void txtAff(WinTXT & win, Jeu & jeu) {
	win.clear();
    
// Affichage des murs et des pastilles
	for(int x=0;x<jeu.ter.getX();++x){
		for(int y=0;y<jeu.ter.getY();++y){
			win.print(y,x,jeu.ter.getCase(x,y));}}

    for(int x=0;x<int(jeu.tabE.size());++x){
        win.print(jeu.tabE[x].PosY(),jeu.tabE[x].PosX(),'E');
    }
/*
    for(int x=0;x<int(jeu.tabT.size());++x){
        win.print(jeu.tabT[x].PosX(),jeu.tabT[x].PosY(),'T');
    }
	*/

	win.draw();
}

void txtBoucle (Jeu & jeu) {
	// Creation d'une nouvelle fenetre en mode texte
	// => fenetre de dimension et position (WIDTH,HEIGHT,STARTX,STARTY)
    WinTXT win (jeu.ter.getY(),jeu.ter.getX());

	bool ok = true;
	int c;
	jeu.ter.generation();

	do {
	    txtAff(win,jeu);

        #ifdef _WIN32
        Sleep(100);
		#else
		usleep(100000);
        #endif // WIN32

		jeu.actionsAutomatiques();

		//DEPLACEMENT

		cout<<endl<<endl<<"nombre d'ennemi : "<<jeu.tabE.size(); //debug nb ennemis

        for(int x=0;x<int(jeu.tabE.size());++x){
            Vecteur direction = jeu.ter.prochaineCase(jeu.tabE[x].position);


			#ifdef _WIN32
        		Sleep(500);
			#else
				usleep(500000);
        	#endif // WIN32

            jeu.tabE[x].Deplacement(direction);

			//debug pos ennemi
			cout<<endl;
			cout<<"Ennemi "<<x+1<<" : "<<jeu.tabE[x].PosX()<<" "<<jeu.tabE[x].PosY()<<endl;
			cout<<"direction : "<<direction<<" "<<jeu.tabE[x].position;
        }


		c = win.getCh();
		switch (c) {
			case 'k':
				jeu.actionClavier('g');
				break;
			case 'm':
				jeu.actionClavier('d');
				break;
			case 'l':
				jeu.actionClavier('h');
				break;
			case 'o':
				jeu.actionClavier('b');
				break;
			case 'q':
				ok = false;
				break;
		}

	} while (ok);

}
