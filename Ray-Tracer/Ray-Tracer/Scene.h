/*
* SCENE HEADER FILE
-> Symbolizes the 'scene' of the image
*/
#ifndef SCENE_H
#define SCENE_H
#include "CommonIncludes.h"
#include "Geometry.h"
#include "Lights.h"
#include "Camera.h"
#include "Intersection.h"

// For no circular dependence
/*
class Geometry;
class Lights;
class Camera;
class Intersection;
*/

class Scene {
private:
	Camera* camera;
	vector<Geometry*> shapes;
	vector<Lights*> lights;
public:
	// --- CONSTRUCTORS --- //
	Scene() : camera(nullptr), shapes(vector<Geometry*>()), lights(vector<Lights*>()) { }
	Scene(Camera &camera) : camera(&camera) { }

	~Scene(); // Destructor

	// --- SETTERS --- //
	void setCamera(Camera &camera);
	void setShapes(vector<Geometry*> shapes);
	void setLights(vector<Lights*> lights);

	// --- GETTERS --- //
	Camera* getCamera() const;
	vector<Geometry*> getShapes() const;
	vector<Lights*> getLights() const;

	// --- HELPERS --- //
	void addShape(Geometry* shape);
	void addLight(Lights* light);
	pair<Intersection*, Geometry*> closestIntersection(int i, int j);
};

#endif