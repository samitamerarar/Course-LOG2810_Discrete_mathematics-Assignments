/*
Fichier: Etat.h
Auteur(s): Tamer Arar, Eric Chao et Guy-Frank
Date de creation: 21 mars 2017
Description: Represente l'etat de l'automate où chaque etat est une serie de lettres
*/

#ifndef ETAT_H
#define ETAT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>

class Etat {
public:
    Etat();
    Etat(const std::string& identifiant);
    ~Etat();

    //getters
    std::string getIdentifiant() const;
    bool siFinal();	//vrai quand l'Etat est la derniere lettre d'un mot
    std::vector<Etat*>& obtenirEnfants();

    //setters
    void modifierIdentifiant(std::string lettres);
    void mettreCommeFinal();					//marque un Etat (noeud) comme final (car fin de mot)

    void ajouterEnfant(Etat* enfant);			//ajouter un Etat au vecteur enfants_

    Etat* trouverUnEnfant(std::string etat);	//retourne l'Etat (noeud) correspondant a l'etat voulu

    //friend std::ostream& operator<<(std::ostream& os, const Etat& etat);
private:
    std::string identifiant_;
    bool siFinal_;

    std::vector<Etat*> enfants_;
};

#endif
