#include "Graphe.h"

Graphe::Graphe() 
{}

void Graphe::viderVecSommet()
{
	std::vector<Sommet*> vecVide;
	vecSommet_ = vecVide;
}

std::vector<Sommet*> Graphe::obtenirVecteurSommets() const
{
	return vecSommet_;
}

std::pair<std::string,std::string> Graphe::lireFichierGraphe(std::string nomFichier) 
{
	std::string ligne1;
	std::string ligne2;

	//lire et stocker les 2 lignes du fichier dans 2 string differents
	std::ifstream fichier(nomFichier);
	if (fichier.is_open()) {
		std::getline(fichier, ligne1);
		std::getline(fichier, ligne2);
	}
	else
		std::cout << "Erreur du fichier" << std::endl;

	return std::make_pair(ligne1, ligne2);
}

void Graphe::creerGraphe(std::string nomFichier)
{
	//storer la premiere ligne du fichier dans un string
		//et activer la lecture du string
	std::stringstream ss1(lireFichierGraphe(nomFichier).first);

	//elements a lire
	std::string identifiant;
	std::string type;
	std::string gainEnString;
	int gain;

	//lire la premiere ligne 		
		//et ajouter chaque nouveau sommet au vecteur de sommets
	while (std::getline(ss1, identifiant, ',')) {
		std::getline(ss1, type, ',');
		std::getline(ss1, gainEnString, ';');
		std::stringstream aa(gainEnString); //convertit le string lu
		aa >> gain;							//en int

		vecSommet_.push_back(new Sommet(identifiant, type, gain));
	}


	//storer la deuxieme ligne du fichier dans un string
	//et activer la lecture du string
	std::stringstream ss2(lireFichierGraphe(nomFichier).second);

	//elements a lire
	std::string identifiant1;
	std::string identifiant2;
	std::string distanceEnString;
	int distance;

	//lire la deuxieme ligne
		//et associer chaque sommet avec un arc
	while (std::getline(ss2, identifiant1, ',')) {
		std::getline(ss2, identifiant2, ',');
		std::getline(ss2, distanceEnString, ';');
		std::stringstream bb(distanceEnString); //convertit le string lu 
		bb >> distance;							//en int


		//chercher le sommet dans le vecteur a l'aide de son identifiant en utilisant un foncteur qui se charge de comparer les noms
		auto itSommet = std::find_if(vecSommet_.begin(), vecSommet_.end(), FoncteurSommetsDeMemeNom(identifiant1));
		auto itSommet2 = std::find_if(vecSommet_.begin(), vecSommet_.end(), FoncteurSommetsDeMemeNom(identifiant2));

		//2 sommets voisins
		Sommet *sommet1 = *itSommet;
		Sommet *sommet2 = *itSommet2;

		//chaque sommet a son propre arc
		Arc arc(distance);
		std::pair<Sommet*, Arc> pair1 = std::make_pair(sommet1, arc);
		std::pair<Sommet*, Arc> pair2 = std::make_pair(sommet2, arc);

		//ajouter au premier sommet la paire de sommet-arc du deuxieme sommet
		sommet1->ajouterPaireSommetArc(pair2);
		//ajouter au deuxieme sommet la paire de sommet-arc du premier sommet
		sommet2->ajouterPaireSommetArc(pair1);
	}
}

void Graphe::lireGraphe()
{
	if (vecSommet_.empty())
		std::cout << "Rien a afficher!" << std::endl;

	else {
		std::cout << std::endl << "Graphe:" << std::endl << std::endl;
		for (int i = 0; i < vecSommet_.size(); i++)
			std::cout << *vecSommet_[i] << std::endl << std::endl;
	}
}

int Graphe::distanceSelonLeSommet(Sommet* som)
{
	int distanceARetourner = 0;

	std::string type = som->obtenirType();
	int gain = som->obtenirGain();

	//si c'est un pokemon
	if (type == "pokemon") {
		if (gain == 10)
			distanceARetourner = 100;
		else if (gain == 40)
			distanceARetourner = 200;
		else if (gain == 100)
			distanceARetourner = 500;
	}

	//si c'est un pokestop ou une arene
	else if (type == "pokestop")
		distanceARetourner = 100;
	else if (type == "arene")
		distanceARetourner = -1;

	return distanceARetourner;
}

void Graphe::distanceRestante(int distance)
{
	//pour chaque sommet
	for (int i = 0; i < vecSommet_.size(); i++) {

		Sommet* som = vecSommet_[i];

		//on soustrait de sa distance marquée, la distance que l'on vient de parcourir sur le graphe
		if (som->obtenirDistanceMarque() >= 0) {

			som->modifierDistanceMarque(som->obtenirDistanceMarque() - distance);
			if (som->obtenirDistanceMarque() < 0)
				som->modifierDistanceMarque(0);

			//et on le démarque pour qu'il redevient accessible sur le graphe
			if (som->obtenirDistanceMarque() == 0)
				som->marquerSommet(false);
		}
	}

}

