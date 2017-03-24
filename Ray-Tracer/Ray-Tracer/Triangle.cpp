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

// TRIANGLE INTERSECTION CASE
// Source from: https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle
pair<bool, float> Triangle::intersection(Rays ray) {
	this->plane = this->getPlane(); // Construct plane to get the intersection
	const float kEpsilon = 1e-8; // Essentially close to 0
	vec3 n = normalize(this->plane->getNormal()); // Get the plane's normal
	vec3 dir = ray.getDirection(); // Get the ray direction

	// Get each vertex
	vec3 v0 = this->getVertex(0);
	vec3 v1 = this->getVertex(1);
	vec3 v2 = this->getVertex(2);

	// Create a denomenator by dot(n, n)
	float denom = dot(n, n);

	// Step 1:
	// Check if ray and plane are ||
	float n_dot_dir = dot(n, dir);
	if (abs(n_dot_dir) < kEpsilon) {
		return make_pair(false, -1);
	}

	// Compute d parameter using equation 2
	float d = dot(n, v0);

	// Compute t using equation 3
	float n_dot_orig = dot(n, ray.getOrigin());
	float t = (n_dot_orig + d) / n_dot_dir;

	// Check if triangle is behind ray
	if (t < 0)
		return make_pair(false, -1);

	// Compute the intersection point using equation 1
	vec3 p = ray.getPoint(t);

	// Inside-outside test
	vec3 c;

	// Edge #0
	vec3 edge0 = v1 - v0;
	vec3 vp0 = p - v0;
	c = cross(edge0, vp0);
	if (dot(n, c) < 0)
		return make_pair(false, -1);

	// Edge 1
	vec3 edge1 = v2 - v1;
	vec3 vp1 = p - v1;
	c = cross(edge1, vp1);
	float u = dot(n, c);
	if (u < 0)
		return make_pair(false, -1);

	// Edge 2
	vec3 edge2 = v0 - v2;
	vec3 vp2 = p - v2;
	c = cross(edge2, vp2);
	float v = dot(n, c);
	if (v < 0)
		return make_pair(false, -1);

	u /= denom;
	v /= denom;

	// Get the intersection of the plane with our ray
	pair<bool, float> planeIntersect = this->plane->intersection(ray); 
	// Save the float inersect to t to return it
	t = planeIntersect.second;

	// Return a pair with our t value
	return make_pair(true, t);
}

// -- MAY BE NEEDED LATER. Triangle 2D projection.
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

// Calculates the area of the triangle. -- MAY BE NEEDED LATER
// Need to handle x/y values since vec2s
/* FORMULA:
A(T) = 1/2 * [ (bx - ax) * (cy - ay) * (cx - ax) * (by - ay) ]
*/
float Triangle::area(vec2 p1, vec2 p2, vec2 p3) {
	// For easier handling...
	float ax = p1.x;
	float ay = p1.y;
	float bx = p2.x;
	float by = p2.y;
	float cx = p3.x;
	float cy = p3.y;

	// Return with formula as stated above
	return ((bx - ax) * (cy - ay) - (cx - ax) * (by - ay)) / 2;
}

// Triangle's phong lighting implementation
vec3 Triangle::phong(vec3 q, Lights* light) {
	// Call plane's phong method to calculate the triangle's
	vec3 l = light->getPosition() - q;
	float l_dot_n = std::max(dot(l, normalize(plane->getNormal())), 0.0f);
	float d = length(l);

	float attenDenom = 1 + 0.2f * d + pow(d, 2);
	float atten = 1 / attenDenom;

	vec3 diffuse = this->getDiffuse();

	return (light->getColor() + diffuse) * l_dot_n * atten;
}