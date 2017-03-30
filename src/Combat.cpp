#include "Combat.h"
#include "Joueur.h"
#include "Region.h"

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
	
	int unDe(int nombre){
		return rand()%nombre +1;
	}
	
	bool Combat::bataille(unsigned int nb_troupes_attaquant, unsigned int nb_troupes_defenseur){
		int res_attaquant = 0, res_defenseur = 0;
		
		for(unsigned int i = 0; i < nb_troupes_attaquant; i++)
			res_attaquant += unDe(6);
		for(unsigned int i = 0; i < nb_troupes_defenseur; i++)
			res_defenseur += unDe(6);
			
		cout << "L'attaquant a fait un jet à " << res_attaquant <<endl;
		cout << "Le défenseur a fait un jet à " << res_defenseur <<endl;
		
		if(res_attaquant > res_defenseur)
			return true;
		else
			return false;
	}

	
	void Combat::maj_troupes(Region& region_attaquant, Region& region_defenseur, Joueur& jatt, Joueur& jdef){
		int a, d, unite_att = region_attaquant.getNbUnite(), unite_def = region_defenseur.getNbUnite();
		string c_att = attaquant.getCouleurJoueur();
		string c_def = jdef.getCouleurJoueur();
		
		do{
		cout << "Joueur " << c_att << ", choisis un nombre d'unites pour l'offensive (entre 0 et " << (unite_att>3? 3:unite_att) << ") : ";
		cin >> a;}
		while((a<0) || (a>3) || (a>unite_att)); 
		cout <<endl;
		do{
		cout << "Joueur " << c_def << ", choisis un nombre d'unites pour la defense (entre 0 et " << (unite_def>2? 2:unite_def) << ") : ";
		cin >> d;}
		while((d<0) || (d>2) || (d>unite_def));
	
		if( !bataille(a,d) ){		// Si le defenseur gagne
			cout << " Le défenseur l'emporte !" << endl <<endl;		
			region_attaquant.setNbUnite(unite_att - a +1);
		}
		else {						// Si l'attaquant gagne
			cout << "Victoire !" <<endl<<endl;				
			region_defenseur.setNbUnite(unite_def - d);
			unsigned int limite = region_defenseur.getNbUnite();
			if(limite <= 0){
				do{
					cout << "Joueur " << c_att << ", choisis un nombre d'unites a transfere dans la region conquise (entre 1 et " << unite_att-1 << ") : ";
					cin >> a;}
				while(a < 1 || a >= unite_att);
				
				region_defenseur.setNbUnite(a);
				region_defenseur.setCouleurRegion(c_att);
				jatt.setNbRegions(jatt.getNbRegions()+1);
				jdef.setNbRegions(jdef.getNbRegions()-1);
				
			}
		}
	}
