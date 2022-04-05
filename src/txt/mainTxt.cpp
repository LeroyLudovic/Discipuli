#include <iostream>

#include "winTxt.h"
#include "txtJeu.h"

using namespace std;

int main ( int argc, char** argv ) {
	char start;
	
	do{
		cout << "enter 't' : play in txt"<<endl;
		cout << "enter 'w' : exit"<<endl;
		cin>>start;

		if(start == 't'){
			termClear();
			Jeu jeu;
			txtBoucle(jeu);
    		termClear();
		}
	}while(start == 't');
	
	return 0;
}