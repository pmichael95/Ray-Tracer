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
	Plane* plane; // A triangle also holds a plane since the 2D surface can be considered a plane
public:
	// --- CONSTRUCTORS --- //
	Triangle() : vertices(vector<vec3>()), Geometry() { } // Empty vertices & call base class to empty
	Triangle(vec3 v1, vec3 v2, vec3 v3, vec3 ambient, vec3 diffuse, vec3 specular, float alpha);

	~Triangle(); // Destructor

	// --- SETTER --- //
	void setVertices(vector<vec3> vertices);
	void setPlane(Plane* plane);

	// --- GETTER --- //
	vector<vec3> getVertices() const;
	Plane* getPlane();

	// --- HELPERS --- //
	vec3 getVertex(int index); // Returns a vec3 vertex based on passed index
	void setVertex(int index, vec3 vertex); // Sets a vertex to replace one based on index
	virtual pair<bool, float> intersection(Rays ray); // The triangle's intersection case
	pair<vector<vec2>, vec2> projection(vec3 &intersect_point); // A projection of the triangle in 2D
	float area(vec2 p1, vec2 p2, vec2 p3);

	static const int TRIANGLE_EDGES = 3;
};

#endif