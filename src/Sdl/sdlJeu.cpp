#include <cassert>
#include <time.h>
#include "sdlJeu.h"
#include <stdlib.h>
#include <string.h>
#include <sstream>
 

#include "../core/Jeu.h"

#include <iostream>
using namespace std;

const int TAILLE_SPRITE = 48;

float temps () {
    return float(SDL_GetTicks()) / CLOCKS_PER_SEC;  // conversion des ms en secondes en divisant par 1000
}

// ============= CLASS IMAGE =============== //

Image::Image () : m_surface(nullptr), m_texture(nullptr), m_hasChanged(false) {
}

Image::~Image()
{
    SDL_FreeSurface(m_surface);
    SDL_DestroyTexture(m_texture);

    m_surface = nullptr;
    m_texture = nullptr;
    m_hasChanged = false;
}

void Image::loadFromFile (const char* filename, SDL_Renderer * renderer) {
    m_surface = IMG_Load(filename);
    if (m_surface == nullptr) {
        string nfn = string("../") + filename;
        cout << "Error: cannot load "<< filename <<". Trying "<<nfn<<endl;
        m_surface = IMG_Load(nfn.c_str());
        if (m_surface == nullptr) {
            nfn = string("../") + nfn;
            m_surface = IMG_Load(nfn.c_str());
        }
    }
    if (m_surface == nullptr) {
        cout<<"Error: cannot load "<< filename <<endl;
        SDL_Quit();
        exit(1);
    }

    SDL_Surface * surfaceCorrectPixelFormat = SDL_ConvertSurfaceFormat(m_surface,SDL_PIXELFORMAT_ARGB8888,0);
    SDL_FreeSurface(m_surface);
    m_surface = surfaceCorrectPixelFormat;

    m_texture = SDL_CreateTextureFromSurface(renderer,surfaceCorrectPixelFormat);
    if (m_texture == NULL) {
        cout << "Error: problem to create the texture of "<< filename<< endl;
        SDL_Quit();
        exit(1);
    }
}

void Image::loadFromCurrentSurface (SDL_Renderer * renderer) {
    m_texture = SDL_CreateTextureFromSurface(renderer,m_surface);
    if (m_texture == nullptr) {
        cout << "Error: problem to create the texture from surface " << endl;
        SDL_Quit();
        exit(1);
    }
}

void Image::draw (SDL_Renderer * renderer, int x, int y, int w, int h) {
    int ok;
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = (w<0)?m_surface->w:w;
    r.h = (h<0)?m_surface->h:h;

    if (m_hasChanged) {
        ok = SDL_UpdateTexture(m_texture,nullptr,m_surface->pixels,m_surface->pitch);
        assert(ok == 0);
        m_hasChanged = false;
    }

    ok = SDL_RenderCopy(renderer,m_texture,nullptr,&r);
    assert(ok == 0);
}

SDL_Texture * Image::getTexture() const {return m_texture;}

void Image::setSurface(SDL_Surface * surf) {m_surface = surf;}










// ============= CLASS SDLJEU =============== //

