/*
Fichier: Foncteur.h
Auteur(s): Tamer Arar, Guy-Frank et Eric Chao
Date de creation: 15 fevrier 2017
Description: regroupe les foncteurs de ce TP
*/

#ifndef FONCTEUR
#define FONCTEUR

#include "Sommet.h"

//foncteur qui renvoie True si le nom d'un sommet (en paramètre) = nom sommet de la classe
class FoncteurSommetsDeMemeNom
{
public:
	FoncteurSommetsDeMemeNom(const std::string& nom) : identifiantDeReference_(nom) {}
	~FoncteurSommetsDeMemeNom() {}

	bool operator() (Sommet *sommet) const {
		return sommet->obtenirIdentifiant() == identifiantDeReference_;
	}

private:
	std::string identifiantDeReference_;
};

#endif