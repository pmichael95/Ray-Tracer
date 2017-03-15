/*
* TRIANGLE CLASS IMPLEMENTATION
*/
#include "Triangle.h"

// --- CONSTRUCTORS --- //
Triangle::Triangle(vec3 v1, vec3 v2, vec3 v3, vec3 ambient, vec3 diffuse, vec3 specular, float alpha) 
	: Geometry(ambient, diffuse, specular, alpha) // Set the base class
{
	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);
}

Triangle::~Triangle() { } // Default destructor

// --- SETTER --- //
void Triangle::setVertices(vector<vec3> vertices) {
	for (int i = 0; i < vertices.size(); i++) {
		this->vertices.push_back(vertices[i]); // Iterate through all of passed vertices to push to member
	}
}

// --- GETTER --- //
vector<vec3> Triangle::getVertices() const { return this->vertices; }

// --- HELPERS --- //
vec3 Triangle::getVertex(int index) {
	if (index > this->vertices.size() || index < 0)
		cerr << "ERROR::UNKNOWN_INDEX_PASSED_FOR_GET_VERTEX" << endl;
	else 
		return this->vertices[index];

	return vec3(0.0f); // If we don't reach the else, return an empty vec3
}

void Triangle::setVertex(int index, vec3 vertex) {
	if (index < this->vertices.size() || index < 0)
		cerr << "ERROR::UNKNOWN_INDEX_PASSED_FOR_SET_VERTEX" << endl;
	else
		this->vertices[index] = vertex;
}