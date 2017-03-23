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

static const int WIDTH = 1212;
static const int HEIGHT = 808;

// MAIN LOOP
void RayCast(Camera &camera, Scene &scene, vector<Triangle> &tri_vec, vector<Lights> &light_vec, vector<Sphere> &sphere_vec, Plane &plane) {
	// DEFAULTS TO BE CHANGED ABOVE
	cout << "\nSetting camera width and height." << endl;
	camera.setWidth(WIDTH);
	camera.setHeight(HEIGHT);

	// Set up CIMG using camera parameters
	cout << "\nSetting up CImg." << endl;
	cimg_library::CImg<float> image(camera.getWidth(), camera.getHeight(), 1, 3, 0);
	
	// Set the scene camera
	cout << "\nInitialized the camera to the scene." << endl;
	scene.setCamera(camera);

	// Counters for intersections
	int intersectCount = 0;
	int sphereICount = 0;
	int triICount = 0;
	int planeICount = 0;

	cout << "\nPopulating essential components." << endl;
	// Populate them
	for (unsigned int i = 0; i < tri_vec.size(); i++) {
		scene.addShape(&tri_vec[i]);
	}
	for (unsigned int i = 0; i < sphere_vec.size(); i++) {
		scene.addShape(&sphere_vec[i]);
	}
	for (unsigned int i = 0; i < light_vec.size(); i++) {
		scene.addLight(&light_vec[i]);
	}
	scene.addShape(&plane); // Finally add our only plane
	
	cout << "\nComputing & rendering ..." << endl;
	// Build the intersect pair and iterate
	pair<Intersection*, Geometry*> intersect;
	for (int i = 0; i < camera.getWidth(); i++) {
		for (int j = 0; j < camera.getHeight(); j++) {
			// Acquire closest intersect from scene
			intersect = scene.closestIntersection(i, j);
			// Verify if we have an intersection
			if (intersect.first->isHit() && intersect.second != nullptr) {
				//cout << "Found an intersection as a " << intersect.second->getType() << endl;
				// Increase overall intersections counter
				intersectCount++;
				if (intersect.second->getType() == "Sphere") {
					// Sphere case, increase its counter and set color
					sphereICount++;
					vec3 color = scene.trace_color(intersect, i, j);
					image(i, j, 0) = color.r * 255.0f;
					image(i, j, 1) = color.g * 255.0f;
					image(i, j, 2) = color.b * 255.0f;

					/* // BLUE DEFAULT
					image(i, j, 0) = 0.0f;
					image(i, j, 1) = 0.0f;
					image(i, j, 2) = 255.0f;
					*/
				}
				else if (intersect.second->getType() == "Triangle") {
					// Triangle case, increase its counter and set color
					triICount++;
					// LIME DEFAULT
					image(i, j, 0) = 0.0f;
					image(i, j, 1) = 255.0f;
					image(i, j, 2) = 0.0f;
					
				}
				else if (intersect.second->getType() == "Plane") {
					// Plane case, increase its counter and set color
					planeICount++;
					vec3 color = scene.trace_color(intersect, i, j);
					image(i, j, 0) = color.r * 255.0f;
					image(i, j, 1) = color.g * 255.0f;
					image(i, j, 2) = color.b * 255.0f;

					/* // YELLOW DEFAULT
					image(i, j, 0) = 255.0f;
					image(i, j, 1) = 255.0f;
					image(i, j, 2) = 0.0f;
					*/
				}
				else {
					// No intersect with shape case
					// Default to red
					image(i, j, 0) = 255.0f;
					image(i, j, 1) = 0.0f;
					image(i, j, 2) = 0.0f;
				}
			}
			else {
				//cout << "No intersection." << endl;
				// Default to red
				image(i, j, 0) = 255.0f;
				image(i, j, 1) = 0.0f;
				image(i, j, 2) = 0.0f;
			}
		}
	}


	// Debug output messages
	cout << "\n\n--- TOTAL INTERSECTIONS: " << intersectCount << endl;
	cout << "==== BREAKDOWN ====\n" << endl;
	cout << "# of Sphere Intersections: " << sphereICount << endl;
	cout << "# of Triangle Intersections: " << triICount << endl;
	cout << "# of Plane Intersections: " << planeICount << endl;
	cout << "\n====================\n" << endl;
	cout << "\n\nCAMERA INFO:\n" << endl;
	cout << "Camera FOV: " << camera.getFOV() << endl;
	cout << "Camera aRatio: " << camera.getAspectRatio() << endl;
	cout << "Camera Focal Length: " << camera.getFocalLength() << endl;
	cout << "Camera Width: " << camera.getWidth() << endl;
	cout << "Camera Height: " << camera.getHeight() << endl;

	// Save our rendered image
	image.save("../render.bmp");

	// Display it and wait until it closes
	cimg_library::CImgDisplay main_display(image, "Render");
	while (!main_display.is_closed()) {
		main_display.wait();
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
	const char* fpath = "../Scenes/scene10.txt";

	// Read the input file
	read_file(fpath, tri_vec, sphere_vec, light_vec, cam, plane);

	// Cast the rays
	RayCast(cam, scene, tri_vec, light_vec, sphere_vec, plane);
	
	// Wait before ending
	system("PAUSE");
	return 0;
}