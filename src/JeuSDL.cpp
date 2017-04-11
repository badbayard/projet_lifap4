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
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = (w < 0) ? surface->w : w;
    rect.h = (w < 0) ? surface->h : h;

	// Mise a jour de la texture si elle a change
    if (a_change) {
        ok = SDL_UpdateTexture(texture,NULL,surface->pixels,surface->pitch);
        assert(ok == 0);
        a_change = false;
    }

	// Affichage de la texture
    ok = SDL_RenderCopy(render,texture,NULL,&rect);
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
/*
	if (renderer != nullptr) {
		SDL_DestroyRenderer(renderer);
	}
	if (fenetre != nullptr) {
		SDL_DestroyWindow(fenetre);
	}
	IMG_Quit();
	SDL_Quit();
*/
	quitterSDL();
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

	// On vide le renderer
	SDL_RenderClear(renderer);
	
	// Mise a jour buffer
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





void JeuSDL::initJeu()
{
	Jeu::initJeu();
	
}





void JeuSDL::boucleJeu()
{
	// Initialisation donnees de jeu
	initJeu();
	
	// Affichage carte
	SDL_RenderClear(renderer);
	if (carte.loadTexture(string("data/Risk_modif.xcf"), renderer)) {
		carte.draw(renderer);
	}
	SDL_RenderPresent(renderer);

	// File d'evenements : stocke toutes les donnees d'evenement
	SDL_Event evenements;
	bool quitter = false;
	
	// Tant qu'un evenement quitter n'a pas ete declenche
	while (!quitter) {
		// Tant qu'il reste des evenements a traiter dans la file d'evenement
		while (SDL_PollEvent( &evenements )) {	// Recuperation d'un evenement

			// Selon le type d'evenement
			switch (evenements.type) {
				// Si on apuuie sur le bouton X de la fenetre
				case SDL_QUIT:
					quitter = true;
					break;
	
				// Si on appuie sur une touche du clavier
				case SDL_KEYDOWN:
					// Selon la touche appuiee
					switch (evenements.key.keysym.scancode) {
						// Si on appuie sur la touche Escape
						case SDL_SCANCODE_ESCAPE:
							quitter = true;
							break;
	
						// Pour les autres touches non gerees par le switch
						default:
							break;
					}
					break;
	
				// Evenements de la souris
				// Au mouvement de la souris
				case SDL_MOUSEMOTION:
					SDL_GetMouseState(&souris_x, &souris_y);
					cout << "souris_x : " << souris_x << "	,	souris_y : " << souris_y << endl;
					//SDL_GetRGB(, , &r, &g, &b);
					break;
			}
		}
	}
}