void Graphe::plusCourtChemin(std::string identifiantDepart, int gainDesire)
{
	auto it = std::find_if(vecSommet_.begin(), vecSommet_.end(), FoncteurSommetsDeMemeNom(identifiantDepart));
	//gerer les donnees saisis, si le sommet est existant et que le gain est positif
	if (it != vecSommet_.end() && gainDesire >= 0)
	{
		std::vector<Sommet*> chemin; //le chemin de sommets qui sera créé

		auto itSommet = std::find_if(vecSommet_.begin(), vecSommet_.end(), FoncteurSommetsDeMemeNom(identifiantDepart));
		chemin.push_back(*itSommet); //mettre le sommet de depart sur notre chemin

		Sommet* sommetEnCours = *itSommet;

		std::string identifSommet;
		std::string identifSommetPourApres;

		int indiceVecteur;
		int indiceVoisin;

		double rapport = std::numeric_limits<int>::max();
		int gainEnCours = 0;
		int distance = 0;

		while (gainEnCours < gainDesire) {

			for (int i = 0; i < vecSommet_.size(); i++) {
				if (sommetEnCours == vecSommet_[i]) {			//trouver les voisins du vecteur en cours
					for (int j = 0; j < (vecSommet_[i]->obtenirPaireSommetArc().size()); j++) {

						//un voisin trouve!
						identifSommet = vecSommet_[i]->obtenirPaireSommetArc()[j].first->obtenirIdentifiant();

						//ne pas tenir en compte le sommet point de depart (car pas de gain)
						//ni un voisin marqué
						if (identifSommet == "depart" || vecSommet_[i]->obtenirPaireSommetArc()[j].first->siSommetMarque())
							continue;

						//tenir compte de la distance jusqu'au voisin trouvé et du gain que l'on obtiendra
						int distanceEnTrainDeParcourir = vecSommet_[i]->obtenirPaireSommetArc()[j].second.obtenirDistance();
						int gainSommet = vecSommet_[i]->obtenirPaireSommetArc()[j].first->obtenirGain();

						//on cherche un voisin avec un max de gain pour une petite distance, ratio doit etre minime
						if (rapport > double(distanceEnTrainDeParcourir) / double(gainSommet)) {
							rapport = double(distanceEnTrainDeParcourir) / double(gainSommet);
							identifSommetPourApres = identifSommet; //on a notre prochain sommet ou pas...

							indiceVecteur = i; //on conserve
							indiceVoisin = j;	//sa position
						}
					}
					break;
				}
			}

			//on marque le sommet visité et on lui ajoute sa distance respective a parcourir pour qu'il redevient accessible
			sommetEnCours->marquerSommet(true);
			sommetEnCours->modifierDistanceMarque(distanceSelonLeSommet(sommetEnCours));

			Sommet* sommetTemp;
			auto itSommet = std::find_if(vecSommet_.begin(), vecSommet_.end(), FoncteurSommetsDeMemeNom(identifSommetPourApres));
			sommetTemp = *itSommet;

			//augmentons le gain et la distance accumulés
			gainEnCours += sommetTemp->obtenirGain();
			int distanceTempDuVoisin = vecSommet_[indiceVecteur]->obtenirPaireSommetArc()[indiceVoisin].second.obtenirDistance();
			distance += distanceTempDuVoisin;

			//mettons le nouveau sommet sur le chemin
			chemin.push_back(sommetTemp);
			sommetEnCours = sommetTemp; //on vérifera après pour les voisins de ce sommet là

			//mise a jour de la distance restante pour les sommets deja parcourus
			distanceRestante(distanceTempDuVoisin);

			rapport = std::numeric_limits<int>::max();
		}

		//afficher le chemin parcouru
		for (int i = 0; i < chemin.size(); i++) {
			std::cout << chemin[i]->obtenirIdentifiant();
			if (i == chemin.size() - 1)
				std::cout << ".";
			else
				std::cout << "->";
		}

		std::cout << std::endl << std::endl << "La distance totale a parcourir pour ce trajet est de " << distance << " metres." << std::endl;
		std::cout << std::endl << "Le gain pour ce trajet est de " << gainEnCours << " points." << std::endl;
	}

	//message d'erreur
	else {
		std::cout << "Une erreur est survenue! " << std::endl << "Assurez-vous de saisir un identifiant valide et/ou un gain positif" << std::endl;
	}
}

