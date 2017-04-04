#ifndef JEUSDL_H
#define JEUSDL_H

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "Jeu.h"

using namespace std;

class JeuSDL : public Jeu
{

	protected:
		SDL_Surface * surface;
		SDL_Texture * texture;
		SDL_Window * fenetre;
		SDL_Renderer * renderer;
		SDL_Rect r;

		/** 
		* @brief Initialise les elements SDL necessaire a l'affichage graphique du jeu
		* @return true si tout s'est bien passé, false s'il y a eu une erreur
		*/

		/** @brief Quitte la SDL proprement en fin de programme */
		void quitterSDL();

	public:
		bool afficherInit();
		JeuSDL();
		~JeuSDL();
	
};

#endif
