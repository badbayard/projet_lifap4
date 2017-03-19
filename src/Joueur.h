#ifndef JOUEUR_H
#define JOUEUR_H

#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <fstream>
#include <cassert>

#include "Region.h"

using namespace std ;

class Joueur {

	private : 

		string couleur;
		string nom_joueur;
		unsigned int nb_regions;
		unsigned int nb_regiments;
		Region *tab_region ;

	public:
		
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
		unsigned int getNbRegiments ()const;

		/** @brief : modifie le nombre de regiments 
		 * @param : nb_Regiments entier */
		void setNbRegiments (unsigned int nb_Regiments);



	
};

#endif
