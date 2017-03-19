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

static const int xSize = 800;
static const int ySize = 800;

int main() {
	// Set up primary necessary variables
	vector<Triangle> tri_vec;
	vector<Lights> light_vec;
	vector<Sphere> sphere_vec;
	Camera cam;
	Plane plane;

	// Read the input file
	read_file("../Scenes/scene1.txt", tri_vec, sphere_vec, light_vec, cam, plane);
	//read_file("../Scenes/scene2.txt", tri_vec, sphere_vec, light_vec, cam, plane);
	//read_file("../Scenes/scene3.txt", tri_vec, sphere_vec, light_vec, cam, plane);
	//read_file("../Scenes/scene4.txt", tri_vec, sphere_vec, light_vec, cam, plane);
	//read_file("../Scenes/scene5.txt", tri_vec, sphere_vec, light_vec, cam, plane);
	//read_file("../Scenes/scene6.txt", tri_vec, sphere_vec, light_vec, cam, plane);
	//read_file("../Scenes/scene7.txt", tri_vec, sphere_vec, light_vec, cam, plane);

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