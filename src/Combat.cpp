#include "Combat.h"

#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <fstream>
#include <cassert>

using namespace std;

	Combat::Combat(){
		
	}
	
	Combat::Combat(Joueur joueur_a, Joueur joueur_d, Region region_a, Region region_d){
		attaquant = joueur_a;
		defenseur = joueur_d;
		region_attaquant = region_a;
		region_defenseur = region_d;
	}
		
	Combat::~Combat(){
	
	}
	
	Joueur Combat::get_attaquant() const{
		return attaquant;
	}
	
	void Combat::set_attaquant(Joueur att){
				
	}
	
	Joueur Combat::get_defenseur() const{
		return defenseur;
	}

	void Combat::set_defenseur(Joueur def);

	Region Combat::get_region_attaquant() const{
		return region_attaquant;
	}

	void Combat::set_region_attaquant(Region region_a);
	
	Region Combat::get_region_defenseur() const{
		return region_defenseur;
	}

	void Combat::set_region_defenseur(Region region_d);
	
	Joueur Combat::bataille(unsigned int nb_troupes_attaquant, unsigned int nb_troupes_defenseur);
	
	void Combat::maj_troupes(Region& region_attaquant, Region& region_defenseur);
