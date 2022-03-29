all: executable.out

executable.out: Main.o Terrain.o Vecteur.o
			g++ -g Main.o Terrain.o Vecteur.o -o executable.out

Main.o: src/Main.cpp src/Terrain.h src/Vecteur.h
			g++ -g -Wall -c src/Main.cpp

Terrain.o: src/Terrain.h src/Terrain.cpp src/Vecteur.h
			g++ -g -Wall -c src/Terrain.cpp

Vecteur.o: src/Vecteur.h src/Vecteur.cpp
			g++ -g -Wall -c src/Vecteur.cpp

clean:
		rm *.o

veryclean: clean
		rm *.out
