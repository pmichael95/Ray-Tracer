/*
* SCENE FILE IMPLEMENTATION
*/
#include "Scene.h"

// Destructor
Scene::~Scene() { }

// --- SETTERS --- //
void Scene::setCamera(Camera &camera) {
	this->camera = camera;
}

void Scene::setShapes(vector<Geometry*> shape) {
	this->shapes = shape;
}

void Scene::setLights(vector<Lights*> lights) {
	this->lights = lights;
}

void Scene::setQ(vec3 q) {
	this->q = q;
}

// --- GETTERS --- //
Camera Scene::getCamera()			 const { return this->camera; }
vector<Geometry*> Scene::getShapes() const { return this->shapes; }
vector<Lights*> Scene::getLights()	 const { return this->lights; }
vec3 Scene::getQ()					 const { return this->q; }

// --- HELPERS --- //
void Scene::addShape(Geometry *shape) {
	this->shapes.push_back(shape);
}

void Scene::addLight(Lights *light) {
	this->lights.push_back(light);
}

// Trace a ray for the colors
vec3 Scene::trace_color(Rays &ray, int d) {
	// Return background colour if we've recurred d_max times
	//if (d > 100)
		//return vec3(0.0f); // Default to stop recursion - NOT NECESSARY ANYMORE

	// Check for the closest intersection
	Geometry* intersectingObject = closestIntersection(ray, q); // Cast ray to q, the surface point

	// If we didn't get an intersection
	if (intersectingObject == nullptr) 
		return vec3(0.0f); // Empty color black

	// Return the color returned from getColor helper function
	return getColor(q, intersectingObject);
}

// Returns the surface point of the closest intersection
Geometry* Scene::closestIntersection(Rays& ray, vec3& q) {
	float t = -1; // Initialize to < 0 for conditions
	Geometry* intersectShape = nullptr; // By default, null (no intersected shape)

	// Loop through every shape in our shapes vector
	for (Geometry* shape : this->shapes) {
		// Get the distance from the intersection
		float temp = shape->intersection(ray).second;

		// If our current distance is < 0 and the returned distance is > 0
		if (t < 0 && temp > 0) {
			// Set the intersect shape to this one
			intersectShape = shape;
			// Set the current distance to the returned one
			t = temp;
		}
		// Otherwise, if our current distance & returned distance > 0 but current distance > returned distance
		else if (t > 0 && temp > 0 && temp < t) {
			// Set the intersected shape to be the current one
			intersectShape = shape;
			// And set the current distance to the returned one
			t = temp;
		}
	} // End loop

	// If we ended up with a distance (not the default -1)
	if (t > 0)
		q = ray.getPoint(t); // Get the point from the ray's hit

	// Finally return the intersected shape (if any)
	return intersectShape;
}

// Returns a vec3 color based on shape and lights
vec3 Scene::getColor(vec3 q, Geometry* shape) {
	// Acquire the ambient color first
	vec3 color = shape->getAmbient();
	// Go through every light in our lights vector
	for (Lights *light : this->lights) {
		// Get the ray direction based off the light's position and the q
		vec3 direction = light->getPosition() - q;
		// Get a point on the shape
		vec3 point = q + direction;
		// Build a ray object relative to the surface's point and with the established direction
		Rays ray = Rays(point, direction);

		// If we didn't intersect...
		if (closestIntersection(ray, vec3(0)) == nullptr)
			// Find the color with the shape's respective phong function
			color += shape->phong(q, light);
	}

	// --- STANDARDIZE THE COLORS! Anything > 1 -> 1, anything < 0 -> 0
	if (color.r > 1.0) 
		color.r = 1.0;
	if (color.r < 0.0) 
		color.r = 0.0;
	if (color.g > 1.0) 
		color.g = 1.0;
	if (color.g < 0.0) 
		color.g = 0.0;
	if (color.b > 1.0) 
		color.b = 1.0;
	if (color.b < 0.0) 
		color.b = 0.0;

	// Return final color
	return color;
}
