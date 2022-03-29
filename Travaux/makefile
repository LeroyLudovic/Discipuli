all: executable.out

executable.out: Main.o Terrain.o Vecteur.o
			g++ -g Main.o Terrain.o Vecteur.o -o executable.out

Main.o: Main.cpp Terrain.h Vecteur.h
			g++ -g -Wall -c Main.cpp

Terrain.o: Terrain.h Terrain.cpp Vecteur.h
			g++ -g -Wall -c Terrain.cpp

Vecteur.o: Vecteur.h Vecteur.cpp
			g++ -g -Wall -c Vecteur.cpp

clean:
		rm *.o

veryclean: clean
		rm *.out
