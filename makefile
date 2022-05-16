SDL= -I/usr/include/SDL2
LIBS_SDL = -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer

CC = g++ -g
CFLAGS = -Wall -c
EXEC_NAME = Discipuli.out
OBJ_DIR = obj/
BIN_DIR = bin/
OBJ_FILES = obj/mainSdl.o obj/sdlJeu.o obj/Jeu.o obj/Terrain.o obj/Tour.o obj/Ennemi.o obj/Vecteur.o
INSTALL_DIR = /home/draconubs/


all: ${EXEC_NAME}

${EXEC_NAME}: ${OBJ_FILES}
			${CC} ${OBJ_FILES} -o ${BIN_DIR}${EXEC_NAME} $(LIBS_SDL)

${OBJ_DIR}mainSdl.o: src/Sdl/mainSdl.cpp src/core/Jeu.h
			${CC} -o ${OBJ_DIR}mainSdl.o ${CFLAGS} src/Sdl/mainSdl.cpp $(SDL)

${OBJ_DIR}sdlJeu.o: src/Sdl/sdlJeu.h src/Sdl/sdlJeu.cpp
			${CC} -o ${OBJ_DIR}sdlJeu.o ${CFLAGS} src/Sdl/sdlJeu.cpp $(SDL)

${OBJ_DIR}Jeu.o: src/core/Jeu.h src/core/Jeu.cpp src/core/Vecteur.h src/core/Terrain.h src/core/Tour.h src/core/Ennemi.h 
			${CC} -o ${OBJ_DIR}Jeu.o ${CFLAGS} src/core/Jeu.cpp $(SDL)

${OBJ_DIR}Terrain.o: src/core/Terrain.h src/core/Terrain.cpp src/core/Vecteur.h
			${CC} -o ${OBJ_DIR}Terrain.o ${CFLAGS} src/core/Terrain.cpp $(SDL)

${OBJ_DIR}Tour.o: src/core/Tour.h src/core/Tour.cpp src/core/Vecteur.h
			${CC} -o ${OBJ_DIR}Tour.o ${CFLAGS} src/core/Tour.cpp $(SDL)

${OBJ_DIR}Ennemi.o: src/core/Ennemi.h src/core/Ennemi.cpp
			${CC} -o ${OBJ_DIR}Ennemi.o ${CFLAGS} src/core/Ennemi.cpp $(SDL)

${OBJ_DIR}Vecteur.o: src/core/Vecteur.h src/core/Vecteur.cpp
			${CC} -o ${OBJ_DIR}Vecteur.o ${CFLAGS} src/core/Vecteur.cpp $(SDL)

clear:
		rm obj/*.o

veryclear: clear
		rm bin/*.out
