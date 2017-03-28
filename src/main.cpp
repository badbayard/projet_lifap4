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

	int i,j;
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



	//test du module joueur et terrain
	string essai1;
	string essai2;
	unsigned int a;

	//test du module jeu
	Jeu jeu;
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
			jeu.afficherAide();
			break;
		
		case 2:
			jeu.lancerJeu();
			break;
		
		case 3:
			exit(1);
	}
	return 0;
}
