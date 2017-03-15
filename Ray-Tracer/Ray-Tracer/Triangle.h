/*
* TRIANGLE SHAPE THAT INHERITS FROM GEOMETRY
*/
#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "CommonIncludes.h"
#include "Geometry.h"
#include "Plane.h"
#include <vector>

class Triangle : public Geometry {
private:
	vector<vec3> vertices; // The vertices that make up the triangle
public:
	// --- CONSTRUCTORS --- //
	Triangle() : vertices(vector<vec3>()), Geometry() { } // Empty vertices & call base class to empty
	Triangle(vec3 v1, vec3 v2, vec3 v3, vec3 ambient, vec3 diffuse, vec3 specular, float alpha);

	~Triangle(); // Destructor

	// --- SETTER --- //
	void setVertices(vector<vec3> vertices);

	// --- GETTER --- //
	vector<vec3> getVertices() const;

	// --- HELPERS --- //
	vec3 getVertex(int index); // Returns a vec3 vertex based on passed index
	void setVertex(int index, vec3 vertex); // Sets a vertex to replace one based on index
};

#endif