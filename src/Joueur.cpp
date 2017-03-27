#include "Joueur.h"

#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <fstream>
#include <cassert>
#include <vector>

using namespace std;

string Joueur::getCouleurJoueur() const
{
	return couleur;
}

void Joueur::setCouleurJoueur(string couleur_joueur)
{
	couleur = couleur_joueur;
}

unsigned int Joueur::getNbRegions()const
{
	return nb_regions;
}

void Joueur::setNbRegions(unsigned int nb_Regions)
{
	assert (nb_Regions >= 0);
	nb_regions = nb_Regions;
}

unsigned int Joueur::getNbRegiments() const
{
	return nb_regiments;
}

void Joueur::setNbRegiments (unsigned int nb_Regiments)
{
	assert (nb_Regiments >= 0);
	nb_regiments = nb_Regiments;
}

void Joueur::setnom_joueur(string nom)
{
	nom_joueur=nom;
}

string Joueur::getnom_joueur()
{
	return nom_joueur;
}

void Joueur::testRegressionJoueur()
{
	assert(getCouleurJoueur()=="");
	assert(getNbRegions()== 0);
	assert(getNbRegiments()==0);
	assert(getnom_joueur()=="");

	setCouleurJoueur("Rouge");
	setNbRegions(3);
	setNbRegiments(40);
	setnom_joueur("jessai");

	assert(getCouleurJoueur()=="Rouge");
	assert(getNbRegions()==3);
	assert(getNbRegiments()==40);
	assert(getnom_joueur()=="jessai");

}


