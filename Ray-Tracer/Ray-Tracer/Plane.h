// PLANE CLASS
// Used as stand-alone but also for Triangle
#ifndef PLANE_H
#define PLANE_H
#include "CommonIncludes.h"
#include "Geometry.h"
#include <vector>

class Plane : public Geometry {
private:
	vec3 normal; // Plane's normal vector
	vec3 pos; // Position/point on plane
public:
	// --- CONSTRUCTORS --- //
	Plane() : normal(vec3(0.0f)) { }
	Plane(vec3 normal, vec3 pos, vec3 ambient, vec3 diffuse, vec3 specular, float alpha)
		: normal(normalize(normal)), pos(pos), Geometry(ambient, diffuse, specular, alpha) { }
	Plane(vec3 normal, vec3 pos)
		: normal(normalize(normal)), pos(pos) { }

	~Plane(); // Destructor

	// --- SETTERS --- //
	void setNormal(vec3 normal);
	void setPos(vec3 pos);
	
	// --- GETTERS --- //
	vec3 getNormal() const;
	vec3 getPos() const;

	// --- HELPERS --- //
	virtual pair<bool, float> intersection(Rays ray);
	virtual string getType() const { return "Plane"; }
};

#endif