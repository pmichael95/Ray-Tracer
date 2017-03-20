/*
* RAY TRACER MAIN DRIVER PROGRAM
* Programmed by Philip Michael.

-> SOURCES: Princeton University, Dr. S. Mudur, Dr. C. Poullis, 
			M. Deom, A. Friesen, ohnozzy (GitHub), University of California (Irvine), 
			Caleb Piercy (YouTube), szellmann (GitHub), Alexander Tolmachev (GitHub)

A lot of the code can be similar to many of the aforementioned sources'.
(Ray Tracing is popular, too many sources exist.)

COMPILATION INSTRUCTIONS:
	- This project was constructed, built, and compiled with MS Visual Studio 2015 Community.
	- If you wish to compile this project, you will need the following libraries:
				* GLM - OpenGL Mathematics Library (any version that is recent)
				* CIMG - Any version that is recent

		/\ This project can be compiled with versions of Visual Studio from 2008 onwards. /\
*/
#include "CommonIncludes.h"
#include "Triangle.h"
#include "Sphere.h"
#include "Camera.h"
#include "Plane.h"
#include "Lights.h"
#include "Rays.h"
#include "File_Reader.h"
#include "Intersection.h"
#include "Scene.h"

static const int WIDTH = 100;
static const int HEIGHT = 100;

// MAIN LOOP
void RayCast(Camera &camera, Scene &scene, vector<Triangle> &tri_vec, vector<Lights> &light_vec, vector<Sphere> &sphere_vec, Plane &plane) {
	// Set up necessary vectors
	vector<Geometry*> shapes;
	vector<Lights*> lights;

	// Populate them
	for (unsigned int i = 0; i < tri_vec.size(); i++) {
		shapes.push_back(&tri_vec[i]);
	}
	for (unsigned int i = 0; i < sphere_vec.size(); i++) {
		shapes.push_back(&sphere_vec[i]);
	}
	for (unsigned int i = 0; i < light_vec.size(); i++) {
		lights.push_back(&light_vec[i]);
	}
	shapes.push_back(&plane);

	// Set the scene values
	scene.setCamera(camera);
	scene.setLights(lights);
	scene.setShapes(shapes);
	
	// Build the intersect pair and iterate
	pair<Intersection*, Geometry*> intersect;
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			intersect = scene.closestIntersection(i, j);
			if (intersect.first->isHit())
				cout << "Found an intersection." << endl;
			else
				cout << "No intersection." << endl;
		}
	}

	// Memory cleanup, unless already nullptr
	if (intersect.first != nullptr && intersect.second != nullptr) {
		delete intersect.first;
		intersect.first = nullptr;
		delete intersect.second;
		intersect.second = nullptr;
	}
}

int main() {
	// Set up primary necessary variables
	vector<Triangle> tri_vec;
	vector<Lights> light_vec;
	vector<Sphere> sphere_vec;
	Plane plane = Plane();
	Camera cam = Camera();
	Scene scene = Scene();

	// Read the input file
	read_file("../Scenes/scene1.txt", tri_vec, sphere_vec, light_vec, cam, plane);
	//read_file("../Scenes/scene2.txt", tri_vec, sphere_vec, light_vec, cam, plane);
	//read_file("../Scenes/scene3.txt", tri_vec, sphere_vec, light_vec, cam, plane);
	//read_file("../Scenes/scene4.txt", tri_vec, sphere_vec, light_vec, cam, plane);
	//read_file("../Scenes/scene5.txt", tri_vec, sphere_vec, light_vec, cam, plane);
	//read_file("../Scenes/scene6.txt", tri_vec, sphere_vec, light_vec, cam, plane);
	//read_file("../Scenes/scene7.txt", tri_vec, sphere_vec, light_vec, cam, plane);

	RayCast(cam, scene, tri_vec, light_vec, sphere_vec, plane);

	/* MAIN LOOP
	for( int i = 0; i < width; i++){
		for( int j = 0; j < height; j++){
			Rays ray = ConstructRayThroughPixel(camera, i, j);
			Intersection hit = FindIntersection(ray, scene);
			image[i][j] = getColor(hit);
		}
	}
	// -- FROM PRINCETON SLIDES
	*/
	
	// Wait before ending
	system("PAUSE");
	return 0;
}