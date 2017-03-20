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

class Rays;

class Camera {
private:
	vec3 position; // Camera pos
	float fov; // Camera field of view
	float aspectRatio; // Camera aspect ratio
	float focalLength; // Camera's visible focal length
	float width; // Width for camera
	float height; // Height for camera
public:
	// --- CONSTRUCTORS --- //
	Camera() : position(vec3(0.0f)), fov(0.0f), aspectRatio(0.0f), focalLength(0.0f), width(800.0f), height(800.0f) { }
	Camera(vec3 pos, float fov, float aRatio);

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
	void updateImgDim(); // Updates the image's plane dimensions based on focal length and aspect ratio
	vec2 getPixelCoord2D(int i, int j); // Returns the pixel coordinate as passed with x and y as a vec2 (2D space)
	vec3 getPixelCoord3D(int i, int j); // Returns the pixel coordinate as passed with x and y as a vec3 (3D space) 
	Rays throughPixel(int i, int j); // Compute a ray through the pixel passed by x and y as a Rays object

	// --- DIMENSIONS --- //
	static const int xSize = 800;
	static const int ySize = 800;
};

#endif