#include "Jeu.h"

#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <fstream>
#include <cassert>

using namespace std;


Jeu::Jeu()
{
	nb_joueur=0;
	terrain = NULL;
}

void Jeu::lancerjeu()
{

	int a;
	Joueur j1;
	cout <<"mettre le nombre de joueur "<<endl;
	cin >> nb_joueur;
	
 // initialiser un joueur pour la couleur
 cout <<"couleur du joueur " <<endl;
 do
 {
	 cout <<"Rouge 1"<<endl;
	 cout <<"Bleu 2"<<endl;
	 cout <<"Vert 3"<<endl;
	 cin >> a;

	 switch(a)
	 {
		 case 1: j1.setCouleurJoueur("Rouge");
		 break;
		 case 2: j1.setCouleurJoueur("Bleu");
		 break;
		 case 3: j1.setCouleurJoueur("Vert");
		 break;
		 default:cout <<"Probléme";
		 break;
	 }
 }
 while((a<=1)&&(a>=3));
}

