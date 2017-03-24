/*
* CAMERA IMPLEMENTATION FILE
*/
#include "Camera.h"

// --- CONSTRUCTORS --- //
Camera::Camera(vec3 pos, float fov, float focalLength, float aRatio)
	: position(pos), fov((PI / 180.0f) * fov), focalLength(focalLength), aspectRatio(aRatio) 
{ 
	this->updateDimensions();
	// The x FOV is 2 * arcTan((width/2) / focalLength)
	xFOV = 2 * std::atan((this->width / 2) / this->focalLength);
}

Camera::~Camera() { } // Destructor

// --- SETTERS --- //
void Camera::setFOV(float fov) {
	this->fov = fov;
	this->updateDimensions(); // Now that we changed the FOV, need to update the image dimensions
}
void Camera::setAspectRatio(float aRatio) {
	this->aspectRatio = aRatio;
	this->updateDimensions(); // Now that we changed the aspect ratio, need to update the image dimensions
}
void Camera::setFocalLength(float focal) {
	this->focalLength = focal;
	this->updateDimensions(); // Now that we changed the focal length, need to update the image dimensions
}
void Camera::setPos(vec3 pos)				{ this->position	= pos;		}
void Camera::setWidth(float width) { 
	this->width	= width;
}
void Camera::setHeight(float height) { 
	this->height = height;
}

// --- GETTERS --- //
vec3 Camera::getPosition()		const { return this->position;		}
float Camera::getFOV()			const { return this->fov;			}
float Camera::getAspectRatio()	const { return this->aspectRatio;	}
float Camera::getFocalLength()	const { return this->focalLength;	}
float Camera::getWidth()		const { return this->width;			}
float Camera::getHeight()		const { return this->height;		}

// --- HELPERS --- //
// Updates the camera image dimensions on need
void Camera::updateDimensions() {
	// Set the height as 2fov * tan(fov/2)
	this->height	= 2 * focalLength * std::tan((fov/2));
	// Set the width as aspect ratio * height
	this->width		= aspectRatio * this->height;
}

// Calculate a ray through the pixel in world coordinates
Rays Camera::throughPixel(int i, int j) {
	// Compute new angles
	float yAngle = this->fov / 2;
	float xAngle = this->xFOV / 2;

	// Find new x and y coordinate values
	float newX = this->focalLength * std::tan(xAngle) * ((j - (this->width / 2)) / (this->width / 2));
	float newY = this->focalLength * std::tan(yAngle) * (((this->height / 2) - i) / (this->height / 2));

	// Now send the ray
	// Ray is: (position, [newX, newY, - focal])
	return Rays(this->getPosition(), vec3(newX, newY, -this->focalLength));
}