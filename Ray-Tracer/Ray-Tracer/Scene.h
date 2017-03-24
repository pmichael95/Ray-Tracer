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

class Scene {
private:
	Camera camera; // Camera object for the scene
	vector<Geometry*> shapes; // All shapes in the scene
	vector<Lights*> lights; // All lights in the scene
	vec3 q; // q to pass around for color
public:
	// --- CONSTRUCTORS --- //
	Scene() : camera(), shapes(vector<Geometry*>()), lights(vector<Lights*>()) { }
	Scene(Camera &camera) : camera(camera) { }

	~Scene(); // Destructor

			  // --- SETTERS --- //
	void setCamera(Camera &camera);
	void setShapes(vector<Geometry*> shapes);
	void setLights(vector<Lights*> lights);
	void setQ(vec3 q);

	// --- GETTERS --- //
	Camera getCamera() const;
	vector<Geometry*> getShapes() const;
	vector<Lights*> getLights() const;
	vec3 getQ() const;

	// --- HELPERS --- //
	void addShape(Geometry* shape);
	void addLight(Lights* light);
	// Trace the object colors of the scene
	vec3 trace_color(Rays &ray, int d);
	// Closest intersecting object with passed ray
	Geometry* closestIntersection(Rays &ray, vec3 &q);
	// Get the color for trace_color
	vec3 getColor(vec3 q, Geometry* shape);
};

#endif