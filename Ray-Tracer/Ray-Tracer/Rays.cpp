/*
* IMPLEMENTATION FILE FOR RAYS
*/
#include "Rays.h"

// --- SETTERS --- //
void Rays::setDirection(vec3 direction) { this->direction	= direction;	}
void Rays::setOrigin(vec3 origin)		{ this->origin		= origin;		}
// ---------------- //

// --- GETTERS --- //
vec3 Rays::getDirection()	const	{ return this->direction;	}
vec3 Rays::getOrigin()		const	{ return this->origin;		}
// --------------- //