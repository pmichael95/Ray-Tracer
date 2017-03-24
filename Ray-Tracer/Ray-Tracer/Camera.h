/*
* CAMERA CLASS
-> The user's Field Of View.
	- Holds a position and orientation (as vec3 in 3D space)
	- Determines rays
*/
#ifndef CAMERA_H
#define CAMERA_H
#include "CommonIncludes.h"
#include "Rays.h" // Will need the rays since direction and origin need to be passed

// Instance pi
#define PI 3.14159265

class Rays;

class Camera {
private:
	// --- CAMERA VARIABLES --- //
	vec3 position; // Camera pos
	float fov; // Camera field of view
	float aspectRatio; // Camera aspect ratio
	float focalLength; // Camera's visible focal length
	float xFOV; // x fov value

	// --- WIDTH/HEIGHT --- //
	float width; // Width for scene
	float height; // Height for scene
public:
	// --- CONSTRUCTORS --- //
	Camera() : position(vec3(0.0f)), fov(0.0f), aspectRatio(0.0f), focalLength(0.0f) { }
	Camera(vec3 pos, float fov, float focalLength, float aRatio);

	~Camera(); // Destructor

	// --- SETTERS --- //
	void setPos(vec3 pos);
	void setFOV(float fov);
	void setAspectRatio(float aRatio);
	void setFocalLength(float focal);
	void setWidth(float width);
	void setHeight(float height);

	// --- GETTERS --- //
	vec3 getPosition()		const;
	float getFOV()			const;
	float getAspectRatio()	const;
	float getFocalLength()	const;
	float getWidth()		const;
	float getHeight()		const;


	// --- HELPERS --- //
	void updateDimensions(); // Updates the image's plane dimensions based on focal length and aspect ratio
	Rays throughPixel(int i, int j); // Compute a ray through the pixel passed by x and y as a Rays object
};

#endif