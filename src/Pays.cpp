#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <fstream>
#include <cassert>
#include <vector>

#include "Pays.h"

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

Pays::~Pays()
{
	for (unsigned int i = 0; i < tab_region.size(); i++) {
		delete tab_region[i];
	}
}




string Pays::getNomPays () const
{
	return nom_pays;
}

void Pays::setNomPays (const string & nom)
{
	nom_pays = nom;
}



vector<Region*> & Pays::getTabRegions ()
{
	return tab_region;
}

void Pays::setTabRegions (const vector<Region*> & tabRegion)
{
	tab_region = tabRegion;
}



unsigned int Pays::getNbRegions () const
{
	return nb_regions;
}

void Pays::setNbRegions (unsigned int nbregions)
{
	nb_regions = nbregions;
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



void Pays::ajouterRegion (const Region & reg)
{
	tab_region.push_back( (Region*) &reg );
}



void Pays::testRegressionPays()
{
	//test des get et du constructeur
	Pays();
	assert(getNbRegions()==0);
	assert(getNomPays()=="");
	
	Pays("essai",5);
	assert(getNbRegions()==5);
	assert(getNomPays()=="essai");
	
}