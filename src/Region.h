#ifndef REGION_H
#define REGION_H

#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <fstream>
#include <cassert>
#include <vector>

using namespace std;

class Region {

	private :
		string couleur_joueur;
		unsigned int nb_unites;
		vector<Region*> frontaliers;
		string nom_region;

	public :
		/** @brief Constructeur par défaut */
		Region();
		Region(const string & nom, unsigned int nb_unite = 1, const string & couleur_region = "");

		/** @brief Destructeur */
		~Region(){
		}

		/**
		* @brief Accesseur pour nb_unites
		* @return Le nombre d'unites presentes dans la region
		*/
		unsigned int getNbUnite () const;

		/**
		* @brief Mutateur pour nb_unites
		* @param nb_unite : entier
		*/
		void setNbUnite (const unsigned int & nb_unite);

		/**
		* @brief Accesseur pour couleur_joueur
		* @return La couleur du joueur possedant la region
		*/
		string getCouleurRegion () const;

		/**
		* @brief Mutateur pour couleur_joueur
		* @param couleur_region: string
		*/
		void setCouleurRegion (const string & couleur_region);

		/**
		* @brief Accesseur pour nom_region
		* @return Le nom de la region
		*/
		string getNomRegion () const;

		void setNomRegion (const string & nom);

		// vector<Region*> & getTabFrontaliers ();

		void setTabFrontaliers (const vector<Region*> & tab_frontalier);

		/**
		* @brief Teste si une region donnee est voisine de l'instance consideree
		* @param voisin : Region
		* @return Booleen
		*/
		bool estFrontalier (const Region & voisin) const;
		
		void ajouterFrontalier (const Region & voisin);

		/** @brief test de regression pou la class region */
		void testRegressionRegion();
};

#endif
