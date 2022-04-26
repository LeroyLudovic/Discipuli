SDL= -I usr/include/SDL2

LIBS_SDL = -Lextern \
			-Lextern/SDL2_mingw-cb20/SDL2-2.0.12/x86_64-w64-mingw32/lib \
			-Lextern/SDL2_mingw-cb20/SDL2_ttf-2.0.15/x86_64-w64-mingw32/lib \
			-Lextern/SDL2_mingw-cb20/SDL2_image-2.0.5/x86_64-w64-mingw32/lib \
			-Lextern/SDL2_mingw-cb20/SDL2_mixer-2.0.4/x86_64-w64-mingw32/lib \
			-lmingw32 -lSDL2main -lSDL2.dll -lSDL2_ttf.dll -lSDL2_image.dll -lSDL2_mixer.dll

all: executable.out

executable.out: mainSdl.o sdlJeu.o Jeu.o Terrain.o Tour.o Ennemi.o Vecteur.o
			g++ -g mainSdl.o sdlJeu.o Jeu.o Terrain.o Tour.o Ennemi.o Vecteur.o -o executable.out $(LIBS_SDL)

mainSdl.o: src/Sdl/mainSdl.cpp src/core/Jeu.h
			g++ -g -Wall -c src/Sdl/mainSdl.cpp $(SDL)

sdlJeu.o: src/Sdl/sdlJeu.h src/Sdl/sdlJeu.cpp
			g++ -g -Wall -c src/Sdl/sdlJeu.cpp $(SDL)

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
