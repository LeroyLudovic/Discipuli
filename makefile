all: executable.out

executable.out: mainTxt.o txtJeu.o winTxt.o Jeu.o Terrain.o Tour.o Ennemi.o Vecteur.o

mainTxt.o: src/txt/mainTxt.cpp src/txt/txtJeu.h src/txt/winTxt.h
			g++ -g -Wall -c src/txt/mainTxt.cpp

txtJeu.o: src/txt/txtJeu.h src/txt/txtJeu.cpp src/txt/winTxt.h
			g++ -g -Wall -c src/txt/txtJeu.cpp

winTxt.o: src/txt/winTxt.h src/txt/winTxt.cpp
			g++ -g -Wall -c src/txt/winTxt.cpp

#executable.out: Main.o Jeu.o Terrain.o Tour.o Ennemi.o Vecteur.o
#			g++ -g Main.o Terrain.o Vecteur.o -o executable.out

Jeu.o: src/core/Jeu.h src/core/Jeu.cpp src/core/Vecteur.h src/core/Terrain.h src/core/Tour.h src/core/Ennemi.h 
			g++ -g -Wall -c src/core/Jeu.cpp

#Main.o: src/core/Main.cpp src/core/Terrain.h src/core/Vecteur.h
#			g++ -g -Wall -c src/core/Main.cpp

Terrain.o: src/core/Terrain.h src/core/Terrain.cpp src/core/Vecteur.h
			g++ -g -Wall -c src/core/Terrain.cpp

Tour.o: src/core/Tour.h src/core/Tour.cpp src/core/Vecteur.h
			g++ -g -Wall -c src/core/Tour.cpp

Ennemi.o: src/core/Ennemi.h src/core/Ennemi.cpp
			g++ -g -Wall -c src/core/Ennemi.cpp

Vecteur.o: src/core/Vecteur.h src/core/Vecteur.cpp
			g++ -g -Wall -c src/core/Vecteur.cpp

clean:
		rm *.o

veryclean: clean
		rm *.out
