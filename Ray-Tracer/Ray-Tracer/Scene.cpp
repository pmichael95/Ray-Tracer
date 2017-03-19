/*
* SCENE FILE IMPLEMENTATION
*/
#include "Scene.h"

// Destructor
Scene::~Scene() {
	// Delete camera
	delete this->camera;
	camera = nullptr;

	// Delete all shapes
	for (int i = 0; i < this->shapes.size(); i++) {
		delete shapes[i];
		shapes[i] = nullptr;
	}

	// Delete all lights
	for (int j = 0; j < this->lights.size(); j++) {
		delete lights[j];
		lights[j] = nullptr;
	}
}

// --- SETTERS --- //
void Scene::setCamera(Camera &camera) {
	this->camera = &camera;
}

void Scene::setShapes(vector<Geometry*> shape) {
	this->shapes = shape;
}

void Scene::setLights(vector<Lights*> lights) {
	this->lights = lights;
}

// --- GETTERS --- //
Camera* Scene::getCamera()			 const { return this->camera; }
vector<Geometry*> Scene::getShapes() const { return this->shapes; }
vector<Lights*> Scene::getLights()	 const { return this->lights; }

// --- HELPERS --- //
void Scene::addShape(Geometry* shape) {
	this->shapes.push_back(shape);
}

void Scene::addLight(Lights* light) {
	this->lights.push_back(light);
}

// Checks closest intersections from the camera to a shape and returns a pair of intersection type and a shape
pair<Intersection*, Geometry*> Scene::closestIntersection(int i, int j) {
	Geometry* closestShape = nullptr;
	Intersection* closestIntersection = nullptr;
	Rays ray = this->camera->throughPixel(i, j); // Call the camera class' throughPixel with our passed i and j (as needed in camera)

	// Iterate & Create shapes for each of our current shapes
	for (Geometry* shape : this->shapes) {
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
		// Set it to not be a hit by initializing the variables to their defaults
		closestIntersection->setDistance(0.0f);
		closestIntersection->setHit(false);
	}

	// At the end, return a struct pair of the closest intersect and its closest shape
	return std::make_pair(closestIntersection, closestShape);
}