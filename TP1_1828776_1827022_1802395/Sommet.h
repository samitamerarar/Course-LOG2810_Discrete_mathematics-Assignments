/*
Fichier: Sommet.h
Auteur(s): Tamer Arar, Guy-Frank et Eric Chao
Date de creation: 15 fevrier 2017
Description: chaque sommet du graphe a un identifiant, un type et une valeur
*/

#ifndef SOMMET
#define SOMMET

#include <iostream>
#include <string>
#include <vector>

#include "Arc.h"

class Sommet {
	public:
		//constructeurs
		Sommet();
		Sommet(const std::string& identifiant, const std::string& type, const int gain);

		//getters
		std::string obtenirIdentifiant() const;
		std::string obtenirType() const;
		int obtenirGain() const;
		std::vector <std::pair<Sommet*, Arc>>& obtenirPaireSommetArc();

		int obtenirDistanceMarque() const; //retourne la distance restante a parcourir pour demarquer le sommet
		bool siSommetMarque() const; //fait savoir si le sommet est marque ou pas

		//setters
		void modifierIdentifiant(std::string identifiant);
		void modifierType(std::string type);
		void modifierGain(int gain);

		void modifierDistanceMarque(int distance); //modifie la distance restante a parcourir du sommet
		void marquerSommet(bool boolean); //marque/demarque le sommet pour qu'il soit inaccessible/accessible lors du parcours du graphe
	
		//ajoute une paire sommet-arc au vecteur de sommet-arc
		void ajouterPaireSommetArc(std::pair<Sommet*, Arc> pair);

		//surcharge sur l'operateur << pour l'affichage de l'informations sur un sommet et de ses sommets adjacents
		friend std::ostream& operator<<(std::ostream& os, const Sommet& sommet);

	private:
		std::string identifiant_;
		std::string type_;
		int gain_;

		//vecteur qui contient des paires sommet-arc
		std::vector <std::pair<Sommet*, Arc>> vecPaireSommetArc_;

		bool marque_;
		int distanceMarque_;
};

#endif