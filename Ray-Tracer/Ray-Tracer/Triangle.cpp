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

// Destructor
Triangle::~Triangle() { 
	delete this->plane;
	this->plane = nullptr;
} 

// --- SETTER --- //
void Triangle::setVertices(vector<vec3> vertices) {
	for (int i = 0; i < vertices.size(); i++) {
		this->vertices.push_back(vertices[i]); // Iterate through all of passed vertices to push to member
	}
}

void Triangle::setPlane(Plane* plane) { this->plane = plane; }

// --- GETTER --- //
vector<vec3> Triangle::getVertices()	const { return this->vertices; }
Plane* Triangle::getPlane() {
	if (this->vertices.size() < 3) {
		cerr << "ERROR::TRIANGLE_VERTICES_NOT_SET" << endl;
		return nullptr; // Should not reach this
	}
	// Create the u and v vectors
	vec3 u = this->vertices[1] - this->vertices[0];
	vec3 v = this->vertices[2] - this->vertices[0];
	// Compute the normal
	vec3 normal = normalize(cross(u, v));
	// Build a new Plane using the normal and the base vertex
	return new Plane(normal, this->vertices[0]);
}

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

pair<bool, float> Triangle::intersection(Rays ray) {
	this->plane = this->getPlane(); // Construct plane to get the intersection
	pair<bool, float> planeIntersect = this->plane->intersection(ray); // Get the intersection of the plane with our ray
	float t = planeIntersect.second; // Save the float inersect t
	vec3 intersectPoint = ray.getPoint(t); // Get the intersection point from the ray

	// If the plane intersect is true..
	if (planeIntersect.first) {
		// Get a projection in 2D
		pair<vector<vec2>, vec2> proj = projection(intersectPoint);
		// Extract the vertices
		vector<vec2> verts = proj.first;
		// Extract the intersection's projection in 2D
		vec2 p = proj.second;

		for (int i = 0; i < TRIANGLE_EDGES; i++) {
			// If the area returns greater than 0
			if (area(verts[i], verts[(i + 1) % TRIANGLE_EDGES], p) >= 0.0f) {
				// Then we have an intersection
				//cout << "FOUND INTERSECTION -- TRIANGLE" << endl;
				return make_pair(true, t);
			}
			else {
				//cout << "NO INTERSECTION -- TRIANGLE" << endl;
				return make_pair(false, -1);
			}
		}
	}

	return make_pair(false, t);
}

pair<vector<vec2>, vec2> Triangle::projection(vec3 &intersect_point) {
	// Set up necessary variables
	vector<vec2> vertexProj;
	vec3 normal = vec3(this->plane->getNormal());
	vec2 intersectProj;

	// Check if we're handling the y/z members
	if (dot(normal, vec3(1.0f, 0.0f, 0.0f)) != 0.0f) {
		for (vec3 vertex : this->vertices) {
			vertexProj.push_back(vec2(vertex.y, vertex.z));
		}
		// Set our intersection 2D point based on this case
		intersectProj = vec2(intersect_point.y, intersect_point.z);
	}
	// Check if we're handling the x/z members
	else if (dot(normal, vec3(0.0f, 1.0f, 0.0f)) != 0.0f) {
		for (vec3 vertex : this->vertices) {
			vertexProj.push_back(vec2(vertex.z, vertex.x));
		}
		// Set our intersection 2D point based on this case
		intersectProj = vec2(intersect_point.z, intersect_point.x);
	}
	// Default: Handle x/y
	else {
		for (vec3 vertex : this->vertices) {
			vertexProj.push_back(vec2(vertex.x, vertex.y));
		}
		// Set our intersection 2D point based on this case
		intersectProj = vec2(intersect_point.x, intersect_point.y);
	}

	// Return the vertex projection and its intersection projection (both vec2)
	return make_pair(vertexProj, intersectProj);
}

// Calculates the area of the triangle.
// Need to handle x/y values since vec2s
/* FORMULA:
A(T) = 1/2 * (-aybx + axby + aycx - bycx - axcy + bxcy)
*/
float Triangle::area(vec2 p1, vec2 p2, vec2 p3) {
	
	float ax = p1.x;
	float ay = p1.y;
	float bx = p2.x;
	float by = p2.y;
	float cx = p3.x;
	float cy = p3.y;

	return ((-ay*bx + ax*by + ay*cx - by*cx - ax*cy + bx*cy)/2);
	//return 0.5 * ((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y));
}

// Triangle's phong lighting implementation
vec3 Triangle::phong(vec3 q, Lights* light) {
	// Call plane's phong method to calculate the triangle's
	return this->plane->phong(q, light);
}