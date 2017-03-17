/*
* RAY TRACER MAIN DRIVER PROGRAM
* [This project is still a Work in Progress!]
* Programmed by Philip Michael
*/
#include "CommonIncludes.h"
#include "Triangle.h"
#include "Sphere.h"
#include "Camera.h"
#include "Plane.h"
#include "Lights.h"
#include "Rays.h"
#include "File_Reader.h"

int main() {
	// TEST
	vector<Triangle> tri_vec;
	vector<Lights> light_vec;
	vector<Sphere> sphere_vec;
	Camera cam;
	Plane plane;

	read_file("../Scenes/scene1.txt", tri_vec, sphere_vec, light_vec, cam, plane);

	// Wait before ending
	system("PAUSE");
	return 0;
}