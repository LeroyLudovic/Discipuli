SDL= -I usr/include/SDL2/SDL.h

all: executable.out

executable.out: mainSdl.o sdlJeu.o txtJeu.o winTxt.o Jeu.o Terrain.o Tour.o Ennemi.o Vecteur.o
			g++ -g mainTxt.o txtJeu.o winTxt.o Jeu.o Terrain.o Tour.o Ennemi.o Vecteur.o -o executable.out

mainSdl.o: src/Sdl/mainSdl.cpp src/core/Jeu.h
			g++ -g -Wall -c src/Sdl/mainSdl.cpp $(SDL)

sdlJeu.o: src/Sdl/sdlJeu.h src/Sdl/sdlJeu.cpp
			g++ -g -Wall -c src/Sdl/SdlJeu.cpp $(SDL)

Jeu.o: src/core/Jeu.h src/core/Jeu.cpp src/core/Vecteur.h src/core/Terrain.h src/core/Tour.h src/core/Ennemi.h 
			g++ -g -Wall -c src/core/Jeu.cpp $(SDL)

Terrain.o: src/core/Terrain.h src/core/Terrain.cpp src/core/Vecteur.h
			g++ -g -Wall -c src/core/Terrain.cpp $(SDL)

Tour.o: src/core/Tour.h src/core/Tour.cpp src/core/Vecteur.h
			g++ -g -Wall -c src/core/Tour.cpp $(SDL)

Ennemi.o: src/core/Ennemi.h src/core/Ennemi.cpp
			g++ -g -Wall -c src/core/Ennemi.cpp $(SDL)

Vecteur.o: src/core/Vecteur.h src/core/Vecteur.cpp
			g++ -g -Wall -c src/core/Vecteur.cpp $(SDL)

clear:
		rm *.o

veryclear: clear
		rm *.out
