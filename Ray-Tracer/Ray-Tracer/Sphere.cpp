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

// --- HELPERS --- //
pair<bool, float> Sphere::intersect(Rays &ray) {
	// --- REFERENCES: https://www.cs.princeton.edu/courses/archive/fall00/cs426/lectures/raycast/raycast.pdf
	// + notes by S. Mudur & C. Poullis on Ray-Sphere intersection
	// --- SETUP ALL NECESSARY VARIABLES
	// Need: origin [from COP] (o), direction (l), radius (r), center (c)
	// Then need to perform some math to find necessary values
	vec3 o = ray.getOrigin();
	vec3 l = ray.getDirection();
	float r = this->getRadius();
	float r2 = pow(r, 2); // r squared
	vec3 c = this->getCenter();
	vec3 o_minus_c = o - c;
	float o_minus_c_dot = dot(o_minus_c, o_minus_c); // dot( o - c,  o - c)
	float l_dot_o_minus_c = dot(l, o_minus_c); // dot(l, o - c)
	float l_dot_o_minus_c_2 = pow(l_dot_o_minus_c, 2); //  dot(l, o - c) ^2
	float l_dot_l = dot(l, l); // dot(l, l)

	// GEOMETRIC METHOD
	// compute the result
	// result of: dot(l, o - c)^2 - dot(l, l) x (dot(o - c, o - c) - r^2)
	float result = l_dot_o_minus_c_2 - l_dot_l * (o_minus_c_dot - r2);

	float t = 0.0f;
	// --------------------------------

	if (result < 0.0f) {
		t = -1; // DID NOT INTERSECT
	}
	else if (result == 0.0f) {
		// Result for t is -dot(l, o - c) / dot(l, l)
		t = -l_dot_o_minus_c / l_dot_l;
	}
	else {
		// Assume result > 0 here
		// Distance is the sqrt of the result
		float dist = sqrt(result);
		// Solve to obtain t1 and t2
		float t1 = (-l_dot_o_minus_c + dist) / l_dot_l;
		float t2 = (-l_dot_o_minus_c - dist) / l_dot_l;
		if ((t1 < 0.0f && t2 >= 0.0f) || (t2 < 0.0f && t1 >= 0.0f)) {
			// Opposite case of the below else if, so return max instead
			t = std::max(t1, t2);
		}
		else if (t1 >= 0.0f && t2 >= 0.0f) {
			// If t1, t2 > 0, return min(t1, t2)
			t = std::min(t1, t2);
		}
		else {
			t = -1; // Default, should not reach [error]
		}
	}

	// Verify if an intersection occured
	bool intersected = false;
	if (t >= 0) // Finally check if our returned t isn't < 0
		intersected = true; // if >= 0, then we intersected

	// Return a pair
	return make_pair(intersected, t);
}