SDLSimple::SDLSimple () : jeu() {
    // Initialisation de la SDL

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    if (TTF_Init() != 0) {
        cout << "Erreur lors de l'initialisation de la SDL_ttf : " << TTF_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if( !(IMG_Init(imgFlags) & imgFlags)) {
        cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
        cout << "No sound !!!" << endl;
        //SDL_Quit();exit(1);
        withSound = false;
    }
    else withSound = true;

	int dimx, dimy;
	dimx = jeu.ter.getX();
	dimy = jeu.ter.getY();
	dimx = dimx * TAILLE_SPRITE;
	dimy = dimy * TAILLE_SPRITE;

    // Creation de la fenetre
    window = SDL_CreateWindow("Discipuli", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, dimy, dimx*2, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == nullptr) {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl; 
        SDL_Quit(); 
        exit(1);
    }
	SDL_Surface* icon;
    icon = SDL_LoadBMP("Data/icon.bmp");

    if (icon)
	{
		SDL_SetColorKey(icon, true, SDL_MapRGB(icon->format, 0, 0, 0));
		SDL_SetWindowIcon(window, icon);
		SDL_FreeSurface(icon);
	}

    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    // IMAGES
    im_FondMenu.loadFromFile("Data/Menu.png",renderer);

    im_Sol.loadFromFile("Data/Sol.png",renderer);
    im_Chemin.loadFromFile("Data/Chemin.png",renderer);

    im_Tour1.loadFromFile("Data/Math.png",renderer);
    im_Tour2.loadFromFile("Data/Sport.png",renderer);
    im_Tour3.loadFromFile("Data/Musique.png",renderer);
    im_Tour4.loadFromFile("Data/Histoire.png",renderer);

    im_Ennemi1.loadFromFile("Data/Intello.png",renderer);
    im_Ennemi2.loadFromFile("Data/Steve.png",renderer);
    im_Ennemi3.loadFromFile("Data/Normi.png",renderer);
    im_Ennemi4.loadFromFile("Data/Ines.png",renderer);


    im_Argent.loadFromFile("Data/Argent.png",renderer);
    im_Diplome.loadFromFile("Data/Diplome.png",renderer);

    im_CadrePlein.loadFromFile("Data/CadrePlein.png",renderer);
    im_Cadre.loadFromFile("Data/Cadre.png",renderer);
    im_SourisSel.loadFromFile("Data/Cadre.png",renderer);

    // FONTS
    font = TTF_OpenFont("Data/alagard.ttf",70);
    if (font == nullptr)
        font = TTF_OpenFont("../Data/alagard.ttf",70);
    if (font == nullptr) {
            cout << "Failed to load alagard.ttf! SDL_TTF Error: " << TTF_GetError() << endl; 
            SDL_Quit(); 
            exit(1);
	}
	

    // SONS
    
    if (withSound)
    {
        /*sound = Mix_LoadWAV("data/son.wav");
        if (sound == nullptr) 
            sound = Mix_LoadWAV("../data/son.wav");
        if (sound == nullptr) {
                cout << "Failed to load son.wav! SDL_mixer Error: " << Mix_GetError() << endl; 
                SDL_Quit();
                exit(1);
        }*/
    }
}

SDLSimple::~SDLSimple () {
    if (withSound) Mix_Quit();
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void SDLSimple::sdlAffMenu () {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_Surface* TextSurface;

    im_FondMenu.draw(renderer,0,0,1920,1080);
    im_CadrePlein.draw(renderer,1872/2-(TAILLE_SPRITE*9.6)/2,420,TAILLE_SPRITE*9.6,TAILLE_SPRITE*2.4);
    im_CadrePlein.draw(renderer,1872/2-(TAILLE_SPRITE*9.6)/2,280,TAILLE_SPRITE*9.6,TAILLE_SPRITE*2.4);

    font_color.r = 255;font_color.g = 255;font_color.b = 255;
    font = TTF_OpenFont("Data/alagard.ttf",150);

    TextSurface = TTF_RenderText_Solid(font,"Discipuli",font_color);
	font_im.setSurface(TTF_RenderText_Solid(font,"Discipuli",font_color));
    font_im.loadFromCurrentSurface(renderer);
    SDL_Rect Titre;
    Titre.x = 1872/2-300;Titre.y = 100;Titre.w = TextSurface->w;Titre.h = TextSurface->h; 
    SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&Titre);
    SDL_FreeSurface(TextSurface);
    
    font_color.r = 0;font_color.g = 0;font_color.b = 0;

    TextSurface = TTF_RenderText_Solid(font,"Discipuli",font_color);
	font_im.setSurface(TTF_RenderText_Solid(font,"Discipuli",font_color));
    font_im.loadFromCurrentSurface(renderer);
    SDL_Rect Titre2;
    Titre2.x = 1872/2-290;Titre2.y = 90;Titre2.w = TextSurface->w;Titre2.h = TextSurface->h; 
    SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&Titre2);
    SDL_FreeSurface(TextSurface);

    font_color.r = 0;font_color.g = 0;font_color.b = 0;
    font = TTF_OpenFont("Data/alagard.ttf",100);

    TextSurface = TTF_RenderText_Solid(font,"Play",font_color);
	font_im.setSurface(TTF_RenderText_Solid(font,"Play",font_color));
    font_im.loadFromCurrentSurface(renderer);
    SDL_Rect PlayButton;
    PlayButton.x = 1872/2-100;PlayButton.y = 290;PlayButton.w = TextSurface->w;PlayButton.h = TextSurface->h; 
    SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&PlayButton);
    SDL_FreeSurface(TextSurface);

    TextSurface = TTF_RenderText_Solid(font,"Quit",font_color);
	font_im.setSurface(TTF_RenderText_Solid(font,"Quit",font_color));
    font_im.loadFromCurrentSurface(renderer);
    SDL_Rect QuitButton;
    QuitButton.x = 1872/2-100;QuitButton.y = 435;QuitButton.w = TextSurface->w;QuitButton.h = TextSurface->h; 
    SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&QuitButton);
    SDL_FreeSurface(TextSurface);
}

