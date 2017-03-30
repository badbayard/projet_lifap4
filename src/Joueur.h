#ifndef JOUEUR_H
#define JOUEUR_H

#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <fstream>
#include <cassert>
#include <vector>

#include "Region.h"

using namespace std ;

class Joueur {

	private : 

		string couleur;
		string nom_joueur;
		unsigned int nb_regions;
		unsigned int nb_regiments;
		vector<Region*> tab_region ;

	public:
		/**
		* @brief Constructeur de la classe Joueur
		* @param
		*/ 
		Joueur(const string & nom = "", const string & couleur_joueur = "");
		
		/** @brief : Recupére la couleur du joueur */
		string  getCouleurJoueur() const;

		/** @brief : modifie la couleur du joueur  
		 * @param : couleur_joueur chaine de caractére
		 * */ 
		void setCouleurJoueur(string couleur_joueur);

		/** @brief : Recupére le nombre de region du joueur */
		unsigned int getNbRegions() const;

		/** @brief : modifie le nombre de region 
		 * @param : nb_Regions entier
		 * */
		void setNbRegions(unsigned int nb_Regions);

		/** @brief : Recupére le nombre de regiments du joueur */
		unsigned int getNbRegiments () const;

		/** @brief : modifie le nombre de regiments 
		 * @param : nb_Regiments entier */
		void setNbRegiments (unsigned int nb_Regiments);

		/** @brief : modifie le nom du joueur 
		 *  @param : nom_joueur chaine de caractere */
		void setnom_joueur (string nom);

		/** @brief:prend le nom du jouer */
		string getnom_joueur(); 

		/** @brief Accesseur pour tab_region */
		vector<Region*> & getRegionsJoueur();

		/** @brief: test de regression de la classe joueur */
		void testRegressionJoueur();


	
};

#endif