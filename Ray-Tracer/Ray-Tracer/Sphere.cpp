/*
* SPHERE CLASS IMPLEMENTATION (Geometric Shape)
*/
#include "Sphere.h"

// --- CONSTRUCTOR --- //
Sphere::Sphere(vec3 center, float radius, vec3 ambient, vec3 diffuse, vec3 specular, float alpha)
	: Geometry(ambient, diffuse, specular, alpha) // Build from base class
{
	this->center = center;
	this->radius = radius;
}

Sphere::~Sphere() { } // Default destructor

// --- SETTERS --- //
void Sphere::setRadius(float radius)	{ this->radius = radius;	}
void Sphere::setCenter(vec3 center)		{ this->center = center;	}

// --- GETTERS --- //
float Sphere::getRadius()	const { return this->radius; }
vec3 Sphere::getCenter()	const { return this->center; }