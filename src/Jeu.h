#ifndef JEU_H
#define JEU_H

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include "Terrain.h"
#include "Joueur.h"

using namespace std;

class Jeu {

	private:

		unsigned int nb_joueur;
		Terrain terrain;
  		vector<Joueur> tab_joueur;
  		
  		/** @brief Initialise la carte a utiliser */
  		void initJeu ();

	public:

		/** @brief : constructeur par default */
		Jeu();

		/** @brief : lancer le jeu */
		void lancerJeu();

		/** @brief : met fin la partie */
		bool finPartie();

		/** @brief : afficher du texte d'aide pour les utilisateurs */
		void afficherAide();

		/** @brief : permet d'entrer en phase de manoeuvre */
		void phaseManoeuvre ();

		/** @brief : permet d'entrer en phase de renfort */
		void phaseRenfort();

		/** @brief : permet d'entrer en phase d'attaque */
		void phaseAttaque();

		/** @brief : permet de mettre fin au tour */
		bool fintour();
};
	



#endif