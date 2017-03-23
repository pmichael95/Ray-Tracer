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

// --- GETTERS --- //
Camera Scene::getCamera()			 const { return this->camera; }
vector<Geometry*> Scene::getShapes() const { return this->shapes; }
vector<Lights*> Scene::getLights()	 const { return this->lights; }

// --- HELPERS --- //
void Scene::addShape(Geometry *shape) {
	this->shapes.push_back(shape);
}

void Scene::addLight(Lights *light) {
	this->lights.push_back(light);
}

// Checks closest intersections from the camera to a shape and returns a pair of intersection type and a shape
pair<Intersection*, Geometry*> Scene::closestIntersection(int i, int j) {
	// Set up some defaults...
	Geometry* closestShape = nullptr;
	Intersection* closestIntersection = nullptr;

	Rays ray = this->camera.throughPixel(i, j); // Call the camera class' throughPixel with our passed i and j (as needed in camera)

	// Iterate & Create shapes for each of our current shapes
	for (auto *shape : this->shapes) {
		Intersection intersect(ray, *shape); // Check intersection

		// If our intersect is a hit and we haven't found a closest intersection
		// OR or current intersect's distance is strictly LESS than our closest intersection's distance...
		if (intersect.isHit() && (closestIntersection == nullptr || intersect.getDistance() < closestIntersection->getDistance())) {
			// Set our closest intersection to be our intersect that was created with the ray and the current shape
			closestIntersection = &intersect; 
			// Then set the closest shape to be the current shape through iteration
			closestShape = shape;
		}
	}

	// If after all iterations we did not find a close intersection...
	if (closestIntersection == nullptr) {
		// Set it to not be a hit by initializing to default empty constructor
		closestIntersection = &Intersection();
	}

	// At the end, return a struct pair of the closest intersect and its closest shape
	return make_pair(closestIntersection, closestShape);
}


/* ///////// WORK IN PROGRESS, WOULD NEED IF SHIFTED AWAY FROM PAIRS & WILL NEED FOR COLOR
// Checks closest intersections from the camera to a shape and returns a pair of intersection type and a shape
pair<Intersection*, Geometry*> Scene::closestIntersection(int i, int j) {
	float t = -1.0f;
	Geometry* intersectShape = nullptr;
	Rays ray = this->camera.throughPixel(i, j);
	Intersection* intersect = nullptr;
	Intersection* closestIntersect = nullptr;

	// Iterate through the shapes 
	for (auto *shape : this->shapes) {
		intersect = new Intersection(ray, *shape);

		float t_temp = shape->intersection(ray).second;

		if (t < 0 && t_temp > 0) {
			t = t_temp;
			// Pointer assignment for our intersecting shape to the current shape 
			intersectShape = shape;
			closestIntersect = intersect;
		}
		else if (t > 0 && t_temp > 0 && t_temp < t) {
			t = t_temp;
			intersectShape = shape;
			closestIntersect = intersect;
		}
		else {
			closestIntersect = &Intersection();
		}
	}

	if (t > 0) {
		vec3 q = ray.getPoint(t); // Get the 'q' value for color, later
	}

	if (intersectShape != nullptr && closestIntersect != nullptr) {
		cout << "FOUND INTERSECTION -- SCENE" << endl;
		return make_pair(closestIntersect, intersectShape);
	}
	else {
		cout << "NO INTERSECTION -- SCENE" << endl;
		return make_pair(closestIntersect, intersectShape);
	}
}*/

// Begin acquiring the color for every intersected shape
vec3 Scene::trace_color(pair<Intersection*, Geometry*> intersect, int i, int j) {
	// If we didn't acquire a shape through the intersection, return black
	if (intersect.second == nullptr)
		return vec3(0.0f);
	else {
		// Otherwise, begin computing the phong colors
		return this->getColor(vec3(0.0f), intersect, i, j);
	}
}

// Acquire the colors by iterating through each light and calling the respective shape's phong implementation
vec3 Scene::getColor(vec3 q, pair<Intersection*, Geometry*> intersect, int i, int j) {
	vec3 color = intersect.second->getAmbient(); // Acquire ambient color first
	// Go through each light in our lights vector object
	for (Lights *light : lights) {
		// Get the ray's direction which is the light's position - our q vector (0.0f by default)
		vec3 rayDir = light->getPosition() - q; // Get light position relative to passed q vector

		// Acquire the surface point by adding the q vector to the ray's direction as a float
		vec3 surfacePoint = q + rayDir * 0.001f; // Convert to float to get our surface's point

		// Build a new ray that starts from our object's surface point and with the direction that we just computed
		Rays ray = Rays(surfacePoint, rayDir);

		// Compute the phong light
		if (intersect.first == nullptr) {
			// Add the phong lighting color to our existing ambient light that was in the color vector
			color += intersect.second->phong(q, this->lights[j]);
		}
	}
	
	// Clamp the colors strictly to 1 or 0 if they exceed or are less than 1 and 0
	if (color.r > 1.0f) 
		color.r = 1.0f;
	if (color.r < 0.0f) 
		color.r = 0.0f;
	if (color.g > 1.0f) 
		color.g = 1.0f;
	if (color.g < 0.0f) 
		color.g = 0.0f;
	if (color.b > 1.0f) 
		color.b = 1.0f;
	if (color.b < 0.0f) 
		color.b = 0.0f;
	
	// Finally return our color
	return color;
}