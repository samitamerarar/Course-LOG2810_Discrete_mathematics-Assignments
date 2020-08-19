/*
Fichier: Automate.h
Auteur(s): Tamer Arar, Eric Chao et Guy-Frank
Date de creation: 21 mars 2017
Description: Represente l'automate minimal qui contient des etats representees par des suites de lettres
                dont leurs combinaisons formeront un mot complet appartenant a un lexique fournit par un fichier.
*/

#ifndef AUTOMATE_H
#define AUTOMATE_H

#include "Etat.h"
#include <QFile>

class Automate {
public:
    Automate();
    ~Automate();

    //getter
    std::vector<std::string>& obtenirLignesALire();

    bool lireLexique(std::string nomFichier);	//lit un fichier et le met dans le tableau de string lignesALire_
    void creerAutomate();						//creation de l'arbre ayant des lettres comme etats (noeuds)
    std::vector<std::string> retournerSuggestions(std::string mot); //retourne un vecteur de suggestions de mot selon un prefixe
    std::vector<Etat*> recherche(Etat* pointDeDepart); //execute l'algorithme de recherche
    bool motPresent(std::string mot);			//verifier la presence du mot dans l'automate
    std::string corrigerLeMot(std::string mot); //renvoie la correction d'un mot mal ecrit d'une lettre

private:
    Etat* racine_;
    std::vector<std::string> lignesALire_;
};

#endif
