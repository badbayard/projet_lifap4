#include "Combat.h"
#include "Joueur.h"
#include "Pays.h"
#include "Region.h"
#include "Terrain.h"
#include "Jeu.h"

#include <iostream>

using namespace std;

int main ()
{
	//test du module joueur et terrain
	string essai1;
	string essai2;
	unsigned int a , b, c, d;
	Terrain (8,8);
	
	//test du module joueur
	Joueur j1;
	j1.setCouleurJoueur("Rouge");
	j1.setNbRegions(12);
	j1.setNbRegiments(25);
	essai1=j1.getCouleurJoueur();
	a= j1.getNbRegions();
	b= j1.getNbRegiments();
	j1.setCouleurJoueur("Bleu");
	j1.setNbRegions(15);
	j1.setNbRegiments(22);
	essai2=j1.getCouleurJoueur();
	c=j1.getNbRegions();
	d=j1.getNbRegiments();
	cout <<"couleur avant "<< essai1 <<endl;
	cout <<"nombre de regions avant " <<a <<endl;
	cout <<"nombre de troupe avant " << b <<endl;
	cout <<"couleur apres " <<essai2 <<endl;
	cout <<"nombre de regions apres " <<c <<endl;
	cout <<" nombre de troupe apres " << d <<endl;

	//test du module jeu
	Jeu j;
	j.lancerjeu();
	return 0;
}
