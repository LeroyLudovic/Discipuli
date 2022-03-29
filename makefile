all: executable.out

executable.out: Main.o Terrain.o Tour.o  Vecteur.o TableauDynamique.o Element.o
			g++ -g Main.o Terrain.o Vecteur.o -o executable.out

Main.o: src/Main.cpp src/Terrain.h src/Vecteur.h
			g++ -g -Wall -c src/Main.cpp

Terrain.o: src/Terrain.h src/Terrain.cpp src/Vecteur.h
			g++ -g -Wall -c src/Terrain.cpp

Tour.o: src/Tour.h src/Tour.cpp
			g++ -g -Wall -c src/Tour.cpp

Vecteur.o: src/Vecteur.h src/Vecteur.cpp
			g++ -g -Wall -c src/Vecteur.cpp

TableauDynamique.o: src/TableauDynamique.h src/TableauDynamique.cpp src/Element.h
			g++ -g -Wall -c src/TableauDynamique.cpp

Element.o: src/Element.h src/Element.cpp
			g++ -g -Wall -c src/Element.cpp


clean:
		rm *.o

veryclean: clean
		rm *.out
