/*
* FILE READER (Function helper)
-> Reads an input file and builds the appropriate objects
*/
#ifndef FILEREADER_H
#define FILEREADER_H

#pragma warning(disable:4996)

#include <string>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <exception>
#include <cstring>

// INCLUDE ALL SHAPES AND FUNDAMENTALS
#include "Triangle.h"
#include "Sphere.h"
#include "Plane.h"
#include "Camera.h"
#include "Lights.h"

using namespace std;

/*
* READ FILE METHOD
-> Processes the input file specified through fpath
	Then builds objects according to the file (populates vectors for the shapes + lights)
NOTE: The call is from the main() method which pre-emptively constructed empty vectors for each shape & lights, and also passes camera and plane 
*/
void readFile(const char* fpath, vector<Triangle> &triangle, vector<Sphere> &sphere, vector<Lights> &light, Camera &camera, Plane &plane) {
	FILE *file;
	int numElements, currLine;
	// First line is camera
	try {
		file = fopen(fpath, "r"); // Open the file as read-only

		// Check to make sure file was openable/locatable
		if (file == NULL) {
			cerr << "ERROR::UNABLE_TO_OPEN_FILE" << endl;
			system("exit");
		}
		else {
			fscanf(file, "%d", &numElements); // The first line will tell us how many cases we need to go through
			while (true) {
				char str[256];
				string type;
				// Iterate through every 'element' (object)
				// First object is the camera
				int res = fscanf(file, "%s", &str);
				if (res == EOF)
					break; // End of file reached, quit it
				type = string(str);
				// type now holds a string representing our cases
				// i.e. camera, plane, triangle, sphere, light

				// --- BEGIN CAMERA --- //
				if (type == "camera") {
					// Camera case, has 4 values
					// --- POSITION --- //
					vec3 position;
					float posX, posY, posZ;
					fscanf(file, "%s", &type); // Skip over 'pos:'
					fscanf(file, "%f", &posX);
					fscanf(file, "%f", &posY);
					fscanf(file, "%f", &posZ);
					position = vec3(posX, posY, posZ);

					// --- FOV --- //
					float fov;
					fscanf(file, "%s", &type); // Skip over 'fov:'
					fscanf(file, "%f", &fov); // Now fov = angle in degrees

					// --- FOCAL LENGTH --- //
					float focal;
					fscanf(file, "%s", &type); // Skip over the 'f:'
					fscanf(file, "%f", &focal); // Now focal = focal length of the camera

					// --- ASPECT RATIO --- //
					float aRatio;
					fscanf(file, "%s", &type); // Skip over the 'a'
					fscanf(file, "%f", &aRatio); // Now aRatio = aspect ratio of the camera

					// --- BUILD CAMERA OBJECT --- //
					// Call setters
					camera.setPos(position);
					camera.setFOV(fov);
					camera.setAspectRatio(aRatio);
					camera.setFocalLength(focal);
					
					// --- END CAMERA --- //
				}
				// --- BEGIN PLANE --- //
				else if (type == "plane") {
					// Plane has 6 values
					// --- NORMAL --- //
					fscanf(file, "%s", &type); // Skip over 'nor:'
					vec3 normal;
					float normX, normY, normZ;
					fscanf(file, "%f", &normX);
					fscanf(file, "%f", &normY);
					fscanf(file, "%f", &normZ);
					normal = vec3(normX, normY, normZ);

					// --- POSITION OF A POINT --- //
					fscanf(file, "%s", &type); // Skip over 'pos:'
					vec3 point;
					float pX, pY, pZ;
					fscanf(file, "%f", &pX);
					fscanf(file, "%f", &pY);
					fscanf(file, "%f", &pZ);
					point = vec3(pX, pY, pZ);

					// --- AMBIENT --- //
					fscanf(file, "%s", &type); // Skip over 'amb:'
					vec3 amb;
					float aX, aY, aZ;
					fscanf(file, "%f", &aX);
					fscanf(file, "%f", &aY);
					fscanf(file, "%f", &aZ);
					amb = vec3(aX, aY, aZ);

					// --- DIFFUSE --- //
					fscanf(file, "%s", &type); // Skip over 'dif:'
					vec3 dif;
					float dX, dY, dZ;
					fscanf(file, "%f", &dX);
					fscanf(file, "%f", &dY);
					fscanf(file, "%f", &dZ);
					dif = vec3(dX, dY, dZ);

					// --- SPECULAR --- //
					fscanf(file, "%s", &type); // Skip over 'spe:'
					vec3 spe;
					float sX, sY, sZ;
					fscanf(file, "%f", &sX);
					fscanf(file, "%f", &sY);
					fscanf(file, "%f", &sZ);
					spe = vec3(sX, sY, sZ);

					// --- SHININESS --- //
					fscanf(file, "%s", &type); // Skip over 'shi:'
					float alpha;
					fscanf(file, "%f", &alpha); // Now alpha = shininess

					// --- BUILD THE PLANE --- //
					plane = Plane(normal, point, amb, dif, spe, alpha); // Calls its constructor to set all values

					// --- END PLANE --- //
				}
				// --- BEGIN TRIANGLE --- //
				else if (type == "triangle") {
					// Triangle has 7 values

					// --- VERTEX 1 --- //
					fscanf(file, "%s", &type); // Skip over 'v1:'
					vec3 v1;
					float v1x, v1y, v1z;
					fscanf(file, "%f", &v1x);
					fscanf(file, "%f", &v1y);
					fscanf(file, "%f", &v1z);
					v1 = vec3(v1x, v1y, v1z);

					// --- VERTEX 2 --- //
					fscanf(file, "%s", &type); // Skip over 'v2:'
					vec3 v2;
					float v2x, v2y, v2z;
					fscanf(file, "%f", &v2x);
					fscanf(file, "%f", &v2y);
					fscanf(file, "%f", &v2z);
					v2 = vec3(v2x, v2y, v2z);


					// --- VERTEX 2 --- //
					fscanf(file, "%s", &type); // Skip over 'v3:'
					vec3 v3;
					float v3x, v3y, v3z;
					fscanf(file, "%f", &v3x);
					fscanf(file, "%f", &v3y);
					fscanf(file, "%f", &v3z);
					v3 = vec3(v3x, v3y, v3z);

					// --- AMBIENT --- //
					fscanf(file, "%s", &type); // Skip over 'amb:'
					vec3 amb;
					float aX, aY, aZ;
					fscanf(file, "%f", &aX);
					fscanf(file, "%f", &aY);
					fscanf(file, "%f", &aZ);
					amb = vec3(aX, aY, aZ);

					// --- DIFFUSE --- //
					fscanf(file, "%s", &type); // Skip over 'dif:'
					vec3 dif;
					float dX, dY, dZ;
					fscanf(file, "%f", &dX);
					fscanf(file, "%f", &dY);
					fscanf(file, "%f", &dZ);
					dif = vec3(dX, dY, dZ);

					// --- SPECULAR --- //
					fscanf(file, "%s", &type); // Skip over 'spe:'
					vec3 spe;
					float sX, sY, sZ;
					fscanf(file, "%f", &sX);
					fscanf(file, "%f", &sY);
					fscanf(file, "%f", &sZ);
					spe = vec3(sX, sY, sZ);

					// --- SHININESS --- //
					fscanf(file, "%s", &type); // Skip over 'shi:'
					float alpha;
					fscanf(file, "%f", &alpha); // Now alpha = shininess

					// --- BUILD TRIANGLE --- //
					Triangle tri = Triangle(v1, v2, v3, amb, dif, spe, alpha);
					triangle.push_back(tri);

					// --- END TRIANGLE --- //
				}
				// --- BEGIN SPHERE --- //
				else if (type == "sphere") {
					// Sphere has 6 values

					// --- POSITION --- //
					fscanf(file, "%s", &type); // Skip over 'pos:'
					vec3 pos;
					float posX, posY, posZ;
					fscanf(file, "%f", &posX);
					fscanf(file, "%f", &posY);
					fscanf(file, "%f", &posZ);
					pos = vec3(posX, posY, posZ);

					// --- RADIUS --- //
					fscanf(file, "%s", &type); // Skip over 'rad:'
					float rad;
					fscanf(file, "%f", &rad); // Now rad = radius

					// --- AMBIENT --- //
					fscanf(file, "%s", &type); // Skip over 'amb:'
					vec3 amb;
					float aX, aY, aZ;
					fscanf(file, "%f", &aX);
					fscanf(file, "%f", &aY);
					fscanf(file, "%f", &aZ);
					amb = vec3(aX, aY, aZ);

					// --- DIFFUSE --- //
					fscanf(file, "%s", &type); // Skip over 'dif:'
					vec3 dif;
					float dX, dY, dZ;
					fscanf(file, "%f", &dX);
					fscanf(file, "%f", &dY);
					fscanf(file, "%f", &dZ);
					dif = vec3(dX, dY, dZ);

					// --- SPECULAR --- //
					fscanf(file, "%s", &type); // Skip over 'spe:'
					vec3 spe;
					float sX, sY, sZ;
					fscanf(file, "%f", &sX);
					fscanf(file, "%f", &sY);
					fscanf(file, "%f", &sZ);
					spe = vec3(sX, sY, sZ);

					// --- SHININESS --- //
					fscanf(file, "%s", &type); // Skip over 'shi:'
					float alpha;
					fscanf(file, "%f", &alpha); // Now alpha = shininess

					// --- BUILD SPHERE --- //
					Sphere newSphere = Sphere(pos, rad, amb, dif, spe, alpha);
					sphere.push_back(newSphere); // Add the created sphere to the spheres vector

					// --- END SPHERE --- //
				}
				// --- BEGIN LIGHT --- //
				else if (type == "light") {
					// Light has 2 values

					// --- POSITION --- //
					fscanf(file, "%s", &type); // Skip over 'pos:'
					vec3 pos;
					float posX, posY, posZ;
					fscanf(file, "%f", &posX);
					fscanf(file, "%f", &posY);
					fscanf(file, "%f", &posZ);
					pos = vec3(posX, posY, posZ);

					// --- COLOR --- //
					fscanf(file, "%s", &type); // Skip over 'col:'
					vec3 color;
					float cX, cY, cZ;
					fscanf(file, "%f", &cX);
					fscanf(file, "%f", &cY);
					fscanf(file, "%f", &cZ);
					color = vec3(cX, cY, cZ);

					// --- BUILD LIGHT --- //
					Lights newLight = Lights(pos, color);
					light.push_back(newLight); // Add the new light to our light vector

					// --- END LIGHT --- //
				}
				else {
					cerr << "ERROR::UNKNOWN_TYPE_SPECIFIED" << endl;
					system("exit"); // Exit application
				}
			}
		}
		fclose(file); // Close file
	}
	catch (exception e) {
		cerr << "ERROR::INPUT_FILE_NOT_READABLE" << endl;
		system("exit"); // Exit application
	}
}

#endif