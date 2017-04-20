#ifndef JEUSDL_H
#define JEUSDL_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "Jeu.h"

using namespace std;

/*
	Classe Image
*/
class Image
{
	private:
		SDL_Texture * texture;
		bool a_change;

		bool loadSurface(const string & nom_image);

	public:
		SDL_Surface * surface;

		Image();
		~Image(){}
		bool loadTexture(const string & nom_image, SDL_Renderer * render);
		void draw(SDL_Renderer * render, int x = 0, int y = 0, int w = -1, int h = -1);
};





/*
	Classe JeuSDL
*/
class JeuSDL : public Jeu
{

	protected:
		Image carte;
		SDL_Window * fenetre;
		SDL_Renderer * renderer;
		int souris_x, souris_y;
		Uint32 current_pix;
		SDL_Rect pix;
		Uint8 r, g, b;
		Image menu;
		Image Aide;

  		/** @brief Initialise la carte a utiliser */
  		void initJeu ();

  		/** 
  		* @brief Charge les donnees de la carte contenues dans le fichier chemin 
  		* @param chemin (string) : nom du fichier contenant les codes couleur sur la carte
  		*/
  		void lireDonneesCarte (const string & chemin);
  		
	public:
		 JeuSDL();
		~JeuSDL();


		/** 
		* @brief Initialise les elements SDL necessaire a l'affichage graphique du jeu
		* @return true si tout s'est bien passé, false s'il y a eu une erreur
		*/
		bool afficherInit();

		/**
		* @brief Lance la partie
		*/
		void boucleJeu();

		/** 
		* @brief Quitte la SDL proprement en fin de programme
		*/
		void quitterSDL();

		void MenuSDL();

};

#endif
