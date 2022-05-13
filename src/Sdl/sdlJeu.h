#ifndef _SDLJEU_H
#define _SDLJEU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include "../core/Jeu.h"

//! \brief Pour g�rer une image avec SDL2
class Image {

private:

    SDL_Surface * m_surface;
    SDL_Texture * m_texture;
    bool m_hasChanged;

public:
    Image () ;
    ~Image();
    void loadFromFile (const char* filename, SDL_Renderer * renderer);
    void loadFromCurrentSurface (SDL_Renderer * renderer);
    void draw (SDL_Renderer * renderer, int x, int y, int w=-1, int h=-1);
    SDL_Texture * getTexture() const;
    void setSurface(SDL_Surface * surf);
};



/**
    La classe gerant le jeu avec un affichage SDL
*/
class SDLSimple {

private :

	Jeu jeu;

    SDL_Window * window;
    SDL_Renderer * renderer;

    TTF_Font * font;
    Image font_im;
    SDL_Color font_color;

    bool withSound;

    Image im_FondMenu;
    Image im_Tour1;
    Image im_Tour2;
    Image im_Tour3;
    Image im_Tour4;
    Image im_Sol;
    Image im_Chemin;
    Image im_Ennemi1;
    Image im_Ennemi2;
    Image im_Ennemi3;
    Image im_Ennemi4;
    Image im_Argent;
    Image im_Diplome;
    Image im_CadrePlein;
    Image im_Cadre;
    Image im_SourisSel;

    bool souris;
    bool touche;
public :

    SDLSimple ();
    ~SDLSimple ();
    void sdlBoucle ();
    void sdlAffJeu ();
    void sdlAffMenu ();

};

#endif