void Graphe::plusGrandGain(std::string identifiantDepart, int distanceMaxDesire)
{
	auto it = std::find_if(vecSommet_.begin(), vecSommet_.end(), FoncteurSommetsDeMemeNom(identifiantDepart));
	//gerer les donnees saisis, si le sommet est existant et que la distance est positive
	if (it != vecSommet_.end() && distanceMaxDesire >= 0)
	{
		std::vector<Sommet*> chemin; //le chemin de sommets qui sera créé

		auto itSommet = std::find_if(vecSommet_.begin(), vecSommet_.end(), FoncteurSommetsDeMemeNom(identifiantDepart));
		chemin.push_back(*itSommet); //mettre le sommet de depart sur notre chemin

		Sommet* sommetEnCours = *itSommet;

		std::string identifSommet;
		std::string identifSommetPourApres;
		std::string identifSommetTemp;

		int indiceVecteur;
		int indiceVoisin;

		double rapport = std::numeric_limits<int>::max();
		int gainAccumule = 0;
		int distanceTotale = 0;

		while (distanceTotale < distanceMaxDesire) {

			for (int i = 0; i < vecSommet_.size(); i++) {
				if (sommetEnCours == vecSommet_[i]) {			//trouver les voisins du vecteur en cours
					for (int j = 0; j < (vecSommet_[i]->obtenirPaireSommetArc().size()); j++) {

						//un voisin trouve!
						identifSommet = vecSommet_[i]->obtenirPaireSommetArc()[j].first->obtenirIdentifiant();

						//ne pas tenir en compte le sommet point de depart (car pas de gain)
						//ni un voisin marqué
						if (identifSommet == "depart" || vecSommet_[i]->obtenirPaireSommetArc()[j].first->siSommetMarque())
							continue;

						//tenir compte de la distance jusqu'au voisin trouvé et du gain que l'on obtiendra
						int distanceEnTrainDeParcourir = vecSommet_[i]->obtenirPaireSommetArc()[j].second.obtenirDistance();
						int gainSommet = vecSommet_[i]->obtenirPaireSommetArc()[j].first->obtenirGain();

						//on ignore les sommets qui depasserons la distance maximale désirée
						if (distanceEnTrainDeParcourir + distanceTotale <= distanceMaxDesire) {

							//on cherche un voisin avec un max de gain pour une petite distance, ratio doit etre minime
							if (rapport > double(distanceEnTrainDeParcourir) / double(gainSommet)) {
								rapport = double(distanceEnTrainDeParcourir) / double(gainSommet);
								identifSommetPourApres = identifSommet; //on a notre prochain sommet ou pas...

								indiceVecteur = i; //on conserve
								indiceVoisin = j;	//sa position
							}
						}
					}
					break;
				}
			}
			//utile pour voir si aucun voisin na été trouver car sinon on depassera la limite de distance fixée en ajoutant le voisin
			//trouvé precedemment sur le chemin (eviter de le réutiliser 2 fois)
			if (identifSommetPourApres == identifSommetTemp) {
				break;
			}
			identifSommetTemp = identifSommetPourApres; //prend en memoire le voisin pour eviter de le réutiliser 2 fois


														//on marque le sommet visité et on lui ajoute sa distance respective a parcourir pour qu'il redevient accessible
			sommetEnCours->marquerSommet(true);
			sommetEnCours->modifierDistanceMarque(distanceSelonLeSommet(sommetEnCours));

			Sommet* sommetTemp;
			auto itSommet = std::find_if(vecSommet_.begin(), vecSommet_.end(), FoncteurSommetsDeMemeNom(identifSommetPourApres));
			sommetTemp = *itSommet;

			//augmentons le gain et la distance accumulés
			gainAccumule += sommetTemp->obtenirGain();
			int distanceTempDuVoisin = vecSommet_[indiceVecteur]->obtenirPaireSommetArc()[indiceVoisin].second.obtenirDistance();
			distanceTotale += distanceTempDuVoisin;

			//mettons le nouveau sommet sur le chemin
			chemin.push_back(sommetTemp);
			sommetEnCours = sommetTemp; //on vérifera après pour les voisins de ce sommet là

										//mise a jour de la distance restante pour les sommets deja parcourus
			distanceRestante(distanceTempDuVoisin);

			rapport = std::numeric_limits<int>::max();
		}

		//afficher le chemin parcouru
		for (int i = 0; i < chemin.size(); i++) {
			std::cout << chemin[i]->obtenirIdentifiant();
			if (i == chemin.size() - 1)
					std::cout << ".";
			else
				std::cout << "->";
		}

		std::cout << std::endl << std::endl << "Le gain de se trajet est de " << gainAccumule << " points." << std::endl;
		std::cout << std::endl << "La distance totale a parcourir pour ce trajet est de " << distanceTotale << " metres." << std::endl;
	}

	//message d'erreur
	else {
		std::cout << "Une erreur est survenue! " << std::endl << "Assurez-vous de saisir un identifiant valide et/ou une distance positive" << std::endl;
	}
}