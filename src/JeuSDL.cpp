#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cstring>
#include <fstream>
#include <cassert>
#include <vector>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "JeuSDL.h"
#include "Jeu.h"
#include "Combat.h"

using namespace std;

/*
	Classe Image
*/
Image::Image()
{
	surface = NULL;
	texture = NULL;
	a_change = false;
}

bool Image::loadSurface(const string & nom_image)
{
	// Chargement de l'image
	surface = IMG_Load(nom_image.c_str());
	if(surface == NULL) {
		cout << "Erreur de chargement de l'image " << nom_image << endl;
		cout << "(IMG_GetError) " << IMG_GetError() << endl;
		cout << "(SDL_GetError) " << SDL_GetError() << endl;
		return false;
	}
/*
    SDL_Surface * surfaceCorrectPixelFormat = SDL_ConvertSurfaceFormat(surface,SDL_PIXELFORMAT_ARGB8888,0);
    SDL_FreeSurface(surface);
    surface = surfaceCorrectPixelFormat;
*/
	return true;
}

bool Image::loadTexture(const string & nom_image, SDL_Renderer * render)
{
	// Chargement de l'image
	if (!loadSurface(nom_image)) {
		return false;
	}
	
	// Chargement de la texture
	texture = SDL_CreateTextureFromSurface(render,surface);
    if (texture == NULL) {
        cout << "Erreur: probleme creation texture pour " << nom_image << endl;
        return false;
    }
    
    return true;
}

void Image::draw(SDL_Renderer * render, int x, int y, int w, int h)
{
	// Positionnement
    int ok;
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = (w < 0) ? surface->w : w;
    r.h = (w < 0) ? surface->h : h;

	// Mise a jour de la texture si elle a change
    if (a_change) {
        ok = SDL_UpdateTexture(texture,NULL,surface->pixels,surface->pitch);
        assert(ok == 0);
        a_change = false;
    }

	// Affichage de la texture
    ok = SDL_RenderCopy(render,texture,NULL,&r);
    assert(ok == 0);
}








/*
	Classe JeuSDL
*/
JeuSDL::JeuSDL() : Jeu()
{
	fenetre = NULL;
	renderer = NULL;
	//afficherInit();
}

JeuSDL::~JeuSDL()
{
	if (renderer != nullptr) {
		SDL_DestroyRenderer(renderer);
	}
	if (fenetre != nullptr) {
		SDL_DestroyWindow(fenetre);
	}
	IMG_Quit();
	SDL_Quit();
}

bool JeuSDL::afficherInit()
{
	// Initialisation SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "SDL_Init Erreur: " << SDL_GetError() << endl;
		return false;
	}

	// Initialisation SDL_image pour utiliser les autres formats d'image
    int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		cout << "IMG_Init Erreur: (IMG_GetError) " << IMG_GetError() << ", (SDL_GetError) " << SDL_GetError() << endl;
		SDL_Quit();
		return false;
	}

	// Creation fenetre
	fenetre = SDL_CreateWindow("A vos Risk et perils!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 1062, SDL_WINDOW_SHOWN);
	if (fenetre == NULL) {
		cout << "SDL_CreateWindow Erreur: " << SDL_GetError() << endl;
		IMG_Quit();
		SDL_Quit();
		return false;
	}

	// Creation renderer
	renderer = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL) {
		cout << "SDL_CreateRenderer Erreur: " << SDL_GetError() << endl;
		SDL_DestroyWindow(fenetre);
		IMG_Quit();
		SDL_Quit();
		return false;
	}

/*
	// Chargement de l'image
	surface = IMG_Load("data/Risk_modif.xcf");
	
	if(surface == NULL) {
		cout << "Erreur de chargement de l'image " << "data/Risk.jpg" << endl;
		cout << "(IMG_GetError) " << IMG_GetError() << endl;
		cout << "(SDL_GetError) " << SDL_GetError() << endl;
		return false;
	}

	// Chargement de la texture
	texture = SDL_CreateTextureFromSurface(renderer,surface);
    if (texture == NULL) {
        cout << "Erreur: probleme creation texture pour " << "data/Risk.jpg" << endl;
        exit(1);
    }
*/

	// On vide le renderer
	SDL_RenderClear(renderer);
	
	if (ecran_titre.loadTexture(string("data/Risk_modif.xcf"), renderer)) {
		ecran_titre.draw(renderer,0,0);
	}

/*
	// Affichage de la texture
    int ok;
    SDL_Rect r;
    r.x = 0;
    r.y = 0;
    r.w = surface->w;
    r.h = surface->h;

    if (a_change) {
        ok = SDL_UpdateTexture(texture,NULL,surface->pixels,surface->pitch);
        assert(ok == 0);
        a_change = false;
    }

    ok = SDL_RenderCopy(renderer,texture,NULL,&r);
    assert(ok == 0);
*/


	// Mise a jour buffer
	SDL_RenderPresent(renderer);
	SDL_Delay(20000);

	return true;
}

void JeuSDL::quitterSDL()
{
	if (renderer != NULL) {
		SDL_DestroyRenderer(renderer);
	}
	if (fenetre != NULL) {
		SDL_DestroyWindow(fenetre);
	}
	IMG_Quit();
	SDL_Quit();
}


