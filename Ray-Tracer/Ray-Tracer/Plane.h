/*
* PLANE THAT INHERITS FROM GEOMETRY
*/
#ifndef PLANE_H
#define PLANE_H
#include "CommonIncludes.h"
#include "Geometry.h"
#include <vector>

class Plane : public Geometry {
private:
	vec4 dimensions; // The dimensions of the plane
public:
	// --- CONSTRUCTORS --- //
	Plane() : dimensions(vec4(0.0f)), Geometry() {}; // Empty dimensions & call base class to empty
	Plane(vec3 normal, vec3 point, vec3 ambient, vec3 diffuse, vec3 specular, float alpha);
	Plane(vec4 dimensions, vec3 ambient, vec3 diffuse, vec3 specular, float alpha);
	Plane(vec3 normal, vec3 point);

	~Plane(); // Destructor

	// --- SETTER --- //
	void setDimensions(vec4 dimensions);

	// --- GETTER --- //
	vec4 getDimensions() const;
	virtual string getType() const { return "Plane"; }

	// --- HELPERS --- //
	virtual pair<bool, float> intersection(Rays ray);
						// Virtual intersection function since we'd also be calling it through Triangle (the triangle forms a plane to check intersection)
};

#endif
