/*
* INTERSECTION IMPLEMENTATION
*/
#include "Intersection.h"

// --- CONSTRUCTORS --- //
Intersection::Intersection(Rays &ray, Geometry &shape) {
	// Take in a ray by reference and an object that IS-A geometry type (can be sphere, triangle, plane)
	// Then build the intersection type
	tie(this->hit, this->distance) = shape.intersection(ray); // Build (using derived intersection method) an intersection with the passed ray
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