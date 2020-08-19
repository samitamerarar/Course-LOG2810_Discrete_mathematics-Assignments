#include "Sommet.h"

Sommet::Sommet() :identifiant_(""), type_(""), gain_(0) {}

Sommet::Sommet(const std::string& identifiant, const std::string& type, const int gain)
	: identifiant_(identifiant), type_(type), gain_(gain)
{
	marque_ = false;
	distanceMarque_ = 0;
}

std::string Sommet::obtenirIdentifiant() const
{
	return identifiant_;
}

std::string Sommet::obtenirType() const
{
	return type_;
}

int Sommet::obtenirGain() const
{
	return gain_;
}

std::vector <std::pair<Sommet*, Arc>>& Sommet::obtenirPaireSommetArc()
{
	return vecPaireSommetArc_;
}

int Sommet::obtenirDistanceMarque() const
{
	return distanceMarque_;
}

bool Sommet::siSommetMarque() const
{
	return marque_;
}

void Sommet::modifierDistanceMarque(int distance)
{
	distanceMarque_ = distance;
}

void Sommet::marquerSommet(bool boolean)
{
	marque_ = boolean;
}

void Sommet::ajouterPaireSommetArc(std::pair<Sommet*, Arc> paire)
{
	vecPaireSommetArc_.push_back(paire);
}

void Sommet::modifierIdentifiant(std::string identifiant) 
{
	identifiant_ = identifiant;
}

void Sommet::modifierType(std::string type) 
{
	type_ = type;
}

void Sommet::modifierGain(int gain) 
{
	gain_ = gain;
}

std::ostream& operator<<(std::ostream& os, const Sommet& sommet)
{
	os << "(" << sommet.identifiant_ << "," << sommet.type_ << "," << sommet.gain_ << ",  \t(";
	for (int i = 0; i < sommet.vecPaireSommetArc_.size(); i++) {
		os << "(" << sommet.vecPaireSommetArc_[i].first->obtenirIdentifiant();
		os << ", " << sommet.vecPaireSommetArc_[i].second.obtenirDistance();
		if (i < sommet.vecPaireSommetArc_.size() - 1)
			os << "), ";
		else
			os << ")";
	}
	return os << "))";	
}