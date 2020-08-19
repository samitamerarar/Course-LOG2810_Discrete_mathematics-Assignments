#include "Automate.h"

Automate::Automate()
{
    racine_ = new Etat();
}

Automate::~Automate()
{}

/**
Getter du vecteur contenant les mots d'un lexique

@return Le vecteur contenant les mots d'un lexique.
*/
std::vector<std::string>& Automate::obtenirLignesALire()
{
    return lignesALire_;
}

/**
Lit un fichier texte dont chaque ligne contient un mot et store
chaque mot dans un vecteur de string.

@param nomFichier Le fichier du lexique contenant un mot par ligne.
@return bool Vrai si la lecture a ete effectuee sinon Faux.
*/
bool Automate::lireLexique(std::string nomFichier)
{
    //lecture du fichier
    std::ifstream fichier(nomFichier);

    if (!fichier.is_open()) {
        return false;
    }
    else {
        while (!fichier.eof()) {
            std::string temp;
            std::getline(fichier, temp);
            lignesALire_.push_back(temp);
        }
        fichier.close();
    }
    return true;
}

/**
Creer un automate minimal a partir d'un vecteur de string contenant comme
elements des mots d'un lexique.

@return void.
*/
void Automate::creerAutomate()
{
    //pour chaque mot
    for (auto it = lignesALire_.begin(); it != lignesALire_.end(); it++) {
        std::string mot = *it;

        Etat* etatEnCours = racine_;

        std::string lettres;
        //traiter le mot lettre par lettre
        for (int i = 0; i < mot.size(); i++) {

            lettres += mot[i];

            //trouver si la lettre a un enfant
            Etat* enfant = etatEnCours->trouverUnEnfant(lettres);

            //si la lettre n'a pas d'enfant, creer un nouvel Etat, l'ajouter comme enfant
            //a l'etat en cours et ensuite traiter le nouvel Etat de la meme maniere
            if (enfant == nullptr) {
                Etat* nouveauEtat = new Etat();
                nouveauEtat->modifierIdentifiant(lettres);
                etatEnCours->ajouterEnfant(nouveauEtat);
                etatEnCours = nouveauEtat;
            }
            else
                etatEnCours = enfant;

            //marquer la derniere lettre du mot pour indiquer la fin du mot
            if (mot.size() == (i + 1))
                etatEnCours->mettreCommeFinal();
        }
    }
}

/**
Execute la recherche a partir d'un point de depart.

@param pointDeDepart L'Etat (noeud) sur lequel on commence la recherche.
@return Le vecteur contenant toutes les suggestions (max 10).
*/
std::vector<Etat*> Automate::recherche(Etat* pointDeDepart)
{
    std::queue<Etat*> queue;
    std::vector<Etat*> vecSuggestionEtats;
    Etat* etatEnCours = pointDeDepart;

    //on commence a chercher dans l'arbre a partir de la derniere lettre de la sequence de mots
    queue.push(etatEnCours); //on le met sur la queue

    //tant qu'il y a des elements sur la queue
    while (!queue.empty()) {
        etatEnCours = queue.front();	//tranferer l'element
        queue.pop();					//retirer l'element

        //si l'etat sur lequel on se trouve presentement est un mot complet, on le sauvegarde
        if (etatEnCours->siFinal())
            vecSuggestionEtats.push_back(etatEnCours);

        //on sort apres 10 suggestions (on ne veut pas plus que 10 suggestions)
        if (vecSuggestionEtats.size() == 10)
            break;

        //on met sur la queue tous les sommets enfants du sommet en cours
        for (int k = 0; k < etatEnCours->obtenirEnfants().size(); k++) {
            if (etatEnCours->obtenirEnfants().at(k) != nullptr)
                queue.push(etatEnCours->obtenirEnfants().at(k));
        }
    }

    return vecSuggestionEtats;
}

/**
Trouve des suggestions pour rendre un mot, dont seulement son
debut est connu, complet.

@param mot Le prefix d'un mot.
@return Le vecteur contenant toutes les suggestions.
*/
std::vector<std::string> Automate::retournerSuggestions(std::string mot)
{
    std::vector<std::string> vecSuggestion;
    std::string suggestion = mot;

    Etat* etatEnCours = racine_;

    std::string lettres;
    //on se rend d'abord a l'etat de la derniere lettre du mot
    for (int i = 0; i < mot.size(); i++) {

        //lettre par lettre
        lettres += mot[i];

        //si on trouve un enfant on continue avec cet enfant
        Etat* enfant = etatEnCours->trouverUnEnfant(lettres);
        if (enfant == nullptr)
            return vecSuggestion; //qui devrait etre vide
        else
            etatEnCours = enfant;
    }

    //executer l'algorithme de recherche
    std::vector<Etat*> vecSuggestionEtats = recherche(etatEnCours);

    //transferer tous les elements du vecteur d'objets ETAT vers un vecteur de STRING
    for (auto it = vecSuggestionEtats.begin(); it != vecSuggestionEtats.end(); it++)
        vecSuggestion.push_back((*it)->getIdentifiant());

    return vecSuggestion;
}

/**
Regarde si un mot est present dans le lexique.

@param mot Le mot a chercher.
@return Vrai si le mot est trouvé, sinon Faux.
*/
bool Automate::motPresent(std::string mot)
{
    Etat* etatEnCours = racine_;

    //parcours l'automate de lettre en lettre pour trouver si le mot est present
    std::string lettres;
    for (int i = 0; i < mot.size(); i++) {

        lettres += mot[i];
        Etat* enfant = etatEnCours->trouverUnEnfant(lettres); //aller au sous enfant
        if (enfant != nullptr)
            etatEnCours = enfant;
        else
            return false;	//pas trouve
    }

    if (etatEnCours->siFinal())
        return true;	//trouve!
    return false;	//pas trouve
}

/**
Regarde s'il peut suggerer une correction a un mot
qui differe que d'une seule lettre du vrai mot.

@param mot Le mot a corriger.
@return La correction du mot a corriger.
*/
std::string Automate::corrigerLeMot(std::string mot)
{
    std::string possibiliteDeMot;

    if (motPresent(mot))
        return mot;

    for (int i = 1; i < mot.size(); i++) {

        possibiliteDeMot = mot; //sauvegarde du mot a corriger

        //remplacer une lettre du mot par tous les lettres de
        //l'alphabet et regarder pour chaque cas si le mot existe
        for (char j = 97; j <= 122; j++) { //de a-z (en ascii)
            possibiliteDeMot[i] = j;
            if (motPresent(possibiliteDeMot))
                return possibiliteDeMot;
        }
    }

    return mot; //le mot differe de plus d'une lettre et/ou lexique incomplet
}
