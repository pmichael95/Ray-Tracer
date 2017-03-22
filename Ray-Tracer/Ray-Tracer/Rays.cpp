/*
* IMPLEMENTATION FILE FOR RAYS
*/
#include "Rays.h"

// Destructor
Rays::~Rays() { }

// --- SETTERS --- //
void Rays::setDirection(vec3 direction) { this->direction	= normalize(direction);	}
void Rays::setOrigin(vec3 origin)		{ this->origin		= origin;				}
// ---------------- //

// --- GETTERS --- //
vec3 Rays::getDirection()	const	{ return this->direction;	}
vec3 Rays::getOrigin()		const	{ return this->origin;		}
// --------------- //

// --- HELPERS --- //
vec3 Rays::getPoint(float t) {
	return this->getOrigin() + this->getDirection() * t;
}
// --------------- //