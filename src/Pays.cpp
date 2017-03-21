#include "Pays.h"

#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <fstream>
#include <cassert>
#include <vector>

using namespace std;

Pays::Pays()
{
	nb_regions = 0;
	nom_pays = "";
}

Pays::Pays(const string & nom, unsigned int nbregions)
{
	assert(nbregions >= 0);
	nb_regions = nbregions;
	nom_pays = nom;
}

unsigned int Pays::getNbRegions () const
{
	return nb_regions;
}

bool Pays::controlePays (const string & couleur_joueur) const
{
	for (unsigned int i = 0; i < getNbRegions(); i++)
	{
		if (!(tab_region[i]->getCouleurRegion() == couleur_joueur))
		{
			return false;
		}
	}
	return true;
}

vector<Region*> & Pays::getTabRegions ()
{
	return tab_region;
}

void Pays::setTabRegions (const vector<Region*> & tabRegion)
{
	tab_region = tabRegion;
}

void Pays::ajouterRegion (const Region & reg)
{
	tab_region.push_back( (Region*) &reg );
}
