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



