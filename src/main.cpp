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
	unsigned int a;

	//test du module jeu
	Jeu j;
	cout << "A vos Risk et perils !" << endl << "-----------------------------" << endl;
	do
	{
		cout << "Aide jeu	1" << endl;
		cout << "Lancer jeu	2" << endl;
		cout << "Quitter		3" << endl;
		cin >> a;
	} while (a < 1 || a > 3);
	switch (a)
	{
		case 1:
			j.afficherAide();
			break;
		
		case 2:
			j.lancerJeu();
			break;
		
		case 3:
			exit(1);
	}
	return 0;
}