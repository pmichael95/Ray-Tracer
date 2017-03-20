/*
* PLANE CLASS IMPLEMENTATION
*/
#include "Plane.h"

// --- CONSTRUCTORS --- //
// The primary constructor will also instantiate based off the Base Class: Geometry

// A point on the plane and a normal will set the dimensions of the plane as a vec3 by doing normal . point
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

// --- HELPERS --- //
pair<bool, float> Plane::intersection(Rays ray) {
	// The intersection point between a plane (n, d) and a ray (r_0, r') is:
	//	t= - (n . r_0 + d) / ( n . r')
	// n . r' = 0 if no intersect

	vec3 n = vec3(this->getDimensions()); // n = (x, y, z) dimensions for plane
	float d = this->getDimensions().w; // d is the w of plane dimensions
	vec3 o = ray.getOrigin(); // o for the ray's origin 3D coords
	float n_dot_r_prime = dot(n, o);

	float t = 0.0f;

	// Verify the result of n.r'
	// If it's 0, then as above there is no intersection
	if (n_dot_r_prime == 0.0f) {
		cout << "NO INTERSECTION -- PLANE" << endl;
		return make_pair(false, -1);
	}
	else {
		// Result is then -(dot(n, ray origin) + d) / n.r'
		cout << "FOUND INTERSECTION -- PLANE" << endl;
		t = -(dot(n, o) + d) / n_dot_r_prime;
	}

	// Return a pair representing the intersection
	return make_pair(t >= 0, t);
}