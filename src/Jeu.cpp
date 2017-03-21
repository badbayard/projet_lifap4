#include "Jeu.h"

#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <fstream>
#include <cassert>
#include <vector>

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

bool Jeu::saisie(unsigned int nb_Joueur)
{
	/*	unsigned int a,i;
		int tabou[nb_Joueur];
	for(i = 0; i <nb_Joueur; i++){
		tabou[i] = 0;}

 // initialiser un joueur pour la couleur
 
for(i =0; i<nb_Joueur;i++)
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
		if(estValide(a,tabou,nb_Joueur) == 1 )
		{
			cout <<"problème dans la saisie"<<endl;
			return false;
		}
	}
 	while( ((a<1)||(a>5)) && !(estValide(a,tabou,nb_Joueur)) );

	 	switch(a)
	 	{
			 case 1: J1.setCouleurJoueur("Rouge");
							// tab[i]=1;
			 break;
			 case 2: J1.setCouleurJoueur("Bleu");
							// tab[i]=2;
			 break;
			 case 3: J1.setCouleurJoueur("Vert");
							// tab[i]=3;
			 break;
			 case 4: J1.setCouleurJoueur("Orange");
							// tab[i]=4;
			 break;
			 case 5: J1.setCouleurJoueur("Blanc");
							// tab[i]=5;
			 break;

			 default:cout <<"Problème"<<endl;
			 break;
		 }
	
	tabou[i] = a;
	cout << endl;
	return true;*/
	return 0;
}




void Jeu::lancerjeu()
{
  unsigned int i;
	cout <<"mettre le nombre de joueur "<<endl;
	cin >> nb_joueur;

	for(i=0;i<nb_joueur;i++)
	{
		tab_joueur.push_back(Joueur());
		cout <<"mettre votre nom"<<endl;
	//	tab_joueur[i].setnomJoueur();
	}
}


	/*
	b=saisie(nb_joueur,j1);
   while (b==false)
	{
		cout <<"recommencer la saisie "<<endl;
		b=saisie(nb_joueur,j1);
	}*/



