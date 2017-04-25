#ifndef JEUSDL_H
#define JEUSDL_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <unordered_map>
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

	public:
		SDL_Surface * surface;
		TTF_Font * font;

		Image();
		~Image();
		bool loadSurface(const string & nom_image);
		bool loadTexture(const string & nom_image, SDL_Renderer * render);
		bool loadFont(const string & font_file, int ptsize = 16);
		bool writeOnTexture(const string & message, TTF_Font * ft, SDL_Renderer * render, SDL_Color text_color = {0,0,0}, SDL_Color background = {255,255,255});
		void draw(SDL_Renderer * render, int x = 0, int y = 0, int w = -1, int h = -1);
};

/*
typedef struct sCodeRGB CodeRGB;
struct sCodeRGB
{
	int R, G, B;
};
*/
class CodeRGB
{
	public:
		int R, G, B;
		
		CodeRGB(int red = 0, int green = 0, int blue = 0) {
			R = red;	G = green;	B = blue;
		}
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
		Image hover_box;
		unordered_map<string, CodeRGB> CodeCouleur;
		bool all_ok;


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
		
		string getNomParRGB(int R, int G, int B);

};

#endif
