/*
* RAY TRACER MAIN DRIVER PROGRAM
* Programmed by Philip Michael.

-> SOURCES: Princeton University, Dr. S. Mudur, Dr. C. Poullis, M. Millar,
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

static const int WIDTH = 10;
static const int HEIGHT = 10;

// MAIN LOOP
void RayCast(Camera &camera, Scene &scene, vector<Triangle> &tri_vec, vector<Lights> &light_vec, vector<Sphere> &sphere_vec, Plane &plane) {
	// Set up necessary vectors
	vector<Geometry*> shapes;
	vector<Lights*> lights;
	// DEFAULTS TO BE CHANGED ABOVE
	camera.setWidth(WIDTH);
	camera.setHeight(HEIGHT);

	int intersectCount = 0;

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
	for (int i = 0; i < camera.getWidth(); i++) {
		for (int j = 0; j < camera.getHeight(); j++) {
			// Acquire closest intersect from scene
			intersect = scene.closestIntersection(i, j);
			// Verify if we have an intersection
			if (intersect.first->isHit() && intersect.second != nullptr) {
				cout << "Found an intersection as a " << intersect.second->getType() << endl;
				intersectCount++;
			}
			else
				cout << "No intersection." << endl;
		}
	}

	cout << "\n\n--- TOTAL INTERSECTIONS: " << intersectCount << endl;
	cout << "Camera FOV: " << camera.getFOV() << endl;
	cout << "Camera aRatio: " << camera.getAspectRatio() << endl;
	cout << "Camera Focal Length: " << camera.getFocalLength() << endl;

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
	//read_file("../Scenes/scene1.txt", tri_vec, sphere_vec, light_vec, cam, plane);
	//read_file("../Scenes/scene2.txt", tri_vec, sphere_vec, light_vec, cam, plane);
	//read_file("../Scenes/scene3.txt", tri_vec, sphere_vec, light_vec, cam, plane);
	//read_file("../Scenes/scene4.txt", tri_vec, sphere_vec, light_vec, cam, plane);
	//read_file("../Scenes/scene5.txt", tri_vec, sphere_vec, light_vec, cam, plane);
	//read_file("../Scenes/scene6.txt", tri_vec, sphere_vec, light_vec, cam, plane);
	read_file("../Scenes/scene7.txt", tri_vec, sphere_vec, light_vec, cam, plane);

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