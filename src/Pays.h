#ifndef PAYS_H
#define PAYS_H

#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <fstream>
#include <cassert>
#include <vector>

#include "Region.h"

using namespace std;

class Pays {

	private :

		unsigned int nb_regions;
		string nom_pays;
		vector<Region*> tab_region;

	public :

		/** @brief Constructeur par défault */
		Pays();

		/** @brief Constructeur de la classe */
		Pays(unsigned int nbregions, const string & nom);

		/**
		* @brief Accesseur pour nb_regions
		* @return Le nombre de regions dans le Pays
		*/
		unsigned int getNbRegions () const;

		/**
		* @brief Teste si un joueur controle toutes les regions du Pays
		* @param couleur_joueur : string (couleur associee au joueur)
		* @return Vrai si le joueur controle toute la region, faux sinon
		*/
		bool controlePays (const string & couleur_joueur) const;

		/**
		* @brief Accesseur pour tab_region
		* @return Reference sur tab_region pour le manipuler directement
		*/
		vector<Region*> & getTabRegions ();

		/**
		* @brief Mutateur pout tab_region
		* @param tabRegion : tableau de Region
		*/
		void setTabRegions (const vector<Region*> & tabRegion);
};

#endif
