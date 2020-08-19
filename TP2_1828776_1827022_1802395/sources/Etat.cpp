#include "Etat.h"

Etat::Etat() : identifiant_(""), siFinal_(false)
{}

Etat::Etat(const std::string& identifiant)
    :identifiant_(identifiant)
{}

Etat::~Etat()
{}

/**
Getter du nom de l'Etat (noeud).

@return Le nom de l'Etat.
*/
std::string Etat::getIdentifiant() const
{
    return identifiant_;
}

/**
Getter du l'etat de l'Etat (noeud).

@return Vrai si l'Etat est un mot complet sinon Faux.
*/
bool Etat::siFinal()
{
    return siFinal_;
}

/**
Getter du vecteur des enfants de chaque Etat.

@return Le vecteur des enfants de chaque Etat.
*/
std::vector<Etat*>& Etat::obtenirEnfants()
{
    return enfants_;
}

/**
Modificateur du nom de l'Etat (noeud).

@param lettres Le nouveau nom de l'Etat.
@return void.
*/
void Etat::modifierIdentifiant(std::string lettres)
{
    identifiant_ = lettres;
}

/**
Met l'etat d'un Etat a Vrai (vrai veut dire que c'est un Etat
avec un mot complet).

@return void.
*/
void Etat::mettreCommeFinal()
{
    siFinal_ = true;
}

/**
Ajouter un enfant au vecteur d'Etats enfants d'un Etat.

@param enfant L'Etat enfant a ajouter.
@return void.
*/
void Etat::ajouterEnfant(Etat* enfant)
{
    enfants_.push_back(enfant);
}

/**
Trouver un Etat specifique dans les enfant d'un Etat.

@param etat L'Etat dans lequel on va chercher parmis ses enfant.
@return L'Etat s'il a ete trouve, sinon nullptr.
*/
Etat* Etat::trouverUnEnfant(std::string identifiant)
{
    //retourne l'enfant
    for (auto it = enfants_.begin(); it != enfants_.end(); it++) {
        if ((*it)->getIdentifiant() == identifiant)
            return (*it);
    }
    //ou
    return nullptr;
}
