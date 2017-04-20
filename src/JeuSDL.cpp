#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <cstring>
#include <fstream>
#include <cassert>
#include <vector>
#include <unordered_map>
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

    SDL_Surface * surfaceCorrectPixelFormat = SDL_ConvertSurfaceFormat(surface,SDL_PIXELFORMAT_ARGB8888,0);
    SDL_FreeSurface(surface);
    surface = surfaceCorrectPixelFormat;

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
	pix.w = 1;
	pix.h = 1;
	r = 0;
	g = 0;
	b = 0;
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

	//Initialisation de SDL_TTF
	if( TTF_Init() == -1 ) {
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
	TTF_Quit();
	SDL_Quit();
}





void JeuSDL::initJeu()
{
	Jeu::initJeu();
	lireDonneesCarte("data/code_RVB");
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
					pix.x = souris_x;
					pix.y = souris_y;
					SDL_RenderReadPixels(renderer, &pix, SDL_PIXELFORMAT_ARGB8888, &current_pix, sizeof(current_pix));
					SDL_GetRGB(current_pix, carte.surface->format, &r, &g, &b);
					system("clear");
					cout << "souris_x : " << souris_x << "	,	souris_y : " << souris_y << endl;
					cout << "r : " << (int)r << endl;
					cout << "g : " << (int)g << endl;
					cout << "b : " << (int)b << endl;
					break;
			}
		}
	}
}





void JeuSDL::lireDonneesCarte(const string & chemin)
{

	ifstream fichier(chemin.c_str(), ios::in);
	if (!fichier.is_open()) {
		cout << "Erreur: le fichier " << chemin << " n'a pas pu etre ouvert" << endl;
		exit(1);
	}

	string ligne;
	int rouge, vert, bleu;
	while (!fichier.eof()) {
		//getline(fichier, ligne);
		fichier >> rouge;
		//fichier >> vert;
		//fichier >> bleu;
		//CodeCouleur[ string(ligne) ] = CodeRGB(rouge,vert,bleu);
	}

	//unordered_map<string, CodeRGB>::iterator it;
	/*
	for (unordered_map<string, CodeRGB>::iterator it = CodeCouleur.begin() ; it != CodeCouleur.end() ; ++it) {
		cout << it->first << endl;
		cout << "R: " << it->second.R << endl;
		cout << "G: " << it->second.G << endl;
		cout << "B: " << it->second.B << endl;
		cout << endl;

	}
*/

	fichier.close();

/*
	CodeCouleur[ string("Alaska") ] = CodeRGB( 223, 192, 88 );
	CodeCouleur[ string("Alberta") ] = CodeRGB( 226, 192, 90 );
	CodeCouleur[ string("Amerique centrale") ] = CodeRGB( 231, 200, 97 );
	CodeCouleur[ string("Etats de l'Est") ] = CodeRGB( 228, 200, 95 );
	CodeCouleur[ string("Groenland") ] = CodeRGB( 231, 200, 95 );
	CodeCouleur[ string("Territoires du Nord-Ouest") ] = CodeRGB( 225, 192, 88 );
	CodeCouleur[ string("Ontario") ] = CodeRGB( 225, 192, 88 );
	CodeCouleur[ string("Quebec") ] = CodeRGB( 221, 192, 88 );
	CodeCouleur[ string("Etats de l'Ouest") ] = CodeRGB( 207, 193, 84);
	CodeCouleur[ string("Afghanistan") ] = CodeRGB( 169, 201, 94 );
	CodeCouleur[ string("Chine") ] = CodeRGB( 169, 201, 96 );
	CodeCouleur[ string("Inde") ] = CodeRGB( 173, 204, 97 );
	CodeCouleur[ string("") ] = CodeRGB(,,);
	CodeCouleur[ string("") ] = CodeRGB(,,);
	CodeCouleur[ string("") ] = CodeRGB(,,);
	CodeCouleur[ string("") ] = CodeRGB(,,);
	CodeCouleur[ string("") ] = CodeRGB(,,);
	CodeCouleur[ string("") ] = CodeRGB(,,);
	CodeCouleur[ string("") ] = CodeRGB(,,);
	CodeCouleur[ string("") ] = CodeRGB(,,);
	CodeCouleur[ string("") ] = CodeRGB(,,);
	CodeCouleur[ string("") ] = CodeRGB(,,);
	CodeCouleur[ string("") ] = CodeRGB(,,);
	CodeCouleur[ string("") ] = CodeRGB(,,);
	CodeCouleur[ string("") ] = CodeRGB(,,);
	CodeCouleur[ string("") ] = CodeRGB(,,);
	CodeCouleur[ string("") ] = CodeRGB(,,);
	CodeCouleur[ string("") ] = CodeRGB(,,);
	CodeCouleur[ string("") ] = CodeRGB(,,);
	CodeCouleur[ string("") ] = CodeRGB(,,);
	CodeCouleur[ string("") ] = CodeRGB(,,);
	CodeCouleur[ string("") ] = CodeRGB(,,);
	CodeCouleur[ string("") ] = CodeRGB(,,);
	CodeCouleur[ string("") ] = CodeRGB(,,);
	CodeCouleur[ string("") ] = CodeRGB(,,);
	CodeCouleur[ string("") ] = CodeRGB(,,);
	CodeCouleur[ string("") ] = CodeRGB(,,);
	CodeCouleur[ string("") ] = CodeRGB(,,);
	CodeCouleur[ string("") ] = CodeRGB(,,);
	CodeCouleur[ string("") ] = CodeRGB(,,);
	CodeCouleur[ string("") ] = CodeRGB(,,);
	CodeCouleur[ string("") ] = CodeRGB(,,);
	CodeCouleur[ string("") ] = CodeRGB(,,);
*/
}




void JeuSDL::MenuSDL()
{
	bool r = false;
	SDL_Event evenements;
	bool quitter = false;


	//--------------------------------------------------




	//---------------------------------------------


	r = afficherInit();
	SDL_RenderClear(renderer);
	if(r == true)
	{
		menu.loadTexture("data/cavalerie-france.xcf",renderer);
		menu.draw(renderer,0,0);
	}
	else
	{
		cout << "probleme avec la sdl" <<endl;
		quitterSDL();
	}

	SDL_RenderPresent(renderer);

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
			case SDL_MOUSEBUTTONUP:
				//SDL_GetMouseState(&souris_x, &souris_y);
				souris_x=evenements.button.x;
				souris_y=evenements.button.y;
				cout << "souris_x : " << souris_x << "	,	souris_y : " << souris_y << endl;

				if(souris_x > 46 && souris_x < 176 && souris_y > 620 && souris_y < 623) //pour le bouton quitter
				{
					quitter = true ;
				}

				if(souris_x > 52 && souris_x < 125 && souris_y > 550 && souris_y < 565)
				{
					Aide.loadTexture("data/fond-gris.xcf",renderer);
					SDL_RenderClear(renderer);
					Aide.draw(renderer,0,0);
					SDL_RenderPresent(renderer);


				}
				if(souris_x > 33 && souris_x < 222 && souris_y > 700 && souris_y < 710)
				{
					SDL_RenderClear(renderer);
					menu.draw(renderer,0,0);
					SDL_RenderPresent(renderer);
				}

				break;
		}
	}
}
}
