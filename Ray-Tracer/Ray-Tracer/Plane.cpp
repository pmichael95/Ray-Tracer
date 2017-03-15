/*
* PLANE CLASS IMPLEMENTATION
*/
#include "Plane.h"

// --- CONSTRUCTORS --- //
// The primary constructor will also instantiate based off the Base Class: Geometry

Plane::Plane(vec3 normal, vec3 point, vec3 ambient, vec3 diffuse, vec3 specular, float alpha) 
	: Plane(vec4(normal, -dot(normal, point)), ambient, diffuse, specular, alpha) { }

Plane::Plane(vec4 dimensions, vec3 ambient, vec3 diffuse, vec3 specular, float alpha)
	: Geometry(ambient, diffuse, specular, alpha), dimensions(dimensions) { }

Plane::Plane(vec3 normal, vec3 point) 
	: Plane(normal, point, vec3(0.0f), vec3(0.0f), vec3(0.0f), 0.0f) { }

Plane::~Plane() { } // Default destructor

// --- SETTER --- //
void Plane::setDimensions(vec4 dimensions) { this->dimensions = dimensions; }

// --- GETTER --- //
vec4 Plane::getDimensions() const { return this->dimensions; }