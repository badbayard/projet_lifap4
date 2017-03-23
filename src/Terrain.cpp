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
	unsigned int i, j;

	for(i=0;i<=dim_x;i++)
	{
		for(j=0;j<=dim_y;j++)
		{
			cout << "*";
		}
		cout << endl;
	}

//terrain 
 const char carte[18][80]={ " *******************   *********  *********************************          ",
	                        " ******************     ******     **    **************************          ",
							"  ***************        * *      **    ***************************          ",
							"   ***************           *   **     ****************************         ",
							"     ************           **        ******************************         ",
							"       *********  **         ********************************************    ",
							"	       *****           *************************************************  ",
							"          ***           **************************************************   ",
							"           *                     ***    ***********************************  ",
							"          *****                   **	   ********************************** ",
							"         *******                   *     *********************************** ",
							"        *********                         ********************************** ",
							"        **********        ***************************************************",
							"        **********     *******************            *******          ****  ",
							"        *********     ********************             ******            **  ",
							"         ********      *****************               ******            **  ",
							"         *******         **************                 ****             **  ",
							"           ****            ***********                   **               *  ",
 };

 for (i=0;i<18;i++)
		{
			for(j=0;j<80;j++)
			{
			cout<<carte[i][j];
		  }
			cout <<endl;
		}	
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
	// Amerique du Nord
	Pays north_america("Amerique du Nord",9);
	Region alaska("Alaska");
	Region alberta("Alberta");
	Region central_america("Amerique centrale");
	Region eastern_us("Etats de l'Est");
	Region greenland("Groenland");
	Region northwest_territory("Territoires du Nord-Ouest");
	Region ontario("Ontario");
	Region quebec("Quebec");
	Region western_us("Etats de l'Ouest");
	north_america.ajouterRegion(alaska);
	north_america.ajouterRegion(alberta);
	north_america.ajouterRegion(central_america);
	north_america.ajouterRegion(eastern_us);
	north_america.ajouterRegion(greenland);
	north_america.ajouterRegion(northwest_territory);
	north_america.ajouterRegion(ontario);
	north_america.ajouterRegion(quebec);
	north_america.ajouterRegion(western_us);
	
	// Asie
	Pays asia("Asie",12);
	Region afghanistan("Afghanistan");
	Region china("Chine");
	Region india("Inde");
	Region irkutsk("Tchita");
	Region japan("Japon");
	Region kamchatka("Kamtchatka");
	Region middle_east("Moyen-Orient");
	Region mongolia("Mongolie");
	Region siam("Siam");
	Region siberia("Siberie");
	Region ural("Oural");
	Region yakutsk("Yakoutie");
	asia.ajouterRegion(afghanistan);
	asia.ajouterRegion(china);
	asia.ajouterRegion(india);
	asia.ajouterRegion(irkutsk);
	asia.ajouterRegion(japan);
	asia.ajouterRegion(kamchatka);
	asia.ajouterRegion(middle_east);
	asia.ajouterRegion(mongolia);
	asia.ajouterRegion(siam);
	asia.ajouterRegion(siberia);
	asia.ajouterRegion(ural);
	asia.ajouterRegion(yakutsk);

	// Amerique du Sud
	Pays south_america("Amerique du Sud",4);
	Region argentina("Argentine");
	Region brazil("Bresil");
	Region peru("Perou");
	Region venezuela("Venezuela");
	south_america.ajouterRegion(argentina);
	south_america.ajouterRegion(brazil);
	south_america.ajouterRegion(peru);
	south_america.ajouterRegion(venezuela);

	// Europe
	Pays europe("Europe",7);
	Region great_britain("Grande-Bretagne");
	Region iceland("Islande");
	Region northern_eu("Europe du Nord");
	Region scandinavia("Scandinavie");
	Region southern_eu("Europe du Sud");
	Region ukraine("Ukraine");
	Region western_eu("Europe occidentale");
	europe.ajouterRegion(great_britain);
	europe.ajouterRegion(iceland);
	europe.ajouterRegion(northern_eu);
	europe.ajouterRegion(scandinavia);
	europe.ajouterRegion(southern_eu);
	europe.ajouterRegion(ukraine);
	europe.ajouterRegion(western_eu);
	
	// Afrique
	Pays africa("Afrique",6);
	Region congo("Congo");
	Region east_africa("Afrique de l'Est");
	Region egypt("Egypte");
	Region madagascar("Madagascar");
	Region north_africa("Afrique du Nord");
	Region south_africa("Afrique du Sud");
	africa.ajouterRegion(congo);
	africa.ajouterRegion(east_africa);
	africa.ajouterRegion(egypt);
	africa.ajouterRegion(madagascar);
	africa.ajouterRegion(north_africa);
	africa.ajouterRegion(south_africa);
	
	// Oceanie
	Pays australia("Oceanie",4);
	Region eastern_au("Australie Orientale");
	Region indonesia("Indonesie");
	Region new_guinea("Nouvelle-Guinee");
	Region western_au("Australie Occidentale");
	australia.ajouterRegion(eastern_au);
	australia.ajouterRegion(indonesia);
	australia.ajouterRegion(new_guinea);
	australia.ajouterRegion(western_au);
	
	
	
	
	// Frontieres Amerique du Nord
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
	
	// Frontieres Asie
	afghanistan.ajouterFrontalier(india);
	afghanistan.ajouterFrontalier(middle_east);
	afghanistan.ajouterFrontalier(ural);
	afghanistan.ajouterFrontalier(china);
	afghanistan.ajouterFrontalier(ukraine);
	china.ajouterFrontalier(afghanistan);
	china.ajouterFrontalier(india);
	china.ajouterFrontalier(mongolia);
	china.ajouterFrontalier(siam);
	china.ajouterFrontalier(siberia);
	china.ajouterFrontalier(ural);
	india.ajouterFrontalier(afghanistan);
	india.ajouterFrontalier(china);
	india.ajouterFrontalier(middle_east);
	india.ajouterFrontalier(siam);
	irkutsk.ajouterFrontalier(kamchatka);
	irkutsk.ajouterFrontalier(mongolia);
	irkutsk.ajouterFrontalier(siberia);
	irkutsk.ajouterFrontalier(yakutsk);
	japan.ajouterFrontalier(kamchatka);
	japan.ajouterFrontalier(mongolia);
	kamchatka.ajouterFrontalier(alaska);
	kamchatka.ajouterFrontalier(irkutsk);
	kamchatka.ajouterFrontalier(japan);
	kamchatka.ajouterFrontalier(mongolia);
	kamchatka.ajouterFrontalier(yakutsk);
	middle_east.ajouterFrontalier(southern_eu);
	middle_east.ajouterFrontalier(egypt);
	middle_east.ajouterFrontalier(east_africa);
	middle_east.ajouterFrontalier(india);
	middle_east.ajouterFrontalier(afghanistan);
	middle_east.ajouterFrontalier(ukraine);
	mongolia.ajouterFrontalier(china);
	mongolia.ajouterFrontalier(irkutsk);
	mongolia.ajouterFrontalier(japan);
	mongolia.ajouterFrontalier(kamchatka);
	mongolia.ajouterFrontalier(siberia);
	siam.ajouterFrontalier(indonesia);
	siam.ajouterFrontalier(china);
	siam.ajouterFrontalier(india);
	siberia.ajouterFrontalier(china);
	siberia.ajouterFrontalier(irkutsk);
	siberia.ajouterFrontalier(mongolia);
	siberia.ajouterFrontalier(ural);
	siberia.ajouterFrontalier(yakutsk);
	ural.ajouterFrontalier(ukraine);
	ural.ajouterFrontalier(afghanistan);
	ural.ajouterFrontalier(china);
	ural.ajouterFrontalier(siberia);
	yakutsk.ajouterFrontalier(irkutsk);
	yakutsk.ajouterFrontalier(kamchatka);
	yakutsk.ajouterFrontalier(siberia);
	
	// Frontieres Europe
	great_britain.ajouterFrontalier(iceland);
	great_britain.ajouterFrontalier(northern_eu);
	great_britain.ajouterFrontalier(scandinavia);
	great_britain.ajouterFrontalier(western_eu);
	iceland.ajouterFrontalier(great_britain);
	iceland.ajouterFrontalier(scandinavia);
	iceland.ajouterFrontalier(greenland);
	northern_eu.ajouterFrontalier(scandinavia);
	northern_eu.ajouterFrontalier(great_britain);
	northern_eu.ajouterFrontalier(western_eu);
	northern_eu.ajouterFrontalier(southern_eu);
	northern_eu.ajouterFrontalier(ukraine);
	scandinavia.ajouterFrontalier(great_britain);
	scandinavia.ajouterFrontalier(iceland);
	scandinavia.ajouterFrontalier(northern_eu);
	scandinavia.ajouterFrontalier(ukraine);
	southern_eu.ajouterFrontalier(egypt);
	southern_eu.ajouterFrontalier(north_africa);
	southern_eu.ajouterFrontalier(middle_east);
	southern_eu.ajouterFrontalier(northern_eu);
	southern_eu.ajouterFrontalier(ukraine);
	southern_eu.ajouterFrontalier(western_eu);
	ukraine.ajouterFrontalier(afghanistan);
	ukraine.ajouterFrontalier(middle_east);
	ukraine.ajouterFrontalier(ural);
	ukraine.ajouterFrontalier(northern_eu);
	ukraine.ajouterFrontalier(scandinavia);
	ukraine.ajouterFrontalier(southern_eu);
	western_eu.ajouterFrontalier(north_africa);
	western_eu.ajouterFrontalier(great_britain);
	western_eu.ajouterFrontalier(northern_eu);
	western_eu.ajouterFrontalier(southern_eu);
	
	// Frontieres Amerique du Sud
	argentina.ajouterFrontalier(brazil);
	argentina.ajouterFrontalier(peru);
	brazil.ajouterFrontalier(argentina);
	brazil.ajouterFrontalier(peru);
	brazil.ajouterFrontalier(venezuela);
	brazil.ajouterFrontalier(north_africa);
	peru.ajouterFrontalier(argentina);
	peru.ajouterFrontalier(brazil);
	peru.ajouterFrontalier(venezuela);
	venezuela.ajouterFrontalier(brazil);
	venezuela.ajouterFrontalier(peru);
	venezuela.ajouterFrontalier(central_america);
	
	// Frontieres Afrique
	congo.ajouterFrontalier(east_africa);
	congo.ajouterFrontalier(north_africa);
	congo.ajouterFrontalier(south_africa);
	east_africa.ajouterFrontalier(middle_east);
	east_africa.ajouterFrontalier(congo);
	east_africa.ajouterFrontalier(egypt);
	east_africa.ajouterFrontalier(madagascar);
	east_africa.ajouterFrontalier(south_africa);
	east_africa.ajouterFrontalier(north_africa);
	egypt.ajouterFrontalier(middle_east);
	egypt.ajouterFrontalier(southern_eu);
	egypt.ajouterFrontalier(north_africa);
	egypt.ajouterFrontalier(east_africa);
	madagascar.ajouterFrontalier(east_africa);
	madagascar.ajouterFrontalier(south_africa);
	north_africa.ajouterFrontalier(egypt);
	north_africa.ajouterFrontalier(east_africa);
	north_africa.ajouterFrontalier(congo);
	north_africa.ajouterFrontalier(brazil);
	north_africa.ajouterFrontalier(southern_eu);
	north_africa.ajouterFrontalier(western_eu);
	south_africa.ajouterFrontalier(congo);
	south_africa.ajouterFrontalier(east_africa);
	south_africa.ajouterFrontalier(madagascar);

	//Frontieres Australia
	eastern_au.ajouterFrontalier(indonesia);
	eastern_au.ajouterFrontalier(western_au);
	indonesia.ajouterFrontalier(eastern_au);
	indonesia.ajouterFrontalier(siam);
	indonesia.ajouterFrontalier(western_au);
	new_guinea.ajouterFrontalier(western_au);
	new_guinea.ajouterFrontalier(eastern_au);
	new_guinea.ajouterFrontalier(indonesia);
}

void Terrain::ajouterPays (const Pays & pays)
{
	tab_pays.push_back( (Pays*) &pays );
}
