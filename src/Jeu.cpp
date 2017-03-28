#include "Jeu.h"
#include "Combat.h"

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cstring>
#include <fstream>
#include <cassert>
#include <vector>

using namespace std;


Jeu::Jeu()
{
	nb_joueur=0;
//	terrain = NULL;
}


// Regarde si l'entier a est présent dans le tableau Tabou de taille NbJoueur
bool estValide(int a, int tabou[], int nbJoueur){
	for(int i = 0; i < nbJoueur; i++)
			if( tabou[i] == a)
				return true;
	return false;
}


unsigned int Jeu::getNbJoueur(){
	return nb_joueur;
}
		
void Jeu::setNbJoueur(unsigned int nbj){
	nb_joueur = nbj;
}

vector<Joueur> Jeu::getTabJoueur(){
	return tab_joueur;
}

void Jeu::setTabJoueur( vector<Joueur> tabj){
	tab_joueur = tabj;
}


void Jeu::lancerJeu()
{
	initJeu();
	afficheTerrainTXT();

		// Initialisation des choix de couleurs possibles
	vector<string> liste_couleurs;
	liste_couleurs.push_back("Rouge");
	liste_couleurs.push_back("Bleu");
	liste_couleurs.push_back("Vert");
	liste_couleurs.push_back("Orange");
	liste_couleurs.push_back("Blanc");
	liste_couleurs.push_back("Violet");
	// liste_couleurs = {"Rouge","Bleu","Vert","Orange","Blanc","Violet"};

		// Initialisation des joueurs
	unsigned int n;
	cout << "Mettre le nombre de joueurs : ";
	do
	{
		cin >> n;
		if (n < 2)
		{
			cout << "/!\\ Minimum 2 joueurs : ";
		}
		if (n > 5)
		{
			cout << "/!\\ Maximum 5 joueurs : ";
		}
	} while (n < 2 || n > 5);
	nb_joueur = n;
	cout << endl;

	// Saisie d'un nouveau joueur
	for (unsigned int i = 0; i < nb_joueur; i++)
	{
		string nom;
		unsigned int num_couleur;
		
		cout << "Joueur " << i+1 << ", entrez votre nom : ";
		cin >> nom;
		
		cout << "Choisissez une couleur..." << endl;
		for (unsigned int j = 0; j < liste_couleurs.size(); j++)
		{
			cout << liste_couleurs[j] << "	" << j+1 << endl;
		}
		do
		{
			cin >> num_couleur;
			if (num_couleur < 1 || num_couleur > liste_couleurs.size())
			{
				cout << "/!\\ Donnez une valeur entre 1 et " << liste_couleurs.size() << " : ";
			}
		} while (num_couleur < 1 || num_couleur > liste_couleurs.size());
		num_couleur--;
		
		// Ajout d'un nouveau joueur avec les valeurs saisies
		tab_joueur.push_back( Joueur( nom, liste_couleurs[num_couleur] ) );
		
		// Traitement du nombre de troupes et du nombre de regions (42 regions)
		tab_joueur[i].setNbRegiments(40);
		switch(nb_joueur)
		{
			case 2:
				tab_joueur[i].setNbRegions(21);
				break;
			case 3:
				tab_joueur[i].setNbRegions(14);
				break;
			case 4:
				tab_joueur[i].setNbRegions(10);
				break;
			case 5:
				tab_joueur[i].setNbRegions(8);
				break;
			default: cout << "pas de joueur" << endl;
				break;
		}
		cout << tab_joueur[i].getnom_joueur() << " (Joueur " << i+1 << ") dispose de " << tab_joueur[i].getNbRegiments() << " troupes et " << tab_joueur[i].getNbRegions() << " regions" << endl;

		// Suppression de la couleur choisie dans la liste des choix de couleur
		liste_couleurs.erase(liste_couleurs.begin() + num_couleur);

		cout << endl;
	}

		// Repartition aleatoire des territoires
	srand((unsigned int) time(NULL));
	vector<Region*> territoires;
	for (unsigned int i = 0; i < terrain.getTabPays().size(); i++)
	{
		for (unsigned int j = 0; j < terrain.getTabPays()[i]->getTabRegions().size(); j++)
		{
			territoires.push_back( terrain.getTabPays()[i]->getTabRegions()[j] );
		}
	}

	for (unsigned int i = 0; i < nb_joueur; i++)
	{
		for (unsigned int j = 0; j < tab_joueur[i].getNbRegions(); j++)
		{
			unsigned int random_val = rand() % territoires.size();
			tab_joueur[i].getRegionsJoueur().push_back( territoires[ random_val ] );
			territoires.erase( territoires.begin() + random_val );
		}
	}	
	// Il reste eventuellement des territoires non attribués pour une partie à 4 ou 5 joueurs

	for (unsigned int i = 0; i < nb_joueur; i++)
	{
		cout << tab_joueur[i].getnom_joueur() << " occupe les territoires suivants :" << endl;
		for (unsigned int j = 0; j < tab_joueur[i].getNbRegions(); j++)
		{
			cout << "	" << tab_joueur[i].getRegionsJoueur()[j]->getNomRegion() << endl;
		}
		cout << endl << endl;
	}
	while( !finPartie() ){
		cout << "Phase Renfort !" <<endl;
		phaseRenfort();
		cout << "Phase Attaque !" <<endl;
		for(unsigned int i = 0; i < nb_joueur; i++){
			phaseAttaque(tab_joueur[i]);
		}
		cout << "Phase Manoeuvre !" << endl;
		for(unsigned int i = 0; i < nb_joueur; i++){
			phaseManoeuvre(tab_joueur[i]);
		}
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
		case 1 : cout <<"Un joueur peut proceder à 3 actions distinctes dans l'ordre suivant"<<endl;
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
		unsigned int b = (tab_joueur[i].getNbRegiments()/3);
		if( b >= 3 )
			total_renfort = b;
		else
			total_renfort = 3;
		troupe_avant = tab_joueur[i].getNbRegiments();
		//rajouter les renforts en fonction du pays
		total_renfort += troupe_avant;
    tab_joueur[i].setNbRegiments(total_renfort);		
	}
}

