/*
* PLANE CLASS IMPLEMENTATION
*/
#include "Plane.h"

// Destructor
Plane::~Plane() { }

// --- SETTERS --- //
void Plane::setNormal(vec3 normal) {
	this->normal = normalize(normal);
}

void Plane::setPos(vec3 pos) {
	this->pos = pos;
}

// --- GETTERS --- //
vec3 Plane::getNormal() const {
	return this->normal;
}

vec3 Plane::getPos() const {
	return this->pos;
}

// --- HELPERS --- //
// INTERSECTION FOR PLANE
// Also relevant for triangle cases
pair<bool, float> Plane::intersection(Rays ray) {
	// Acquire necessary variables
	float n_dot_dir = dot(this->getNormal(), ray.getDirection());
	float n_dot_o = dot(this->getNormal(), ray.getOrigin());
	float d = -(dot(this->getPos(), this->getNormal()));

	// Check to see if there is an intersection
	if (n_dot_dir == 0.0f) {
		cout << "NO INTERSECTION -- PLANE" << endl;
		return make_pair(false, -1);
	}
	else {
		cout << "FOUND INTERSECTION -- PLANE" << endl;
		return make_pair(true, -((n_dot_o + d) / n_dot_dir));
	}
}