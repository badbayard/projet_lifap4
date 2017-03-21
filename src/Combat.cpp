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
				attaquant = att;
	}
	
	Joueur Combat::get_defenseur() const{
		return defenseur;
	}

	void Combat::set_defenseur(Joueur def){
		defenseur = def;
	}

	Region Combat::get_region_attaquant() const{
		return region_attaquant;
	}

	void Combat::set_region_attaquant(Region region_a){
		region_attaquant = region_a;
	}
	
	Region Combat::get_region_defenseur() const{
		return region_defenseur;
	}

	void Combat::set_region_defenseur(Region region_d){
		region_defenseur = region_d;
	}
	
	int unDe6(){
		return rand()%6;
	}
	
	bool Combat::bataille(unsigned int nb_troupes_attaquant, unsigned int nb_troupes_defenseur){
		int res_attaquant = 0, res_defenseur = 0;
		
		for(unsigned int i = 0; i < nb_troupes_attaquant; i++)
			res_attaquant += unDe6();
		for(unsigned int i = 0; i < nb_troupes_defenseur; i++)
			res_defenseur += unDe6();
			
		if(res_attaquant > res_defenseur)
			return true;
		else
			return false;
	}
	
	
	void Combat::maj_troupes(Region& region_attaquant, Region& region_defenseur){
		int a, d, unite_att = region_attaquant.getNbUnite(), unite_def = region_defenseur.getNbUnite();
		string c_att = attaquant.getCouleurJoueur();
		string c_def = defenseur.getCouleurJoueur();
		
		do{
		cout << "Joueur " << c_att << " choisit un nombre d'unites pour l'offensive : ";
		cin >> a;}
		while((a<0 || a>3) && a<unite_att);
		cout <<endl;
		do{
		cout << "Joueur " << c_def << " choisit un nombre d'unites pour la defense : ";
		cin >> d;}
		while((d<0 || d>2) && d<unite_def);
	
		if( !bataille(a,d) ){	// Si le defenseur gagne
			region_attaquant.setNbUnite(unite_att - a +1);
		}
		else {
			region_defenseur.setNbUnite(unite_def - d);
			int limite = region_defenseur.getNbUnite();
			if(limite <= 0){
				cout << "Joueur " << c_att << " choisit un nombre d'unites a transfere dans la region conquise : ";
				cin >> a;
				region_defenseur.setNbUnite(a);
				region_defenseur.setCouleurRegion(c_att);
			}
			
		}
	}
