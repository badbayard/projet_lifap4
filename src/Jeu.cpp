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


// Regarde si l'entier a est présent dans le tableau Tabou de taille NbJoueur
bool estValide(int a, int tabou[], int nbJoueur){
	for(int i = 0; i < nbJoueur; i++)
			if( tabou[i] == a)
				return true;
	return false;
}

void Jeu::lancerjeu()
{

	int a;
	Joueur j1;
	unsigned int i;
	cout <<"mettre le nombre de joueur "<<endl;
	cin >> nb_joueur;
	// int tab[nb_joueur];
	int tabou[nb_joueur];
	for(i = 0; i <nb_joueur; i++){
		tabou[i] = 0;}

 // initialiser un joueur pour la couleur
 
for(i =0; i<nb_joueur;i++)
{
	 cout <<"couleur du joueur " <<endl;
 	do
 	{
		cout <<"Rouge 1"<<endl;
	 	cout <<"Bleu 2"<<endl;
	 	cout <<"Vert 3"<<endl;
		cout <<"Orange 4"<<endl;
		cout <<"Blanc 5"<<endl;
	 	cin >> a;
	}
 	while( ((a<1)||(a>5)) && !(estValide(a,tabou,nb_joueur)) );

	if(estValide(a,tabou,nb_joueur) == 1 )
	{
		cout <<"problème dans la saisie"<<endl;
	}


	 	switch(a)
	 	{
			 case 1: j1.setCouleurJoueur("Rouge");
							// tab[i]=1;
			 break;
			 case 2: j1.setCouleurJoueur("Bleu");
							// tab[i]=2;
			 break;
			 case 3: j1.setCouleurJoueur("Vert");
							// tab[i]=3;
			 break;
			 case 4: j1.setCouleurJoueur("Orange");
							// tab[i]=4;
			 break;
			 case 5: j1.setCouleurJoueur("Blanc");
							// tab[i]=5;
			 break;

			 default:cout <<"Problème"<<endl;
			 break;
		 }
	
tabou[i] = a;
cout << endl;
}
}
