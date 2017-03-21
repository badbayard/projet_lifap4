#include "Terrain.h"
#include "Joueur.h"
#include "Pays.h"
#include "Region.h"

#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <fstream>
#include <cassert>
#include <vector>

using namespace std;

Terrain::Terrain()
{
	dim_x = 0;
 	dim_y = 0;
}

Terrain::Terrain(unsigned int dimensionX, unsigned int dimensionY)
{
	assert(dimensionX >= 0);
	assert(dimensionY >= 0);
	dim_x = dimensionX;
 	dim_y = dimensionY;
//	unsigned int i, j;
/*
	for(i=0;i<=dim_x;i++)
	{
		for(j=0;j<=dim_y;j++)
		{
			cout << "*";
		}
		cout << endl;
	}
*/
}

Terrain::~Terrain()
{
	dim_x= 0;
	dim_y= 0;
}

unsigned int Terrain::getdim_x() const
{
	return dim_x;
}

void Terrain::setdim_x(unsigned int dimensionX)
{
	assert(dimensionX >= 0);
	dim_x = dimensionX;
}

unsigned int Terrain::getdim_y() const
{
	return dim_y;
}

void Terrain::setdim_y(unsigned int dimensionY)
{
	assert(dimensionY >= 0);
	dim_y = dimensionY;
}

void Terrain::initTerrain ()
{
	Pays north_america(string("Amerique du Nord"),9);
	Region alaska(string("Alaska"));
	Region alberta(string("Alberta"));
	Region central_america(string("Amerique centrale"));
	Region eastern_us(string("Etats de l'Est"));
	Region greenland(string("Groenland"));
	Region northwest_territory(string("Territoires du Nord-Ouest"));
	Region ontario(string("Ontario"));
	Region quebec(string("Quebec"));
	Region western_us(string("Etats de l'Ouest"));
	
	Pays asia(string("Asie"),12);
	Region kamchatka(string("Kamtchatka"));
	
	Pays south_america(string("Amerique du Sud"),4);
	Region venezuela(string("Venezuela"));

	Pays europe(string("Europe"),7);
	Region iceland(string("Islande"));
	
	alaska.ajouterFrontalier(northwest_territory);
	alaska.ajouterFrontalier(kamchatka);
	alberta.ajouterFrontalier(northwest_territory);
	alberta.ajouterFrontalier(ontario);
	alberta.ajouterFrontalier(western_us);
	central_america.ajouterFrontalier(western_us);
	central_america.ajouterFrontalier(eastern_us);
	central_america.ajouterFrontalier(venezuela);
	eastern_us.ajouterFrontalier(central_america);
	eastern_us.ajouterFrontalier(western_us);
	eastern_us.ajouterFrontalier(ontario);
	eastern_us.ajouterFrontalier(quebec);
	greenland.ajouterFrontalier(northwest_territory);
	greenland.ajouterFrontalier(ontario);
	greenland.ajouterFrontalier(quebec);
	greenland.ajouterFrontalier(iceland);
	northwest_territory.ajouterFrontalier(alaska);
	northwest_territory.ajouterFrontalier(alberta);
	northwest_territory.ajouterFrontalier(ontario);
	northwest_territory.ajouterFrontalier(greenland);
	ontario.ajouterFrontalier(northwest_territory);
	ontario.ajouterFrontalier(alberta);
	ontario.ajouterFrontalier(western_us);
	ontario.ajouterFrontalier(eastern_us);
	ontario.ajouterFrontalier(quebec);
	ontario.ajouterFrontalier(greenland);
	quebec.ajouterFrontalier(ontario);
	quebec.ajouterFrontalier(eastern_us);
	quebec.ajouterFrontalier(greenland);
	western_us.ajouterFrontalier(alberta);
	western_us.ajouterFrontalier(ontario);
	western_us.ajouterFrontalier(eastern_us);
	western_us.ajouterFrontalier(central_america);
	
	north_america.ajouterRegion(alaska);
	north_america.ajouterRegion(alberta);
	north_america.ajouterRegion(central_america);
	north_america.ajouterRegion(eastern_us);
	north_america.ajouterRegion(greenland);
	north_america.ajouterRegion(northwest_territory);
	north_america.ajouterRegion(ontario);
	north_america.ajouterRegion(quebec);
	north_america.ajouterRegion(western_us);
}

void Terrain::ajouterPays (const Pays & pays)
{
	tab_pays.push_back( (Pays*) &pays );
}
