/*
* CLASS REPRESENTING THE RAYS
-> A ray starts from Camera and goes to infinity through objects.
*/
#ifndef RAYS_H
#define RAYS_H
#include "CommonIncludes.h"

class Rays {
private:
	vec3 origin; // The coordinates of origin (camera)
	vec3 direction; // The vector for the direction
public:
	// --- CONSTRUCTORS --- //
	Rays() : origin(vec3(0.0f, 0.0f, 0.0f)), direction(vec3(0.0f, 0.0f, 0.0f)) { }; 
	Rays(vec3 m_origin, vec3 m_direction) : origin(m_origin), direction(m_direction) { };

	~Rays(); // Destructor

	// --- SETTERS --- //
	void setOrigin(vec3 origin); 
	void setDirection(vec3 direction);

	// --- GETTERS --- //
	vec3 getOrigin() const;
	vec3 getDirection() const;

	// --- HELPERS --- //
	vec3 getPoint(float t); // Gets a point that the ray hit
};

#endif