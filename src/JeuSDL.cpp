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
	font = NULL;
	a_change = false;
}

Image::~Image()
{
	if (surface != NULL) {
		SDL_FreeSurface(surface);
		surface = NULL;
	}
	if (texture != NULL) {
		SDL_DestroyTexture(texture);
		texture = NULL;
	}
	if (font != NULL) {
		TTF_CloseFont(font);
		font = NULL;
	}
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

bool Image::loadFont(const string & font_file, int ptsize)
{
	if (font != NULL) {
		TTF_CloseFont(font);
		font = NULL;
	}
	font = TTF_OpenFont(font_file.c_str(), ptsize);
	if (font == NULL) {
		cout << "TTF_OpenFont Erreur: " << SDL_GetError() << endl;
		return false;
	}
	return true;
}

bool Image::writeOnTexture(const string & message, TTF_Font * ft, SDL_Renderer * render, SDL_Color text_color, SDL_Color background)
{
	surface = TTF_RenderUTF8_Blended_Wrapped(ft, message.c_str(), text_color, 500);
	if (surface == NULL) {
		cout << "writeOnTexture Erreur: " << SDL_GetError() << endl;
		return false;
	}
	texture = SDL_CreateTextureFromSurface(render,surface);
    if (texture == NULL) {
        cout << "Erreur: probleme creation texture TTF pour " << message << endl;
        return false;
    }
	//SDL_FreeSurface(surface);
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
	all_ok = true;
	//afficherInit();
}



JeuSDL::~JeuSDL()
{
	quitterSDL();
}




bool JeuSDL::afficherInit()
{
	// Initialisation SDL
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0) {
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

	//Initialisation de SDL_ttf
	if( TTF_Init() == -1 ) {
		cout << "TTF_Init Erreur: " << SDL_GetError() << endl;
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
	/*
	// Ce bloc cause un core dump s'il est exécuté
	if (TTF_WasInit()) {
		TTF_Quit();
	}
	*/
	SDL_Quit();
	Mix_CloseAudio();
}





void JeuSDL::initJeu()
{
	Jeu::initJeu();
	lireDonneesCarte("data/code_RVB");
	all_ok = all_ok && carte.loadTexture(string("data/Risk_modif.xcf"), renderer);
	all_ok = all_ok && hover_box.loadFont("data/tugano.ttf");

}





void JeuSDL::boucleJeu()
{
	// Initialisation donnees de jeu
	initJeu();
	bool manoeuvre = false;
	bool renfort = true;
	bool attaque = false;

	// Affichage carte
	// SDL_RenderClear(renderer);
	if (all_ok) {
		// carte.draw(renderer);
		// File d'evenements : stocke toutes les donnees d'evenement
		SDL_Event evenements;
		bool quitter = false;

		// Tant qu'un evenement quitter n'a pas ete declenche
		while (!quitter) {
			SDL_RenderClear(renderer);
			//carte.draw(renderer);

			// Tant qu'il reste des evenements a traiter dans la file d'evenement
			while (SDL_PollEvent( &evenements )) {	// Recuperation d'un evenement
			SDL_RenderClear(renderer);
			carte.draw(renderer);



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
						string pays = getNomParRGB( (int)r, (int)g, (int)b );
						string est_pays = pays;
						pays += "\n\nJoueur : " + terrain.getTabPays()[0]->getNomPays();
						pays += "\nNb regiments : ";
						system("clear");
						cout << "souris_x : " << souris_x << "	,	souris_y : " << souris_y << endl;
						cout << "r : " << (int)r << endl;
						cout << "g : " << (int)g << endl;
						cout << "b : " << (int)b << endl;
						cout << ">>> " << pays << endl;
						if (est_pays != "x") {
							hover_box.writeOnTexture( pays, hover_box.font, renderer);
							hover_box.draw(renderer, 60, 760);
						}
						break;

					// Quand on clique avec la souris
					//case SDL_MOUSEBUTTONDOWN:
						//hover_box.writeOnTexture("Hello world!", hover_box.font, renderer);
						//hover_box.draw(renderer, souris_x + 20, souris_y + 20);
						//break;
				}
				SDL_RenderPresent(renderer);
			}
			// Mise a jour buffer
			//SDL_RenderPresent(renderer);
		}
	}
	// SDL_RenderPresent(renderer);

	else {
		cout << "----> Last error: " << SDL_GetError() << endl;
	}
}



string JeuSDL::getNomParRGB(int R, int G, int B)
{
	for (unordered_map<string, CodeRGB>::iterator it = CodeCouleur.begin() ; it != CodeCouleur.end() ; ++it) {
		/*
		cout << it->first << endl;
		cout << "R: " << it->second.R << endl;
		cout << "G: " << it->second.G << endl;
		cout << "B: " << it->second.B << endl;
		cout << endl;
		*/
		if (it->second.R == R && it->second.G == G && it->second.B == B) {
			return it->first;
		}
	}
	return string("x");
}




void JeuSDL::lireDonneesCarte(const string & chemin)
{

	CodeCouleur[ string("Alaska") ] = CodeRGB( 223, 192, 88 );
	CodeCouleur[ string("Alberta") ] = CodeRGB( 226, 192, 90 );
	CodeCouleur[ string("Amerique centrale") ] = CodeRGB( 231, 200, 97 );
	CodeCouleur[ string("Etats de l'Est") ] = CodeRGB( 228, 200, 95 );
	CodeCouleur[ string("Groenland") ] = CodeRGB( 231, 200, 95 );
	CodeCouleur[ string("Territoires du Nord-Ouest") ] = CodeRGB( 225, 192, 88 );
	CodeCouleur[ string("Ontario") ] = CodeRGB( 225, 192, 90 );
	CodeCouleur[ string("Quebec") ] = CodeRGB( 221, 192, 88 );
	CodeCouleur[ string("Etats de l'Ouest") ] = CodeRGB( 207, 193, 84 );
	CodeCouleur[ string("Afghanistan") ] = CodeRGB( 169, 201, 94 );
	CodeCouleur[ string("Chine") ] = CodeRGB( 169, 201, 96 );
	CodeCouleur[ string("Inde") ] = CodeRGB( 173, 204, 97 );
	CodeCouleur[ string("Tchita") ] = CodeRGB(173,204,100);
	CodeCouleur[ string("Japon") ] = CodeRGB(175,204,100);
	CodeCouleur[ string("Kamtchaka") ] = CodeRGB(178,207,101);
	CodeCouleur[ string("Moyen-Orient") ] = CodeRGB(179,207,102);
	CodeCouleur[ string("Mongolie") ] = CodeRGB(179,207,104);
	CodeCouleur[ string("Siam") ] = CodeRGB(180,207,105);
	CodeCouleur[ string("Siberie") ] = CodeRGB(184,209,106);
	CodeCouleur[ string("Oural") ] = CodeRGB(187,212,108);
	CodeCouleur[ string("Yakoutie") ] = CodeRGB(190,214,109);
	CodeCouleur[ string("Argentine") ] = CodeRGB(215,72,88);
	CodeCouleur[ string("Bresil") ] = CodeRGB(217,73,89);
	CodeCouleur[ string("Perou") ] = CodeRGB(219,73,89);
	CodeCouleur[ string("Venezuela") ] = CodeRGB(222,74,90);
	CodeCouleur[ string("Grande-Bretagne") ] = CodeRGB(149,166,173);
	CodeCouleur[ string("Islande") ] = CodeRGB(149,166,175);
	CodeCouleur[ string("Europe du Nord") ] = CodeRGB(151,166,175);
	CodeCouleur[ string("Scandinavie") ] = CodeRGB(151,166,176);
	CodeCouleur[ string("Europe du Sud") ] = CodeRGB(151,166,178);
	CodeCouleur[ string("Ukraine") ] = CodeRGB(154,169,181);
	CodeCouleur[ string("Europe occidentale") ] = CodeRGB(156,169,181);
	CodeCouleur[ string("Congo") ] = CodeRGB(155,122,98);
	CodeCouleur[ string("Afrique de l'Est") ] = CodeRGB(157,122,98);
	CodeCouleur[ string("Egypte") ] = CodeRGB(161,125,100);
	CodeCouleur[ string("Madagascar") ] = CodeRGB(162,125,100);
	CodeCouleur[ string("Afrique du Nord") ] = CodeRGB(162,125,102);
	CodeCouleur[ string("Afrique du Sud") ] = CodeRGB(164,125,102);
	CodeCouleur[ string("Australie Orientale") ] = CodeRGB(166,72,161);
	CodeCouleur[ string("Indonesie") ] = CodeRGB(168,72,161);
	CodeCouleur[ string("Nouvelle-Guinee") ] = CodeRGB(170,72,161);
	CodeCouleur[ string("Australie Occidentale") ] = CodeRGB(173,72,161);
	//CodeCouleur[ string("") ] = CodeRGB(,,);

}






void JeuSDL::MenuSDL()
{
	bool r = false;
	SDL_Event evenements;
	bool quitter = false;
	MusicSDL();


	//--------------------------------------------------




	//---------------------------------------------


	//r = afficherInit();
	r = menu.loadTexture("data/cavalerie-france.xcf",renderer);
	SDL_RenderClear(renderer);
	if(r == true)
	{
		//menu.loadTexture("data/cavalerie-france.xcf",renderer);
		menu.draw(renderer,0,0);
	}
	else
	{
		cout << "probleme avec la sdl" <<endl;
		//quitterSDL();
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

				if(souris_x > 46 && souris_x < 176 && souris_y > 590 && souris_y < 650) //pour le bouton quitter
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


void JeuSDL::MusicSDL()
{
		//afficherInit();
	  SDL_Init(SDL_INIT_AUDIO);
		//SDL_WM_SetCaption("SDL_Mixer", NULL);
		if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer

		{

   		printf("%s", Mix_GetError());

		}
		//Mix_AllocateChannels(2);
	/*	Mix_AllocateChannels(16);
		Mix_Chunk *son ;
		son = Mix_LoadWAV("data/music_menu.wav");
		Mix_PlayChannel(2,son,0);*/

			Mix_Music *musique = NULL;

		    musique = Mix_LoadMUS("data/music_menu.mp3"); //Charge le son a l'adresse indiquée


		  /*  if(musique == NULL)  //Vérifie si le son est ok.
		    {
		        cout << "Erreur lors du chargement du son";
		    } */

		    Mix_PlayMusic(musique,-1); // on joue notre son qu'une seul fois. */

}
