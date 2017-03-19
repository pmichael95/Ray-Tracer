/*
* IMPLEMENTATION FILE FOR RAYS
*/
#include "Rays.h"

// Constructor
Rays::Rays(Camera &cam, int i, int j) {
	this->camera = &cam;
	this->constructRayThroughPixel(camera, i, j);
	this->setOrigin(this->camera->getPosition());
	this->setDirection(vec3(0.0f, 0.0f, 0.0f));
}

// Destructor
Rays::~Rays() {  }

// --- SETTERS --- //
void Rays::setDirection(vec3 direction) { this->direction	= direction;	}
void Rays::setOrigin(vec3 origin)		{ this->origin		= origin;		}
// ---------------- //

// --- GETTERS --- //
vec3 Rays::getDirection()	const	{ return this->direction;	}
vec3 Rays::getOrigin()		const	{ return this->origin;		}
// --------------- //

// --- HELPERS --- //
vec3 Rays::getPoint(float t) {
	return this->getOrigin() + this->getDirection() * t;
}

// Need to project the ray through each pixel
Rays Rays::constructRayThroughPixel(Camera *cam, int i, int j) {
	// Use camera member's function for it
	cam->throughPixel(i, j);
}
// --------------- //