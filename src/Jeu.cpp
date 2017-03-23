#include "Jeu.h"
#include "Combat.h"

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


void Jeu::lancerjeu()
{
  unsigned int i,a;
	string nom;
	cout <<"mettre le nombre de joueur "<<endl;
	cin >> nb_joueur;
	int tabou[nb_joueur];

	for(i=0;i<nb_joueur;i++)
	{
		//traitement pour crée les joueurs avec leur noms et leur couleur
		tab_joueur.push_back(Joueur());
		cout <<"mettre votre nom"<<endl;
		cin>>nom;
		tab_joueur[i].setnom_joueur(nom);
		cout <<"Mettre la couleur du joueur "<<endl;

			do
 		{
			cout <<"Rouge 1"<<endl;
	 		cout <<"Bleu 2"<<endl;
	 		cout <<"Vert 3"<<endl;
			cout <<"Orange 4"<<endl;
			cout <<"Blanc 5"<<endl;
	 		cin >> a;
			if(estValide(a,tabou,nb_joueur) == 1 )
			{
				cout <<"problème dans la saisie"<<endl;
			}
		}		
 		while( ((a<1)||(a>5)) && !(estValide(a,tabou,nb_joueur)) );

	 	switch(a)
	 	{
			 case 1: tab_joueur[i].setCouleurJoueur("Rouge");
							// tab[i]=1;
			 break;
			 case 2: tab_joueur[i].setCouleurJoueur("Bleu");
							// tab[i]=2;
			 break;
			 case 3: tab_joueur[i].setCouleurJoueur("Vert");
							// tab[i]=3;
			 break;
			 case 4: tab_joueur[i].setCouleurJoueur("Orange");
							// tab[i]=4;
			 break;
			 case 5: tab_joueur[i].setCouleurJoueur("Blanc");
							// tab[i]=5;
			 break;

			 default:cout <<"Problème"<<endl;
			 break;
		 }
	
	tabou[i] = a;
	cout << endl;
  //traitement du nombre de troupes et du nombre de regioni (42 regions)
	tab_joueur[i].setNbRegiments(40);
	
	switch(nb_joueur)
	{
		case 2:tab_joueur[i].setNbRegions(21);
		break;
		case 3:tab_joueur[i].setNbRegions(14);
		break;
		case 4:tab_joueur[i].setNbRegions(10);
		break;
		case 5:tab_joueur[i].setNbRegions(8);
		break;
		default : cout <<"pas de joueur"<<endl;
		break;
	}
	cout <<" le joueur "<<tab_joueur[i].getnom_joueur()<<"  dispose de : " <<tab_joueur[i].getNbRegiments() <<"   troupes "<<endl;
	cout <<"le joueur  " <<tab_joueur[i].getnom_joueur()<<" dispose de : " <<tab_joueur[i].getNbRegions() <<"   regions " <<endl;

	//manque la répartition aléatoire des territoires sur la carte

	}

//traitement pour le terrain
 
 switch(nb_joueur)
 {
	 case 2: Terrain(30,30);
	 break;
	 case 3: Terrain(40,40);
	 break;
	 case 4: Terrain(50,50);
	 break;
	 case 5: Terrain(60,60);
	 break;
	 default: Terrain(20,20);
						cout <<"Pas de joueur"<<endl;
	 break;
 }


}


bool Jeu::finPartie()
{
	unsigned int i;

	for(i=0;i<nb_joueur;i++)
	{
		if(tab_joueur[i].getNbRegions() == 42)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}


void Jeu::afficherAide()
{
	int a;
	cout <<"Aide du jeu"<<endl;
	
	do
	{
		cout <<"Les phases de jeu : 1 " <<endl;
		cout <<"Les renforts : 2 " <<endl;
		cout <<"Les combats : 3 " <<endl;
		cout <<"Les manoeuvres : 4"<<endl;
		cout <<"Les conditions de victoire : 5 " <<endl;
		cin >> a;
	}
	while((a<1)||(a>4));

	switch(a)
	{
		case 1 : cout <<" Un joueur peut proceder à 3 actions distinctes dans l'ordre suivant"<<endl;
						 cout <<"1-Phase de renforts "<<endl;
						 cout <<"2-Phase de combats " <<endl;
						 cout <<"3-Phase de manoeuvre " <<endl;
		break;

		case 2 : cout <<"La phase de renforts permet d'avoir des renforts en fonction du nombre de regions controles et de pays controleren entier " <<endl;
		break;

		case 3 : cout <<"La phase de combats permet d'engager le combat contre un autre joueur qui se situe a votre frontiere " <<endl;
		break;

		case 4 : cout <<"la phase de manoeuvre permet de faire un déplacement de troupe d'une regions a une autre regions frontaliere" <<endl; 
		break;

		case 5 : cout <<"Les conditions de victoire sont le contrôle totale de la map"<<endl;
		break;

		default : exit(1);
		break;
	}
}


void Jeu::phaseRenfort()
{
	unsigned int i,total_renfort,troupe_avant;
	//unsigned int bonus_pays;

	for(i=0;i<nb_joueur;i++)
	{
		total_renfort=(tab_joueur[i].getNbRegiments()/3)+3;
		troupe_avant = tab_joueur[i].getNbRegiments();
		//rajouter les renforts en fonction du pays
		total_renfort += troupe_avant;
    tab_joueur[i].setNbRegiments(total_renfort);		
	}
}

void Jeu::phaseAttaque()
{
	string region_depart,region_selectionner;
	int a ;
	cout<<" Voulez-vous attaquer une region ? " <<endl;
	do
	{
		cout <<"oui : 1"<<endl;
		cout <<"non : 2" <<endl;
		cin >> a ;
	}while((a<1)||(a>2));

	switch(a)
	{
	
	case 1:  Combat bataille;
	       	 cout <<"Entrer le nom de la regions a selectionner "<<endl;
					 cin >> region_depart;
	         cout <<"Entrer le nom de la regions a attaque "<<endl;
	         cin >> region_selectionner;

			/*	if(estFrontalier()==true)
				{
					 bataille.set_region_attaquant(region_depart);
					 bataille.set_region_defenseur(region_selectionner);
					 bataille.maj_troupes(bataille.get_region_attaquant(),bataille.get_region_defenseur());
				}*/
	break;
//	default: cout<<"rien"<<endl;
//	break;
	}
					 

}
		




