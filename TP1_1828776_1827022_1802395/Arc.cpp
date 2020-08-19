#include "Arc.h"

Arc::Arc() : distance_(0) {}

Arc::Arc(const int distance)
	: distance_(distance) 
{}

int Arc::obtenirDistance() const
{
	return distance_;
}
