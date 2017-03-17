/*
* INPUT FILE READER
*/
#ifndef FILE_READER_H
#define FILE_READER_H

#include <string>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <exception>
#include <cstring>
#include <fstream>

// INCLUDE ALL SHAPES AND FUNDAMENTALS
#include "Triangle.h"
#include "Sphere.h"
#include "Plane.h"
#include "Camera.h"
#include "Lights.h"

using namespace std;

// Helper function that will take in a vector and populate its x/y/z components (by reference)
void readVec3(vec3 &vec, ifstream &input) {
	input >> vec.x;
	input >> vec.y;
	input >> vec.z;
}

// Reads a file and processes it to populate elements
void read_file(const char* fpath, vector<Triangle> &triangle, vector<Sphere> &sphere, vector<Lights> &light, Camera &camera, Plane &plane) {
	string type;
	int numElements;
	ifstream input(fpath);

	if (input.is_open()) {
		input >> numElements; // Read the # of elements for looping
		cout << "Number of elements: " << numElements << endl;

		// Loop until # of elements done
		for (int i = 0; i < numElements; i++) {
			input >> type;
			cout << "Type: " << type << endl;
			
			// --- BEGIN CAMERA --- //
			if (type == "camera") {
				// --- POSITION --- //
				input >> type; // Skip over 'pos:'
				vec3 pos;
				readVec3(pos, input);

				// --- FOV --- //
				input >> type; // Skip over 'fov:'
				float fov;
				input >> fov;

				// --- FOCAL --- //
				input >> type; // Skip over the 'f:'
				float focal;
				input >> focal;

				// --- ASPECT RATIO --- //
				input >> type; // Skip over the 'a:'
				float aRatio;
				input >> aRatio;

				// --- BUILD CAMERA --- //
				camera.setPos(pos);
				camera.setFOV(fov);
				camera.setFocalLength(focal);
				camera.setAspectRatio(aRatio);

				// --- END CAMERA --- //
			}
			// --- BEGIN PLANE --- //
			else if (type == "plane") {
				// --- NORMAL --- //
				input >> type; // Skip over 'nor:'
				vec3 normal;
				readVec3(normal, input);

				// --- POSITION --- //
				input >> type; // Skip over 'pos:'
				vec3 point;
				readVec3(point, input);

				// --- AMBIENT --- //
				input >> type; // Skip over 'amb:'
				vec3 amb;
				readVec3(amb, input);

				// --- DIFFUSE --- //
				input >> type; // Skip over 'dif:'
				vec3 dif;
				readVec3(dif, input);

				// --- SPECULAR --- //
				input >> type; // Skip over 'spe:'
				vec3 spe;
				readVec3(spe, input);

				// --- SHININESS --- //
				input >> type; // Skip over 'shi:'
				float alpha;
				input >> alpha;

				// --- BUILD PLANE --- //
				plane = Plane(normal, point, amb, dif, spe, alpha);

				// --- END PLANE --- //
			}
			// --- BEGIN TRIANGLE --- //
			else if (type == "triangle") {
				// --- VERTEX 1 --- //
				input >> type; // Skip over 'v1:'
				vec3 v1;
				readVec3(v1, input);

				// --- VERTEX 2 --- //
				input >> type; // Skip over 'v2:'
				vec3 v2;
				readVec3(v2, input);

				// --- VERTEX 3 --- //
				input >> type; // Skip over 'v3:'
				vec3 v3;
				readVec3(v3, input);

				// --- AMBIENT --- //
				input >> type; // Skip over 'amb:'
				vec3 amb;
				readVec3(amb, input);

				// --- DIFFUSE --- //
				input >> type; // Skip over 'dif:'
				vec3 dif;
				readVec3(dif, input);

				// --- SPECULAR --- //
				input >> type; // Skip over 'spe:'
				vec3 spe;
				readVec3(spe, input);

				// --- SHININESS --- //
				input >> type; // Skip over 'shi:'
				float alpha;
				input >> alpha;

				// --- BUILD TRIANGLE --- //
				Triangle tri = Triangle(v1, v2, v3, amb, dif, spe, alpha);
				triangle.push_back(tri); // Push it to the vector
				
				// --- END TRIANGLE --- //
			}
			// --- BEGIN SPHERE --- //
			else if (type == "sphere") {
				// --- POSITION --- //
				input >> type; // Skip over 'pos:'
				vec3 pos;
				readVec3(pos, input);

				// --- RADIUS --- //
				input >> type; // Skip over 'rad:'
				float radius;
				input >> radius;

				// --- AMBIENT --- //
				input >> type; // Skip over 'amb:'
				vec3 amb;
				readVec3(amb, input);

				// --- DIFFUSE --- //
				input >> type; // Skip over 'dif:'
				vec3 dif;
				readVec3(dif, input);

				// --- SPECULAR --- //
				input >> type; // Skip over 'spe:'
				vec3 spe;
				readVec3(spe, input);

				// --- SHININESS --- //
				input >> type; // Skip over 'shi:'
				float alpha;
				input >> alpha;

				// --- BUILD SPHERE --- //
				Sphere newSphere = Sphere(pos, radius, amb, dif, spe, alpha);
				sphere.push_back(newSphere); // Add the created sphere to the spheres vector

				// --- END SPHERE --- //
			}
			// --- BEGIN LIGHT --- //
			else if (type == "light") {
				// --- POSITION --- //
				input >> type; // Skip over 'pos:'
				vec3 pos;
				readVec3(pos, input);

				// --- COLOR --- //
				input >> type; // Skip over 'col:'
				vec3 color;
				readVec3(color, input);

				// --- BUILD LIGHT --- //
				Lights newLight = Lights(pos, color);
				light.push_back(newLight); // Add the new light to our light vector

				// --- END LIGHT --- //
			}
		}
	}
	else {
		cerr << "ERROR::UNABLE_TO_OPEN_FILE" << endl;
	}
	// When done, close file
	input.close();
}

#endif