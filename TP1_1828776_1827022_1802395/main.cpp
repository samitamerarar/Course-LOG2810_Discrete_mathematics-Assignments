/*
Fichier: main.h
Auteur(s): Tamer Arar, Guy-Frank et Eric Chao
Date de creation: 15 fevrier 2017
Description: menu principal; selon la lettre inseree, une option est executee
*/

#include "Graphe.h"
#include <Windows.h>
#undef max

int main()
{
	std::string menu[4] = { "(a) Mettre a jour la carte", "(b) Determiner le plus court chemin", "(c) Determiner le plus grand gain", "(d) Quitter" };

	std::string optionSelect = "";
	int pointeur;
	
	
	Graphe graphe;
	std::string nomDuFichier;
	std::string identifiantDepart;
	int gainVoulu;
	int distanceMaxVoulu;
	bool grapheMisAJour = false;


	for(;;)
	{
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11); //Rouge
		std::cout << "\t<TP1 - Graphes> par : Tamer A, Eric C et Guy E" << std::endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); //Rouge
		std::cout << "---------------------Menu Principal---------------------" << std::endl << std::endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); //Vert
		std::cout << "Veuillez choisir parmi les options suivantes en inserant" << std::endl << "la lettre correspondante suivi de la touche ENTREE" << std::endl << std::endl;

		for (int i = 0; i < sizeof(menu)/sizeof(menu[0]); i++) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); //blanc
				std::cout << menu[i] << std::endl;
		}

		for(;;)
		{
			while (1) {

				for (;;) { 
					if (std::cin >> optionSelect)
						break;
					else {
						std::cout << "Veuillez inserer un indice valide" << std::endl;
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					}
				}

				if (optionSelect.length() > 1)
					std::cout << "SVP inserer un indice valide" << std::endl;
	
				else {

					if (optionSelect[0] == 'a') {
						pointeur = 0;
						break;
					}
					else if (optionSelect[0] == 'b') {
						pointeur = 1;
						break;
					}
					else if (optionSelect[0] == 'c') {
						pointeur = 2;
						break;
					}
					else if (optionSelect[0] == 'd') {
						pointeur = 3;
						break;
					}
					else
						std::cout << "SVP inserer un indice valide" << std::endl;
				}
				
			}

			switch (pointeur)
			{
				case 0: //mettre a jour la carte
				{
					graphe.viderVecSommet(); //vider le vecteur avant de l'afficher
					
					//gerer la saisie de texte
					for (;;) { //"data_pokemon.txt"
						std::cout << "Veuillez entrer le nom du fichier contenant les informations sur le graphe." << std::endl;
						if (std::cin >> nomDuFichier) {
							break;
						}
						else {
							std::cout << "Veuillez inserer un nom de fichier valide" << std::endl;
							std::cin.clear();
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						}
					}
					graphe.creerGraphe(nomDuFichier);
					std::cout << std::endl << std::endl << "Lecture du fichier en cours..." << std::endl;
					Sleep(1200);
					graphe.lireGraphe();

					if (graphe.obtenirVecteurSommets().size() > 1)
						grapheMisAJour = true;

					Sleep(1000);
					std::cout << std::endl << std::endl << "Appuyer sur ESC pour revenir au menu principal";
					for (;;) { //faut faire escape pour revenir au menu principal
						if (GetAsyncKeyState(VK_ESCAPE))
							break;
					};
				}break;
				case 1: //determiner le plus court chemin
				{
					if (grapheMisAJour == false) {
						std::cout << "Vous devez d'abord mettre a jour le graphe!" << std::endl;
						Sleep(2000);
						break;
					}

					//entree utilisateur de l'identifiant de depart
					for (;;) {
						std::cout << std::endl << std::endl << "Veuillez entrer l'identifiant de votre point de depart." << std::endl;
						if (std::cin >> identifiantDepart) {
							break;
						}
						else {
							std::cout << "Veuillez inserer un identifiant valide!" << std::endl;
							std::cin.clear();
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						}
					}

					//entree utilisateur du gain voulu
					for (;;) {
						std::cout << std::endl << "Veuillez maintenant entrer le gain voulu." << std::endl;
						if (std::cin >> gainVoulu) {
							break;
						}
						else {
							std::cout << "Veuillez inserer un gain valide!" << std::endl;
							std::cin.clear();
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						}
					}


					//affichage du resultat
					std::cout << std::endl << "Voici votre resultat: " << std::endl;
					Sleep(1500);
					graphe.plusCourtChemin(identifiantDepart, gainVoulu);


					Sleep(1000);
					std::cout << std::endl << std::endl << "Appuyer sur ESC pour revenir au menu principal";
					for (;;) { //faut faire escape pour revenir au menu principal
						if (GetAsyncKeyState(VK_ESCAPE))
							break;
					};
				}break;
				case 2: //determiner le plus grand gain
				{	
					if (grapheMisAJour == false) {
						std::cout << "Vous devez d'abord mettre a jour le graphe!" << std::endl;
						Sleep(2000);
						break;
					}

					//entree utilisateur de l'identifiant de depart
					for (;;) {
						std::cout << std::endl << std::endl << "Veuillez entrer l'identifiant de votre point de depart." << std::endl;
						if (std::cin >> identifiantDepart) {
							break;
						}
						else {
							std::cout << "Veuillez inserer un identifiant valide!" << std::endl;
							std::cin.clear();
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						}
					}

					//entree utilisateur de la distance max voulu
					for (;;) {
						std::cout << std::endl << "Veuillez maintenant entrer la distance maximale que vous voulez parcourir." << std::endl;
						if (std::cin >> distanceMaxVoulu) {
							break;
						}
						else {
							std::cout << "Veuillez inserer un gain valide!" << std::endl;
							std::cin.clear();
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						}
					}


					//affichage du resultat
					std::cout << std::endl << "Voici votre resultat: " << std::endl;
					Sleep(1500);
					graphe.plusGrandGain(identifiantDepart, distanceMaxVoulu);

					Sleep(1000);
					std::cout << std::endl << std::endl << "Appuyer sur ESC pour revenir au menu principal";
					for (;;) { //faut faire escape pour revenir au menu principal
						if (GetAsyncKeyState(VK_ESCAPE))
							break;
					};
				}break;
				case 3: //quitter
				{
					std::cout << std::endl << "A la prochaine!" << std::endl;
					Sleep(2000);
					return 0;
				}break;
			}
			break;
		}
		Sleep(100);
	}
	return 0;
}