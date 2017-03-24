/*
* RAY TRACER MAIN DRIVER PROGRAM
* Programmed by Philip Michael.

-> SOURCES & REFERENCES: 
			Princeton University, Dr. S. Mudur, Dr. C. Poullis, M. Millar,
			M. Deom, A. Friesen, ohnozzy (GitHub), University of California (Irvine), 
			Caleb Piercy (YouTube), szellmann (GitHub), Alexander Tolmachev (GitHub)

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

// MAIN 
int main() {
	// Create needed variables
	vector<Triangle> tri_vec;
	vector<Lights> light_vec;
	vector<Sphere> sphere_vec;
	Plane plane = Plane();
	Camera cam = Camera();
	Scene scene = Scene();
	const char* fpath = "../Scenes/scene1.txt";

	// Read the input file
	cout << "Reading file for input data ..." << endl;
	read_file(fpath, tri_vec, sphere_vec, light_vec, cam, plane);
	cout << "\nFinished reading file for input data." << endl;
	cout << "Camera width: " << cam.getWidth() << endl;
	cout << "Camera height: " << cam.getHeight() << endl;

	// Populate the scene
	cout << "\nPopulating the Scene object ..." << endl;
	// Triangles
	for (unsigned int i = 0; i < tri_vec.size(); i++) {
		scene.addShape(&tri_vec.at(i));
	}
	// Spheres
	for (unsigned int i = 0; i < sphere_vec.size(); i++) {
		scene.addShape(&sphere_vec.at(i));
	}
	// Lights
	for (unsigned int i = 0; i < light_vec.size(); i++) {
		scene.addLight(&light_vec.at(i));
	}
	// Add the only plane at the end
	scene.addShape(&plane); 
	cout << "\nFinished populating the Scene object." << endl;

	// Set up necessary CImg variables
	using namespace cimg_library;
	cout << "\nInitializing CImg ... " << endl;
	CImg<float> image(cam.getWidth(), cam.getHeight(), 1, 3, 0);
	cout << "\nFinished initializing CImg." << endl;

	// Render time!
	cout << "\nComputing & rendering image ..." << endl;
	Rays ray;
	vec3 color;
	// i, j loop using CImg library
	cimg_forXY(image, x, y) {
		// Shoot a ray through each pixel x, y
		ray = cam.throughPixel(y, x); 
		// Compute the color each time with the ray
		color = scene.trace_color(ray, 0);
		image(x, y, 0) = color.r * 255;
		image(x, y, 1) = color.g * 255;
		image(x, y, 2) = color.b * 255;
	}
	image.save("../render.bmp");
	cout << "\nFinished computing & rendering." << endl;

	// Display it and wait
	CImgDisplay display(image, "Render");
	while (!display.is_closed()) {
		display.wait();
	}

	system("PAUSE");
	return 0;
}