void SDLSimple::sdlAffJeu () {
	//Remplir l'écran de blanc
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

	int x,y;
    int decalage = 80;
	Terrain& ter = jeu.ter;

    ostringstream d,m,v,vag,dmgT,vitT,rangeT,upgradeT;
    SDL_Surface* TextSurface;
    font = TTF_OpenFont("Data/alagard.ttf",25);

    // Afficher les sprites du sol et du chemin
	for (x=0;x<ter.getX();++x)
		for (y=0;y<ter.getY();++y)
			if (ter.getCase(x,y)=='O' || ter.getCase(x,y)=='#')
				im_Sol.draw(renderer,y*TAILLE_SPRITE,x*TAILLE_SPRITE+decalage,TAILLE_SPRITE,TAILLE_SPRITE);
			else if (ter.getCase(x,y)==' ')
				im_Chemin.draw(renderer,y*TAILLE_SPRITE,x*TAILLE_SPRITE+decalage,TAILLE_SPRITE,TAILLE_SPRITE);

	// Afficher le sprite de tours
    for (int i = 0 ; i < int(jeu.tabT.size()) ; i++) { 
        if (jeu.tabT[i].type == 1) im_Tour1.draw(renderer,jeu.tabT[i].getY()*TAILLE_SPRITE,jeu.tabT[i].getX()*TAILLE_SPRITE+decalage,TAILLE_SPRITE,TAILLE_SPRITE);
        if (jeu.tabT[i].type == 2) im_Tour2.draw(renderer,jeu.tabT[i].getY()*TAILLE_SPRITE,jeu.tabT[i].getX()*TAILLE_SPRITE+decalage,TAILLE_SPRITE,TAILLE_SPRITE);
        if (jeu.tabT[i].type == 3) im_Tour3.draw(renderer,jeu.tabT[i].getY()*TAILLE_SPRITE,jeu.tabT[i].getX()*TAILLE_SPRITE+decalage,TAILLE_SPRITE,TAILLE_SPRITE);
        if (jeu.tabT[i].type == 4) im_Tour4.draw(renderer,jeu.tabT[i].getY()*TAILLE_SPRITE,jeu.tabT[i].getX()*TAILLE_SPRITE+decalage,TAILLE_SPRITE,TAILLE_SPRITE);
    }

	// Afficher le sprite du Fantome
    for (int i = 0 ; i < int(jeu.tabE.size()) ; i++) {
        float mov = (5*jeu.tabE[i].vitesse*(jeu.tabE[i].chargement/jeu.tabE[i].vitesse))/100*TAILLE_SPRITE;
        if (ter.prochaineCase(jeu.tabE[i].position).y == 1) {
            if (jeu.tabE[i].type == 1) im_Ennemi1.draw(renderer,jeu.tabE[i].getY()*TAILLE_SPRITE+mov,jeu.tabE[i].getX()*TAILLE_SPRITE+decalage,TAILLE_SPRITE,TAILLE_SPRITE);
            if (jeu.tabE[i].type == 2) im_Ennemi2.draw(renderer,jeu.tabE[i].getY()*TAILLE_SPRITE+mov,jeu.tabE[i].getX()*TAILLE_SPRITE+decalage,TAILLE_SPRITE,TAILLE_SPRITE);
            if (jeu.tabE[i].type == 3) im_Ennemi3.draw(renderer,jeu.tabE[i].getY()*TAILLE_SPRITE+mov,jeu.tabE[i].getX()*TAILLE_SPRITE+decalage,TAILLE_SPRITE,TAILLE_SPRITE);
            if (jeu.tabE[i].type == 4) im_Ennemi4.draw(renderer,jeu.tabE[i].getY()*TAILLE_SPRITE+mov,jeu.tabE[i].getX()*TAILLE_SPRITE+decalage,TAILLE_SPRITE,TAILLE_SPRITE);

            v << jeu.tabE[i].vie;
            TextSurface = TTF_RenderText_Solid(font,v.str().c_str(),font_color);
            font_im.setSurface(TTF_RenderText_Solid(font,v.str().c_str(),font_color));
            font_im.loadFromCurrentSurface(renderer);
            SDL_Rect eVie;
            eVie.x = jeu.tabE[i].getY()*TAILLE_SPRITE+mov;eVie.y = jeu.tabE[i].getX()*TAILLE_SPRITE+decalage;eVie.w = TextSurface->w;eVie.h = TextSurface->h; 
            SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&eVie);
            SDL_FreeSurface(TextSurface);
            v.str("");
            v.clear();
        }
        else if (ter.prochaineCase(jeu.tabE[i].position).x == -1) {
            if (jeu.tabE[i].type == 1) im_Ennemi1.draw(renderer,jeu.tabE[i].getY()*TAILLE_SPRITE,jeu.tabE[i].getX()*TAILLE_SPRITE+decalage-mov,TAILLE_SPRITE,TAILLE_SPRITE);
            if (jeu.tabE[i].type == 2) im_Ennemi2.draw(renderer,jeu.tabE[i].getY()*TAILLE_SPRITE,jeu.tabE[i].getX()*TAILLE_SPRITE+decalage-mov,TAILLE_SPRITE,TAILLE_SPRITE);
            if (jeu.tabE[i].type == 3) im_Ennemi3.draw(renderer,jeu.tabE[i].getY()*TAILLE_SPRITE,jeu.tabE[i].getX()*TAILLE_SPRITE+decalage-mov,TAILLE_SPRITE,TAILLE_SPRITE);
            if (jeu.tabE[i].type == 4) im_Ennemi4.draw(renderer,jeu.tabE[i].getY()*TAILLE_SPRITE,jeu.tabE[i].getX()*TAILLE_SPRITE+decalage-mov,TAILLE_SPRITE,TAILLE_SPRITE);
            
            v << jeu.tabE[i].vie;
            TextSurface = TTF_RenderText_Solid(font,v.str().c_str(),font_color);
            font_im.setSurface(TTF_RenderText_Solid(font,v.str().c_str(),font_color));
            font_im.loadFromCurrentSurface(renderer);
            SDL_Rect eVie;
            eVie.x = jeu.tabE[i].getY()*TAILLE_SPRITE;eVie.y = jeu.tabE[i].getX()*TAILLE_SPRITE+decalage-mov;eVie.w = TextSurface->w;eVie.h = TextSurface->h; 
            SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&eVie);
            SDL_FreeSurface(TextSurface);
            v.str("");
            v.clear();
        }
        else if (ter.prochaineCase(jeu.tabE[i].position).x == 1) {
            if (jeu.tabE[i].type == 1) im_Ennemi1.draw(renderer,jeu.tabE[i].getY()*TAILLE_SPRITE,jeu.tabE[i].getX()*TAILLE_SPRITE+decalage+mov,TAILLE_SPRITE,TAILLE_SPRITE);
            if (jeu.tabE[i].type == 2) im_Ennemi2.draw(renderer,jeu.tabE[i].getY()*TAILLE_SPRITE,jeu.tabE[i].getX()*TAILLE_SPRITE+decalage+mov,TAILLE_SPRITE,TAILLE_SPRITE);
            if (jeu.tabE[i].type == 3) im_Ennemi3.draw(renderer,jeu.tabE[i].getY()*TAILLE_SPRITE,jeu.tabE[i].getX()*TAILLE_SPRITE+decalage+mov,TAILLE_SPRITE,TAILLE_SPRITE);
            if (jeu.tabE[i].type == 4) im_Ennemi4.draw(renderer,jeu.tabE[i].getY()*TAILLE_SPRITE,jeu.tabE[i].getX()*TAILLE_SPRITE+decalage+mov,TAILLE_SPRITE,TAILLE_SPRITE);            

            v << jeu.tabE[i].vie;
            TextSurface = TTF_RenderText_Solid(font,v.str().c_str(),font_color);
            font_im.setSurface(TTF_RenderText_Solid(font,v.str().c_str(),font_color));
            font_im.loadFromCurrentSurface(renderer);
            SDL_Rect eVie;
            eVie.x = jeu.tabE[i].getY()*TAILLE_SPRITE;eVie.y = jeu.tabE[i].getX()*TAILLE_SPRITE+decalage+mov;eVie.w = TextSurface->w;eVie.h = TextSurface->h; 
            SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&eVie);
            SDL_FreeSurface(TextSurface);
            v.str("");
            v.clear();
        }
    }

    im_Argent.draw(renderer,50,520+decalage,TAILLE_SPRITE*4,TAILLE_SPRITE*1.5);
    im_Diplome.draw(renderer,50,670+decalage,TAILLE_SPRITE*4,TAILLE_SPRITE*1.5);

    im_Tour1.draw(renderer,500,525+decalage,TAILLE_SPRITE,TAILLE_SPRITE);
    im_Tour2.draw(renderer,575,525+decalage,TAILLE_SPRITE,TAILLE_SPRITE);
    im_Tour3.draw(renderer,650,525+decalage,TAILLE_SPRITE,TAILLE_SPRITE);
    im_Tour4.draw(renderer,725,525+decalage,TAILLE_SPRITE,TAILLE_SPRITE);

    // Ecrire le nombre de vie
    font_color.r = 255;font_color.g = 0;font_color.b = 0;font_color.a = 255;
    font = TTF_OpenFont("Data/alagard.ttf",70);
    d << jeu.diplome;
    TextSurface = TTF_RenderText_Solid(font,d.str().c_str(),font_color);
	font_im.setSurface(TTF_RenderText_Solid(font,d.str().c_str(),font_color));
	font_im.loadFromCurrentSurface(renderer);
    SDL_Rect NbDiplome;
    NbDiplome.x = 160;NbDiplome.y = 757;NbDiplome.w = TextSurface->w;NbDiplome.h = TextSurface->h;
    SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&NbDiplome);
    SDL_FreeSurface(TextSurface);
    d.str("");
    d.clear();

    // Ecrire la quantité d'argent
    m << jeu.fonds;
    TextSurface = TTF_RenderText_Solid(font,m.str().c_str(),font_color);
	font_im.setSurface(TTF_RenderText_Solid(font,m.str().c_str(),font_color));
    font_im.loadFromCurrentSurface(renderer);
    SDL_Rect NbArgent;
    NbArgent.x = 95;NbArgent.y = 607;NbArgent.w = TextSurface->w;NbArgent.h = TextSurface->h; 
    SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&NbArgent);
    SDL_FreeSurface(TextSurface);
    m.str("");
    m.clear();

    // Ecrire le titre
    TextSurface = TTF_RenderText_Solid(font,"Discipuli",font_color);
	font_im.setSurface(TTF_RenderText_Solid(font,"Discipuli",font_color));
    font_im.loadFromCurrentSurface(renderer);
    SDL_Rect Titre;
    Titre.x = 1872/2-160;Titre.y = 9;Titre.w = TextSurface->w;Titre.h = TextSurface->h;
    SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&Titre);
    SDL_FreeSurface(TextSurface);

    font = TTF_OpenFont("Data/alagard.ttf",25);
    TextSurface = TTF_RenderText_Solid(font,"Vague :",font_color);
	font_im.setSurface(TTF_RenderText_Solid(font,"Vague :",font_color));
    font_im.loadFromCurrentSurface(renderer);
    SDL_Rect Vague;
    Vague.x = 20;Vague.y = 50;Vague.w = TextSurface->w;Vague.h = TextSurface->h;
    SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&Vague);
    SDL_FreeSurface(TextSurface);

    vag << jeu.vague;
    TextSurface = TTF_RenderText_Solid(font,vag.str().c_str(),font_color);
	font_im.setSurface(TTF_RenderText_Solid(font,vag.str().c_str(),font_color));
    font_im.loadFromCurrentSurface(renderer);
    SDL_Rect vagF;
    vagF.x = 120;vagF.y = 50;vagF.w = TextSurface->w;vagF.h = TextSurface->h; 
    SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&vagF);
    SDL_FreeSurface(TextSurface);
    vag.str("");
    vag.clear();
    
    TextSurface = TTF_RenderText_Solid(font,"A        Z       E        R",font_color);
	font_im.setSurface(TTF_RenderText_Solid(font,"A        Z       E        R",font_color));
    font_im.loadFromCurrentSurface(renderer);
    SDL_Rect Touches;
    Touches.x = 515;Touches.y = 570;Touches.w = TextSurface->w;Touches.h = TextSurface->h;
    SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&Touches);
    SDL_FreeSurface(TextSurface);

    TextSurface = TTF_RenderText_Solid(font,"Prix :",font_color);
    font_im.setSurface(TTF_RenderText_Solid(font,"Prix :",font_color));
    font_im.loadFromCurrentSurface(renderer);
    SDL_Rect Prix;
    Prix.x = 415;Prix.y = 670;Prix.w = TextSurface->w;Prix.h = TextSurface->h;
    SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&Prix);
    SDL_FreeSurface(TextSurface);

    TextSurface = TTF_RenderText_Solid(font,"50",font_color);
    font_im.setSurface(TTF_RenderText_Solid(font,"50",font_color));
    font_im.loadFromCurrentSurface(renderer);
    SDL_Rect P1;
    P1.x = 510;P1.y = 670;P1.w = TextSurface->w;P1.h = TextSurface->h;
    SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&P1);
    SDL_FreeSurface(TextSurface);

    TextSurface = TTF_RenderText_Solid(font,"65",font_color);
    font_im.setSurface(TTF_RenderText_Solid(font,"65",font_color));
    font_im.loadFromCurrentSurface(renderer);
    SDL_Rect P2;
    P2.x = 585;P2.y = 670;P2.w = TextSurface->w;P2.h = TextSurface->h;
    SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&P2);
    SDL_FreeSurface(TextSurface);

    TextSurface = TTF_RenderText_Solid(font,"55",font_color);
    font_im.setSurface(TTF_RenderText_Solid(font,"55",font_color));
    font_im.loadFromCurrentSurface(renderer);
    SDL_Rect P3;
    P3.x = 660;P3.y = 670;P3.w = TextSurface->w;P3.h = TextSurface->h;
    SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&P3);
    SDL_FreeSurface(TextSurface);

    TextSurface = TTF_RenderText_Solid(font,"75",font_color);
    font_im.setSurface(TTF_RenderText_Solid(font,"75",font_color));
    font_im.loadFromCurrentSurface(renderer);
    SDL_Rect P4;
    P4.x = 735;P4.y = 670;P4.w = TextSurface->w;P4.h = TextSurface->h;
    SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&P4);
    SDL_FreeSurface(TextSurface);

    font = TTF_OpenFont("Data/alagard.ttf",70);

    switch(jeu.tourSel){
        case 1 :
            im_Cadre.draw(renderer,495,520+decalage,TAILLE_SPRITE*1.2,TAILLE_SPRITE*1.2);
            break;
        case 2 :
            im_Cadre.draw(renderer,570,520+decalage,TAILLE_SPRITE*1.2,TAILLE_SPRITE*1.2);
            break;
        case 3 :
            im_Cadre.draw(renderer,645,520+decalage,TAILLE_SPRITE*1.2,TAILLE_SPRITE*1.2);
            break;
        case 4 :
            im_Cadre.draw(renderer,720,520+decalage,TAILLE_SPRITE*1.2,TAILLE_SPRITE*1.2);
            break;
    }

    if (jeu.tourMenu){

        for (int i = 0 ; i < int(jeu.tabT.size()) ; i++) {
            if(jeu.tabT[i].getX() == jeu.posClick.x && jeu.tabT[i].getY() == jeu.posClick.y && jeu.tabT[i].type == 1){
                im_Tour1.draw(renderer,1200,650,TAILLE_SPRITE*2.5,TAILLE_SPRITE*2.5);
                
                font = TTF_OpenFont("Data/alagard.ttf",30);

                dmgT << jeu.tabT[i].degat;
                TextSurface = TTF_RenderText_Solid(font,dmgT.str().c_str(),font_color);
                font_im.setSurface(TTF_RenderText_Solid(font,dmgT.str().c_str(),font_color));
                font_im.loadFromCurrentSurface(renderer);
                SDL_Rect NbDmg;
                NbDmg.x = 1435;NbDmg.y = 680;NbDmg.w = TextSurface->w;NbDmg.h = TextSurface->h; 
                SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&NbDmg);
                SDL_FreeSurface(TextSurface);
                dmgT.str("");
                dmgT.clear();

                vitT << jeu.tabT[i].vitesse;
                TextSurface = TTF_RenderText_Solid(font,vitT.str().c_str(),font_color);
                font_im.setSurface(TTF_RenderText_Solid(font,vitT.str().c_str(),font_color));
                font_im.loadFromCurrentSurface(renderer);
                SDL_Rect NbVit;
                NbVit.x = 1435;NbVit.y = 780;NbVit.w = TextSurface->w;NbVit.h = TextSurface->h; 
                SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&NbVit);
                SDL_FreeSurface(TextSurface);
                vitT.str("");
                vitT.clear();

                rangeT << jeu.tabT[i].portee;
                TextSurface = TTF_RenderText_Solid(font,rangeT.str().c_str(),font_color);
                font_im.setSurface(TTF_RenderText_Solid(font,rangeT.str().c_str(),font_color));
                font_im.loadFromCurrentSurface(renderer);
                SDL_Rect NbRange;
                NbRange.x = 1435;NbRange.y = 880;NbRange.w = TextSurface->w;NbRange.h = TextSurface->h; 
                SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&NbRange);
                SDL_FreeSurface(TextSurface);
                rangeT.str("");
                rangeT.clear();
                
                }
            if(jeu.tabT[i].getX() == jeu.posClick.x && jeu.tabT[i].getY() == jeu.posClick.y && jeu.tabT[i].type == 2){
                im_Tour2.draw(renderer,1200,650,TAILLE_SPRITE*2.5,TAILLE_SPRITE*2.5);
                
                font = TTF_OpenFont("Data/alagard.ttf",30);

                dmgT << jeu.tabT[i].degat;
                TextSurface = TTF_RenderText_Solid(font,dmgT.str().c_str(),font_color);
                font_im.setSurface(TTF_RenderText_Solid(font,dmgT.str().c_str(),font_color));
                font_im.loadFromCurrentSurface(renderer);
                SDL_Rect NbDmg;
                NbDmg.x = 1435;NbDmg.y = 680;NbDmg.w = TextSurface->w;NbDmg.h = TextSurface->h; 
                SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&NbDmg);
                SDL_FreeSurface(TextSurface);
                dmgT.str("");
                dmgT.clear();

                vitT << jeu.tabT[i].vitesse;
                TextSurface = TTF_RenderText_Solid(font,vitT.str().c_str(),font_color);
                font_im.setSurface(TTF_RenderText_Solid(font,vitT.str().c_str(),font_color));
                font_im.loadFromCurrentSurface(renderer);
                SDL_Rect NbVit;
                NbVit.x = 1435;NbVit.y = 780;NbVit.w = TextSurface->w;NbVit.h = TextSurface->h; 
                SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&NbVit);
                SDL_FreeSurface(TextSurface);
                vitT.str("");
                vitT.clear();

                rangeT << jeu.tabT[i].portee;
                TextSurface = TTF_RenderText_Solid(font,rangeT.str().c_str(),font_color);
                font_im.setSurface(TTF_RenderText_Solid(font,rangeT.str().c_str(),font_color));
                font_im.loadFromCurrentSurface(renderer);
                SDL_Rect NbRange;
                NbRange.x = 1435;NbRange.y = 880;NbRange.w = TextSurface->w;NbRange.h = TextSurface->h; 
                SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&NbRange);
                SDL_FreeSurface(TextSurface);
                rangeT.str("");
                rangeT.clear();

                }
            if(jeu.tabT[i].getX() == jeu.posClick.x && jeu.tabT[i].getY() == jeu.posClick.y && jeu.tabT[i].type == 3){
                im_Tour3.draw(renderer,1200,650,TAILLE_SPRITE*2.5,TAILLE_SPRITE*2.5);
                
                font = TTF_OpenFont("Data/alagard.ttf",30);

                dmgT << jeu.tabT[i].degat;
                TextSurface = TTF_RenderText_Solid(font,dmgT.str().c_str(),font_color);
                font_im.setSurface(TTF_RenderText_Solid(font,dmgT.str().c_str(),font_color));
                font_im.loadFromCurrentSurface(renderer);
                SDL_Rect NbDmg;
                NbDmg.x = 1435;NbDmg.y = 680;NbDmg.w = TextSurface->w;NbDmg.h = TextSurface->h; 
                SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&NbDmg);
                SDL_FreeSurface(TextSurface);
                dmgT.str("");
                dmgT.clear();

                vitT << jeu.tabT[i].vitesse;
                TextSurface = TTF_RenderText_Solid(font,vitT.str().c_str(),font_color);
                font_im.setSurface(TTF_RenderText_Solid(font,vitT.str().c_str(),font_color));
                font_im.loadFromCurrentSurface(renderer);
                SDL_Rect NbVit;
                NbVit.x = 1435;NbVit.y = 780;NbVit.w = TextSurface->w;NbVit.h = TextSurface->h; 
                SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&NbVit);
                SDL_FreeSurface(TextSurface);
                vitT.str("");
                vitT.clear();

                rangeT << jeu.tabT[i].portee;
                TextSurface = TTF_RenderText_Solid(font,rangeT.str().c_str(),font_color);
                font_im.setSurface(TTF_RenderText_Solid(font,rangeT.str().c_str(),font_color));
                font_im.loadFromCurrentSurface(renderer);
                SDL_Rect NbRange;
                NbRange.x = 1435;NbRange.y = 880;NbRange.w = TextSurface->w;NbRange.h = TextSurface->h; 
                SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&NbRange);
                SDL_FreeSurface(TextSurface);
                rangeT.str("");
                rangeT.clear();
                
                }
            if(jeu.tabT[i].getX() == jeu.posClick.x && jeu.tabT[i].getY() == jeu.posClick.y && jeu.tabT[i].type == 4){
                im_Tour4.draw(renderer,1200,650,TAILLE_SPRITE*2.5,TAILLE_SPRITE*2.5);
                
                font = TTF_OpenFont("Data/alagard.ttf",30);

                dmgT << jeu.tabT[i].degat;
                TextSurface = TTF_RenderText_Solid(font,dmgT.str().c_str(),font_color);
                font_im.setSurface(TTF_RenderText_Solid(font,dmgT.str().c_str(),font_color));
                font_im.loadFromCurrentSurface(renderer);
                SDL_Rect NbDmg;
                NbDmg.x = 1435;NbDmg.y = 680;NbDmg.w = TextSurface->w;NbDmg.h = TextSurface->h; 
                SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&NbDmg);
                SDL_FreeSurface(TextSurface);
                dmgT.str("");
                dmgT.clear();

                vitT << jeu.tabT[i].vitesse;
                TextSurface = TTF_RenderText_Solid(font,vitT.str().c_str(),font_color);
                font_im.setSurface(TTF_RenderText_Solid(font,vitT.str().c_str(),font_color));
                font_im.loadFromCurrentSurface(renderer);
                SDL_Rect NbVit;
                NbVit.x = 1435;NbVit.y = 780;NbVit.w = TextSurface->w;NbVit.h = TextSurface->h; 
                SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&NbVit);
                SDL_FreeSurface(TextSurface);
                vitT.str("");
                vitT.clear();

                rangeT << jeu.tabT[i].portee;
                TextSurface = TTF_RenderText_Solid(font,rangeT.str().c_str(),font_color);
                font_im.setSurface(TTF_RenderText_Solid(font,rangeT.str().c_str(),font_color));
                font_im.loadFromCurrentSurface(renderer);
                SDL_Rect NbRange;
                NbRange.x = 1435;NbRange.y = 880;NbRange.w = TextSurface->w;NbRange.h = TextSurface->h; 
                SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&NbRange);
                SDL_FreeSurface(TextSurface);
                rangeT.str("");
                rangeT.clear();

                }
            //cout << "X : " << jeu.tabT[i].getX() << " Y : " << jeu.tabT[i].getY() << endl;
            //cout << "click X : " << jeu.posClick.x << " click Y : " << jeu.posClick.y << endl;

            // reste  fonctionnement boutons
        }

        im_Cadre.draw(renderer,1163,600,TAILLE_SPRITE*13.5,TAILLE_SPRITE*7.5);
        im_Cadre.draw(renderer,1563,650,TAILLE_SPRITE*4,TAILLE_SPRITE*2);
        im_Cadre.draw(renderer,1563,800,TAILLE_SPRITE*4,TAILLE_SPRITE*2);

        font = TTF_OpenFont("Data/alagard.ttf",30);
        
        TextSurface = TTF_RenderText_Solid(font,"Degats",font_color);
        font_im.setSurface(TTF_RenderText_Solid(font,"Degats",font_color));
        font_im.loadFromCurrentSurface(renderer);
        SDL_Rect txtDegats;
        txtDegats.x = 1400;txtDegats.y = 650;txtDegats.w = TextSurface->w;txtDegats.h = TextSurface->h;
        SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&txtDegats);
        SDL_FreeSurface(TextSurface);
        
        TextSurface = TTF_RenderText_Solid(font,"Vitesse",font_color);
        font_im.setSurface(TTF_RenderText_Solid(font,"Vitesse",font_color));
        font_im.loadFromCurrentSurface(renderer);
        SDL_Rect txtVitesse;
        txtVitesse.x = 1400;txtVitesse.y = 750;txtVitesse.w = TextSurface->w;txtVitesse.h = TextSurface->h;
        SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&txtVitesse);
        SDL_FreeSurface(TextSurface);

        TextSurface = TTF_RenderText_Solid(font,"Portee",font_color);
        font_im.setSurface(TTF_RenderText_Solid(font,"Portee",font_color));
        font_im.loadFromCurrentSurface(renderer);
        SDL_Rect txtPortee;
        txtPortee.x = 1400;txtPortee.y = 850;txtPortee.w = TextSurface->w;txtPortee.h = TextSurface->h;
        SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&txtPortee);
        SDL_FreeSurface(TextSurface);

        font = TTF_OpenFont("Data/alagard.ttf",25);
        TextSurface = TTF_RenderText_Solid(font,"Prix upgrade",font_color);
        font_im.setSurface(TTF_RenderText_Solid(font,"Prix upgrade",font_color));
        font_im.loadFromCurrentSurface(renderer);
        SDL_Rect txtUpgrade1;
        txtUpgrade1.x = 1200;txtUpgrade1.y = 800;txtUpgrade1.w = TextSurface->w;txtUpgrade1.h = TextSurface->h;
        SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&txtUpgrade1);
        SDL_FreeSurface(TextSurface);

        font = TTF_OpenFont("Data/alagard.ttf",40);
        TextSurface = TTF_RenderText_Solid(font,"Upgrade",font_color);
        font_im.setSurface(TTF_RenderText_Solid(font,"Upgrade",font_color));
        font_im.loadFromCurrentSurface(renderer);
        SDL_Rect txtUpgrade2;
        txtUpgrade2.x = 1580;txtUpgrade2.y = 680;txtUpgrade2.w = TextSurface->w;txtUpgrade2.h = TextSurface->h;
        SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&txtUpgrade2);
        SDL_FreeSurface(TextSurface);

        TextSurface = TTF_RenderText_Solid(font,"Vendre",font_color);
        font_im.setSurface(TTF_RenderText_Solid(font,"Vendre",font_color));
        font_im.loadFromCurrentSurface(renderer);
        SDL_Rect txtSell;
        txtSell.x = 1595;txtSell.y = 830;txtSell.w = TextSurface->w;txtSell.h = TextSurface->h;
        SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&txtSell);
        SDL_FreeSurface(TextSurface);

    }

}

