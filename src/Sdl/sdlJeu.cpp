#include <cassert>
#include <time.h>
#include "sdlJeu.h"
#include <stdlib.h>

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
    window = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, dimy, dimx, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == nullptr) {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl; 
        SDL_Quit(); 
        exit(1);
    }

    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    // IMAGES
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

    // FONTS
    font = TTF_OpenFont("Data/DejaVuSansCondensed.ttf",50);
    if (font == nullptr)
        font = TTF_OpenFont("../Data/DejaVuSansCondensed.ttf",50);
    if (font == nullptr) {
            cout << "Failed to load DejaVuSansCondensed.ttf! SDL_TTF Error: " << TTF_GetError() << endl; 
            SDL_Quit(); 
            exit(1);
	}
	font_color.r = 50;font_color.g = 50;font_color.b = 255;
	font_im.setSurface(TTF_RenderText_Solid(font,"Discipuli",font_color));
	font_im.loadFromCurrentSurface(renderer);

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

void SDLSimple::sdlAff () {
	//Remplir l'écran de blanc
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

	int x,y;
    int decalage = 80;
	Terrain& ter = jeu.ter;

    // Afficher les sprites du sol et du chemin
	for (x=0;x<ter.getX();++x)
		for (y=0;y<ter.getY();++y)
			if (ter.getCase(x,y)=='O')
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
        if (ter.getCase(jeu.tabE[i].getX(),jeu.tabE[i].getY()+1) == ' ') {
            if (jeu.tabE[i].type == 1) im_Ennemi1.draw(renderer,jeu.tabE[i].getY()*TAILLE_SPRITE+mov,jeu.tabE[i].getX()*TAILLE_SPRITE+decalage,TAILLE_SPRITE,TAILLE_SPRITE);
            if (jeu.tabE[i].type == 2) im_Ennemi2.draw(renderer,jeu.tabE[i].getY()*TAILLE_SPRITE+mov,jeu.tabE[i].getX()*TAILLE_SPRITE+decalage,TAILLE_SPRITE,TAILLE_SPRITE);
            if (jeu.tabE[i].type == 3) im_Ennemi3.draw(renderer,jeu.tabE[i].getY()*TAILLE_SPRITE+mov,jeu.tabE[i].getX()*TAILLE_SPRITE+decalage,TAILLE_SPRITE,TAILLE_SPRITE);
            if (jeu.tabE[i].type == 4) im_Ennemi4.draw(renderer,jeu.tabE[i].getY()*TAILLE_SPRITE+mov,jeu.tabE[i].getX()*TAILLE_SPRITE+decalage,TAILLE_SPRITE,TAILLE_SPRITE);
        }
        else if (ter.getCase(jeu.tabE[i].getX()-1,jeu.tabE[i].getY()) == ' ') {
            if (jeu.tabE[i].type == 1) im_Ennemi1.draw(renderer,jeu.tabE[i].getY()*TAILLE_SPRITE,jeu.tabE[i].getX()*TAILLE_SPRITE+decalage-mov,TAILLE_SPRITE,TAILLE_SPRITE);
            if (jeu.tabE[i].type == 2) im_Ennemi2.draw(renderer,jeu.tabE[i].getY()*TAILLE_SPRITE,jeu.tabE[i].getX()*TAILLE_SPRITE+decalage-mov,TAILLE_SPRITE,TAILLE_SPRITE);
            if (jeu.tabE[i].type == 3) im_Ennemi3.draw(renderer,jeu.tabE[i].getY()*TAILLE_SPRITE,jeu.tabE[i].getX()*TAILLE_SPRITE+decalage-mov,TAILLE_SPRITE,TAILLE_SPRITE);
            if (jeu.tabE[i].type == 4) im_Ennemi4.draw(renderer,jeu.tabE[i].getY()*TAILLE_SPRITE,jeu.tabE[i].getX()*TAILLE_SPRITE+decalage-mov,TAILLE_SPRITE,TAILLE_SPRITE);
        }
        else if (ter.getCase(jeu.tabE[i].getX()+1,jeu.tabE[i].getY()) == ' ') {
            if (jeu.tabE[i].type == 1) im_Ennemi1.draw(renderer,jeu.tabE[i].getY()*TAILLE_SPRITE,jeu.tabE[i].getX()*TAILLE_SPRITE+decalage+mov,TAILLE_SPRITE,TAILLE_SPRITE);
            if (jeu.tabE[i].type == 2) im_Ennemi2.draw(renderer,jeu.tabE[i].getY()*TAILLE_SPRITE,jeu.tabE[i].getX()*TAILLE_SPRITE+decalage+mov,TAILLE_SPRITE,TAILLE_SPRITE);
            if (jeu.tabE[i].type == 3) im_Ennemi3.draw(renderer,jeu.tabE[i].getY()*TAILLE_SPRITE,jeu.tabE[i].getX()*TAILLE_SPRITE+decalage+mov,TAILLE_SPRITE,TAILLE_SPRITE);
            if (jeu.tabE[i].type == 4) im_Ennemi4.draw(renderer,jeu.tabE[i].getY()*TAILLE_SPRITE,jeu.tabE[i].getX()*TAILLE_SPRITE+decalage+mov,TAILLE_SPRITE,TAILLE_SPRITE);
        }
    }

    im_Argent.draw(renderer,90,270+decalage,TAILLE_SPRITE*2,TAILLE_SPRITE);
    im_Diplome.draw(renderer,90,370+decalage,TAILLE_SPRITE*2,TAILLE_SPRITE);

    // Ecrire un titre par dessus
    SDL_Rect positionTitre;
    positionTitre.x = 270;positionTitre.y = 490;positionTitre.w = 100;positionTitre.h = 30; 
    SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&positionTitre);

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
        

            SDL_GetMouseState(&hx, &hy);

            nt = SDL_GetTicks();
            if (nt-t>1000) {
                jeu.actionsAutomatiques();
                t = nt;
            }

                for(int i=0;i<int(jeu.tabE.size());i++){
				if(jeu.tabE[i].position.y == jeu.ter.getY()-1){
					jeu.diplome--;
					jeu.tabE.erase(jeu.tabE.begin() + i);
				}
				if(jeu.tabE[i].vie <= 0){
					jeu.GainFonds(jeu.tabE[i]);
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
                            jeu.ajoutTour(Vecteur(int((hy-80) / TAILLE_SPRITE),int(hx / TAILLE_SPRITE)),jeu.tourSel);
                        }                    
                        if((withSound) && (test)){}
                    }
                }

            
            // on affiche le jeu sur le buffer cach�
            sdlAff();

            // on permute les deux buffers (cette fonction ne doit se faire qu'une seule fois dans la boucle)
            SDL_RenderPresent(renderer);
            delta = 0;
        }
        OldT = SDL_GetTicks();
	}
}
