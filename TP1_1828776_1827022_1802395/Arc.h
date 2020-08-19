/*
Fichier: Arc.h
Auteur(s): Tamer Arar, Guy-Frank et Eric Chao
Date de creation: 15 fevrier 2017
Description: chaque arc du graphe a une longueur en metres
*/

#ifndef ARC
#define ARC

class Arc {
public:
	//constructeurs
	Arc();
	Arc(const int distance);

	//getter de l'attribut distance
	int obtenirDistance() const;

private:
	int distance_;
};

#endif