/*
* INTERSECTION IMPLEMENTATION
*/
#include "Intersection.h"

// --- CONSTRUCTORS --- //
Intersection::Intersection(Rays &ray, Geometry &base) {
	// Take in a ray by reference and an object that IS-A geometry type (can be sphere, triangle, plane)
	// Then build the intersection type
	bool isHit = false;
	float dist = 0.0f;
	//tie(isHit, dist) = base.intersection(ray);
	//					^ would use base class' derived child's intersection function (which uses this)
}