/*
* INTERSECTION CLASS HEADER
-> Here we process the intersections between rays and surfaces
*/
#include "CommonIncludes.h"
#include "Rays.h"
#include "Geometry.h"

class Intersection {
private:
	bool hit; // To determine if a hit (intersection) acquired
	float distance; // Distance computed
public:
	// --- CONSTRUCTORS --- //
	Intersection() : hit(false), distance(0.0f) { }
	Intersection(Rays &ray, Geometry &base);

	~Intersection(); // Destructor

	// --- SETTERS --- //
	void setHit(bool hit);
	void setDistance(float dist);

	// --- GETTERS --- //
	bool isHit() const; // Check if we did hit an intersection
	float getDistance() const; // Returns a numerical float distance from the ray to the object that intersected
};