void SDLSimple::sdlBoucle () {
    jeu.ter.generation();
    SDL_Event events;
	bool quit = false;
    int hx, hy;
   
    unsigned int NewT = SDL_GetTicks();
    unsigned int OldT = SDL_GetTicks();
    double delta = 0;

    Uint32 t = SDL_GetTicks(), nt;

	// tant que ce n'est pas la fin ...
	while (!quit) {
        NewT=SDL_GetTicks();
        delta += NewT - OldT;

        if(delta > 1000/60){
        
            if(jeu.ecrans){
                SDL_GetMouseState(&hx, &hy);

                while (SDL_PollEvent(&events)) {
                    if (events.type == SDL_QUIT) quit = true;           // Si l'utilisateur a clique sur la croix de fermeture
                    else if (events.type == SDL_KEYDOWN) {              // Si une touche est enfoncee
                        bool pauseTour = false;
                        switch ( events.key.keysym.scancode) {
                        case SDL_SCANCODE_Q:
                            pauseTour = jeu.actionClavier('a');    // car Y inverse
                            break;
                        case SDL_SCANCODE_W:
                            pauseTour = jeu.actionClavier('z');     // car Y inverse
                            break;
                        case SDL_SCANCODE_E:
                            pauseTour = jeu.actionClavier('e');
                            break;
                        case SDL_SCANCODE_R:
                            pauseTour = jeu.actionClavier('r');
                            break;
                        case SDL_BUTTON_LEFT:
                            pauseTour = jeu.actionSouris('g');
                            break;
                        case SDL_SCANCODE_ESCAPE:
                            break;
                        case SDL_SCANCODE_A:
                            quit = true;
                            break;
                        default: break; 
                        }
                        if ((withSound) && (pauseTour)){}
                            //Mix_PlayChannel(-1,sound,0);
                    }else if(events.type == SDL_MOUSEBUTTONDOWN){
                        bool test;
                        if(events.button.clicks == 1){
                            test = jeu.actionSouris('g');
                            for (int x = 705 ; x <= 1164 ; x++) {
                                for (int y = 280 ; y <= 394 ; y++) {
                                    if (hx == x && hy == y) {
                                        jeu.ecrans = !jeu.ecrans;
                                    }
                                }
                            }
                            for (int x = 705 ; x <= 1164 ; x++) {
                                for (int y = 420 ; y <= 534 ; y++) {
                                    if (hx == x && hy == y) {
                                        quit = !quit;
                                    }
                                }
                            }
                        }                    
                        if((withSound) && (test)){}
                    }
                }
                sdlAffMenu();
                SDL_RenderPresent(renderer);
                delta = 0;

            }else{
                SDL_GetMouseState(&hx, &hy);

                nt = SDL_GetTicks();
                jeu.actionsAutomatiques();

                for(int i=0;i<int(jeu.tabE.size());i++){
                    if(jeu.tabE[i].position.y == jeu.ter.getY()-1){
                        jeu.diplome--;
                        jeu.tabE.erase(jeu.tabE.begin() + i);
                    }
                    if(jeu.tabE[i].vie <= 0){
                        jeu.GainFonds(jeu.tabE[i]);
                        jeu.kill += 1;
                        jeu.tabE.erase(jeu.tabE.begin() + i);
                    }
                }
                    
                if(jeu.diplome<0){quit=true;}
                for(int x=0;x<int(jeu.tabE.size());++x){
                    bool dep = jeu.tabE[x].Charg();
                    if(dep){
                        Vecteur direction = jeu.ter.prochaineCase(jeu.tabE[x].position);
                        jeu.tabE[x].Deplacement(direction);
                    }

                    //debug pos ennemi
                    //cout<<endl<<"Ennemi "<<x+1<<" : "<<jeu.tabE[x].getX()<<" "<<jeu.tabE[x].getY()<<endl;
                }

                // tant qu'il y a des évenements à traiter (cette boucle n'est pas bloquante)
                while (SDL_PollEvent(&events)) {
                    if (events.type == SDL_QUIT) quit = true;           // Si l'utilisateur a clique sur la croix de fermeture
                    else if (events.type == SDL_KEYDOWN) {              // Si une touche est enfoncee
                        bool pauseTour = false;
                        switch ( events.key.keysym.scancode) {
                        case SDL_SCANCODE_Q:
                            pauseTour = jeu.actionClavier('a');    // car Y inverse
                            break;
                        case SDL_SCANCODE_W:
                            pauseTour = jeu.actionClavier('z');     // car Y inverse
                            break;
                        case SDL_SCANCODE_E:
                            pauseTour = jeu.actionClavier('e');
                            break;
                        case SDL_SCANCODE_R:
                            pauseTour = jeu.actionClavier('r');
                            break;
                        case SDL_BUTTON_LEFT:
                            pauseTour = jeu.actionSouris('g');
                            break;
                        case SDL_SCANCODE_ESCAPE:
                            break;
                        case SDL_SCANCODE_A:
                            jeu.ecrans = !jeu.ecrans;
                            break;
                        default: break; 
                        }
                        if ((withSound) && (pauseTour)){}
                            //Mix_PlayChannel(-1,sound,0);
                    }else if(events.type == SDL_MOUSEBUTTONDOWN){
                        bool test;
                        if(events.button.clicks == 1){
                            test = jeu.actionSouris('g');
                            jeu.ajoutTour(Vecteur(int((hy-80) / TAILLE_SPRITE),int(hx / TAILLE_SPRITE)),jeu.tourSel);

                            if (jeu.tourMenu) {
                                for (int x = 1563 ; x <= 1707 ; x++) { // upgrade
                                    for (int y = 650 ; y <= 698 ; y++) {
                                        if (hx == x && hy == y) {
                                            // fonction upgrade
                                        }
                                    }
                                }

                                for (int x = 1563 ; x <= 1707 ; x++) { // vendre
                                    for (int y = 800 ; y <= 848 ; y++) {
                                         if (hx == x && hy == y) {
                                            //fonction vendre
                                            jeu.tourMenu = !jeu.tourMenu;
                                        }
                                    }
                                }
                            }
                        }                 
                        if((withSound) && (test)){}
                    }
                }

                // on affiche le jeu sur le buffer cach�
                sdlAffJeu();
                if (int(hx / TAILLE_SPRITE) >= 0 && int(hx / TAILLE_SPRITE) <= 37 && int((hy-80) / TAILLE_SPRITE) >= 0 && int((hy-80) / TAILLE_SPRITE) <= 9){
                    im_SourisSel.draw(renderer,int(hx / TAILLE_SPRITE)*TAILLE_SPRITE,int((hy-80) / TAILLE_SPRITE)*TAILLE_SPRITE+80,TAILLE_SPRITE,TAILLE_SPRITE);
                }

                // on permute les deux buffers (cette fonction ne doit se faire qu'une seule fois dans la boucle)
                SDL_RenderPresent(renderer);
                delta = 0;
            }
        }
        OldT = SDL_GetTicks();
	}
}