void Jeu::phaseAttaque(Joueur j)
{
	string region_depart,region_selectionner;
	int a ;
	cout<<"Joueur " << j.getCouleurJoueur()<< ", voulez-vous attaquer une region ? " <<endl;
	do
	{
		cout <<"oui : 1"<<endl;
		cout <<"non : 2" <<endl;
		cin >> a ;
	}while((a<1)||(a>2));

	
	if(a == 1)
	{	
		Region region_depart, region_attaquee;
  		vector <Region> tab_regions_frontalieres;
		unsigned int num;
		do{
    		cout << "Choisis la region depuis laquelle tu veux attaquer : " << endl;
    		for( unsigned int i = 0; i < j.getNbRegions(); i++)
      		{
				cout << j.getRegionsJoueur()[i]->getNomRegion() << " : " << i <<endl;
     		}
    		cin >> num;}
  		while(num < 0 || num >= j.getNbRegions() );
	
		region_depart = *(j.getRegionsJoueur()[num]);
		
  		for (unsigned int i = 0; i < region_depart.getTabFrontaliers().size(); i++)
  		{
  			tab_regions_frontalieres.push_back(*(region_depart.getTabFrontaliers()[i]));
  		}
  		for( unsigned int i = 0; i < tab_regions_frontalieres.size(); i++)
   	 		if( tab_regions_frontalieres[i].getCouleurRegion() == j.getCouleurJoueur())
      			tab_regions_frontalieres.erase( tab_regions_frontalieres.begin() + i );
	
		do{
    		cout << " Choisis la region frontaliere que tu souhaites attaquer : " <<endl;
    		for( unsigned int i = 0; i < tab_regions_frontalieres.size(); i++)
      		{
				cout << tab_regions_frontalieres[i].getNomRegion() << " : " << i << endl;
      		}
    		cin >> num;}
  		while( num < 0 || num >= tab_regions_frontalieres.size() );
 
  		region_attaquee = tab_regions_frontalieres[num];
		
		Joueur j2;
		for(unsigned int i = 0; i < nb_joueur; i++)
			if(region_attaquee.getCouleurRegion() == tab_joueur[i].getCouleurJoueur())
				j2 = tab_joueur[i];
		
		Combat batailleEpique(j, j2, region_depart, region_attaquee);
		batailleEpique.maj_troupes(region_depart, region_attaquee, j, j2);
	}
	
}




		
void Jeu::phaseManoeuvre(Joueur j){
  Region region_depart, region_arrivee;
  unsigned int num;
  vector <Region> tab_regions_frontalieres;

  do{
    cout << "Joueur " << j.getCouleurJoueur() << ", choisis la region de depart : " << endl;
    for( unsigned int i = 0; i < j.getNbRegions(); i++)
      {
	cout << j.getRegionsJoueur()[i]->getNomRegion() << " : " << i <<endl;
      }
    cin >> num;}
  while(num < 0 || num >= j.getNbRegions() );

  region_depart = *(j.getRegionsJoueur()[num]);
  for (unsigned int i = 0; i < region_depart.getTabFrontaliers().size(); i++)
  {
  	tab_regions_frontalieres.push_back(*(region_depart.getTabFrontaliers()[i]));
  }
  for( unsigned int i = 0; i < tab_regions_frontalieres.size(); i++)
    if( tab_regions_frontalieres[i].getCouleurRegion() != j.getCouleurJoueur())
      tab_regions_frontalieres.erase( tab_regions_frontalieres.begin() + i );

  do{
    cout << " Choisis la region frontaliere ou doivent se rendre les troupes : " <<endl;
    for( unsigned int i = 0; i < tab_regions_frontalieres.size(); i++)
      {
	cout << tab_regions_frontalieres[i].getNomRegion() << " : " << i <<endl;
      }
    cin >> num;}
  while( num < 0 || num >= tab_regions_frontalieres.size() );
 
  region_arrivee = tab_regions_frontalieres[num];

  unsigned int max_troupes = region_depart.getNbUnite()-1;
  do{
    cout << "Choisis le nombre de troupes à déplacer entre 0 et " << max_troupes << " : ";
    cin >> num;}
  while(num < 0 || num > max_troupes);

  region_depart.setNbUnite(region_depart.getNbUnite() - num);
  region_arrivee.setNbUnite(region_arrivee.getNbUnite() + num);

}
		

void Jeu::initJeu()
{
	terrain.initTerrain();
}

void Jeu::afficheTerrainTXT()
{
	for (unsigned int i = 0; i < terrain.getTabPays().size(); i++)
	{
		cout << terrain.getTabPays()[i]->getNomPays() << " (" << terrain.getTabPays()[i]->getRegimentsSupp() << ")" <<  endl;
		for (unsigned int j = 0; j < terrain.getTabPays()[i]->getTabRegions().size(); j++)
		{
			cout << "	" << terrain.getTabPays()[i]->getTabRegions()[j]->getNomRegion() << endl;
			cout << "	(";
			for (unsigned int k = 0; k < terrain.getTabPays()[i]->getTabRegions()[j]->getTabFrontaliers().size(); k++)
			{
				cout << terrain.getTabPays()[i]->getTabRegions()[j]->getTabFrontaliers()[k]->getNomRegion();
				if (k != terrain.getTabPays()[i]->getTabRegions()[j]->getTabFrontaliers().size()-1)
				{
					cout << ", ";
				}
			}
			cout << ")" << endl << endl;
		}
		cout << endl << endl;
	}
}
