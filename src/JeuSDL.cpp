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

JeuSDL::JeuSDL() : Jeu()
{
	surface = NULL;
	texture = NULL;
	fenetre = NULL;
	renderer = NULL;
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
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		cout << "SDL_Init Error: " << SDL_GetError() << endl;
		return false;
	}

	// Initialisation SDL_image pour utiliser les autres formats d'image
	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
		cout << "IMG_Init Error: (IMG_GetError) " << IMG_GetError() << ", (SDL_GetError) " << SDL_GetError() << endl;
		SDL_Quit();
		return false;
	}

	// Creation fenetre
	fenetre = SDL_CreateWindow("A vos Risk et perils!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 1062, SDL_WINDOW_SHOWN);
	if (fenetre == NULL) {
		cout << "SDL_CreateWindow Error: " << SDL_GetError() << endl;
		IMG_Quit();
		SDL_Quit();
		return false;
	}

	// Creation renderer
	renderer = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL) {
		cout << "SDL_CreateRenderer Error: " << SDL_GetError() << endl;
		SDL_DestroyWindow(fenetre);
		IMG_Quit();
		SDL_Quit();
		return false;
	}

	return true;
}

void JeuSDL::quitterSDL()
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