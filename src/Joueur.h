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
	
};

#endif
