/*
* INTERSECTION IMPLEMENTATION
*/
#include "Intersection.h"

// --- CONSTRUCTORS --- //
Intersection::Intersection(Rays &ray, Geometry &shape) {
	// Take in a ray by reference and an object that IS-A geometry type (can be sphere, triangle, plane)
	// Then build the intersection type
	bool isHit = false;
	float dist = 0.0f;
	tie(isHit, dist) = shape.intersection(ray); // Build (using derived intersection method) an intersection with the passed ray
												// NOTE: It may or may not actually have an intersection.
	// When done, extract the values from the above isHit and dist to set our member variables
	this->hit		= isHit;
	this->distance	= dist;
}

Intersection::~Intersection() { } // Destructor

// --- SETTERS --- //
void Intersection::setHit(bool isHit) {
	this->hit = isHit;
}

void Intersection::setDistance(float dist) {
	this->distance = dist;
}

// --- GETTERS --- //
bool Intersection::isHit()			const { return this->hit;		}
float Intersection::getDistance()	const { return this->distance;	}