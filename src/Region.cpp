#include "Region.h"

#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <fstream>
#include <cassert>
#include <vector>

using namespace std;

Region::Region()
{
	couleur_joueur = "";
	nb_unites = 1;
	nom_region = "";
}

Region::Region(const string & nom, unsigned int nb_unite, const string & couleur_region)
{
	assert(nb_unite >= 0);
	couleur_joueur = couleur_region;
	nb_unites = nb_unite;
	nom_region = nom;
}

unsigned int Region::getNbUnite () const
{
	return nb_unites;
}

void Region::setNbUnite (const unsigned int & nb_unite)
{
	assert(nb_unite >= 0);
	nb_unites = nb_unite;
}

string Region::getCouleurRegion () const
{
	return couleur_joueur;
}

void Region::setCouleurRegion (const string & couleur_region)
{
	couleur_joueur = couleur_region;
}

string Region::getNomRegion () const
{
	return nom_region;
}

void Region::setNomRegion (const string & nom)
{
	nom_region = nom;
}

bool Region::estFrontalier (const Region & voisin) const
{
	for (unsigned int i = 0; i < frontaliers.size(); i++) {
		if (frontaliers[i]->getNomRegion() == voisin.getNomRegion())
		{
			return true;
		}
	}
	return false;
}

void Region::ajouterFrontalier (const Region & voisin)
{
	frontaliers.push_back( (Region*) &voisin );
}
