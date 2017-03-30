#ifndef JEU_SDL_H
#define JEU_SDL_H

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

	// protected:

	public:
		JeuSDL();
		~JeuSDL();
	
};

#endif