#ifndef REGION_H
#define REGION_H

#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <fstream>
#include <cassert>

using namespace std;

class Region {

	private : 
		string couleur_joueur;
		unsigned int nb_unites;
		//tab de region
		string nom_region;

	public :
		/** @brief Constructeur par défault */
		Region();

};

#endif
