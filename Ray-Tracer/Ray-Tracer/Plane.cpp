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
	float neg_pos_dot_n = -(dot(this->getPos(), this->getNormal()));

	// Check to see if there is an intersection
	if (n_dot_dir == 0.0f) {
		//cout << "NO INTERSECTION -- PLANE" << endl;
		return make_pair(false, -1);
	}
	else {
		//cout << "FOUND INTERSECTION -- PLANE" << endl;
		return make_pair(true, -((n_dot_o + neg_pos_dot_n) / n_dot_dir));
	}
}

// Phong lighting implementation
vec3 Plane::phong(vec3 q, Lights* light) {
	vec3 l = light->getPosition() - q; // Light position relative to obj
	// Position dot the normal, and get a max in abs
	float l_dot_n = std::max(dot(l, normalize(this->getNormal())), 0.0f);
	// d is the length of the position
	float d = length(l);
	float d2 = pow(d, 2);

	// Set the attenuation factor
	float atten_denom = 1 + 0.2f * d + d2;
	float atten = 1 / atten_denom;

	// Return (light color + diffuse color) * L.N * attenuation -> color vector!
	return (light->getColor() + this->getDiffuse()) * l_dot_n * atten;
}