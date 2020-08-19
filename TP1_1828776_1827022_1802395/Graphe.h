/*
Fichier: Graphe.h
Auteur(s): Tamer Arar, Guy-Frank et Eric Chao
Date de creation: 15 fevrier 2017
Description: graphe non oriente regroupant tous les sommets et arcs
*/

#ifndef GRAPHE
#define GRAPHE

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <utility> 
#include <vector>
#include <algorithm>
#include <list>

#include "Sommet.h"
#include "Foncteur.h"

class Graphe 
{
	public:
		//constructeur
		Graphe();

		//getters
		std::vector<Sommet*> obtenirVecteurSommets() const; //retourne le vecteur de sommets

		//vider le vecteur de sommets
		void viderVecSommet();

		//permet la lecture d'un fichier et la separation de ses 2 lignes en 2 string distincts
		std::pair<std::string, std::string> lireFichierGraphe(std::string nomFichier);

		//permet la creation d'un graphe a l'aide d'un nom de fichier passe en parametre
		void creerGraphe(std::string nomFichier);

		//permet l'affichage d'un graphe deja cr��
		void lireGraphe();

		//mettre a jour la distance restante a parcourir pour chacun des sommets deja visit�s
		//et de les d�marqu�s une fois la distance atteinte
		void Graphe::distanceRestante(int distance);

		//renvoi la distance a parcourir selon le type et le gain du sommet une fois ce sommet visit�
		int distanceSelonLeSommet(Sommet* som);

		//permet de trouver le chemin le plus court, � partir d'un sommet fix�, pour atteindre un gain fix�.
		void plusCourtChemin(std::string identifiant, int gain);

		//permet de trouver le chemin poss�dant un maximum de gain pour une distance maximale fix�e.
		void plusGrandGain(std::string identifiantDepart, int distanceMaxDesire);
		
	private:
		std::vector<Sommet*> vecSommet_; //vecteur avec tous les sommets et chaque sommet a un vecteur de sommets voisins
};

#endif