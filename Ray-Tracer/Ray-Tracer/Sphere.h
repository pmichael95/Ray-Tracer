/*
* SPHERE GEOMETRIC SHAPE
*/
#ifndef SPHERE_H
#define SPHERE_H
#include "Geometry.h"

class Sphere : public Geometry {
private:
	float radius;
	vec3 center; // In 3D, a point for the center of the sphere
public:
	// --- CONSTRUCTORS --- //
	Sphere() : Geometry(), center(vec3(0.0f)), radius(0.0f) { }
	Sphere(vec3 center, float radius, vec3 ambient, vec3 diffuse, vec3 specular, float alpha);

	~Sphere(); // Destructor

	// --- SETTERS --- //
	void setRadius(float radius);
	void setCenter(vec3 center);

	// --- GETTERS --- //
	float getRadius() const;
	vec3 getCenter() const;
};

#endif