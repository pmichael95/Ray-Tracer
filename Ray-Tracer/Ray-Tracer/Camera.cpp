/*
* CAMERA IMPLEMENTATION FILE
*/
#include "Camera.h"

// --- CONSTRUCTORS --- //
Camera::Camera(vec3 pos, float fov, float aRatio)
	: position(pos), fov(fov), aspectRatio(aRatio), width(800.0f), height(800.0f) { }

Camera::~Camera() { } // Destructor

// --- SETTERS --- //
void Camera::setFOV(float fov) {
	this->fov = fov;
	this->updateImgDim(); // Now that we changed the FOV, need to update the image dimensions
}
void Camera::setAspectRatio(float aRatio) {
	this->aspectRatio = aRatio;
	this->updateImgDim(); // Now that we changed the aspect ratio, need to update the image dimensions
}
void Camera::setFocalLength(float focal) {
	this->focalLength = focal;
	this->updateImgDim(); // Now that we changed the focal length, need to update the image dimensions
}
void Camera::setPos(vec3 pos)				{ this->position	= pos;		}
void Camera::setWidth(float width)			{ this->width		= width;	}
void Camera::setHeight(float height)		{ this->height		= height;	}

// --- GETTERS --- //
vec3 Camera::getPosition()		const { return this->position;		}
float Camera::getFOV()			const { return this->fov;			}
float Camera::getAspectRatio()	const { return this->aspectRatio;	}
float Camera::getFocalLength()	const { return this->focalLength;	}
float Camera::getWidth()		const { return this->width;			}
float Camera::getHeight()		const { return this->height;		}

// --- HELPERS --- //
void Camera::updateImgDim() {
	this->width = this->height * this->aspectRatio; // Width = height * aspect ratio -> NOTE: Width = x
	this->height = this->focalLength * atan(this->fov / 2); // Height = focal length * arcTan(FOV/2) -> NOTE: Height = y
}

// Return a 2D pixel coordinate
vec2 Camera::getPixelCoord2D(int i, int j) {
	// First need to make sure it's within the bounds
	// x and y both need to be greater than or equal to 0 
	// They also need to be strictly less than our maximum x and y dimensions
	if ((i >= 0 && i < xSize) && (j >= 0 && j < ySize)) {
		// Then recalculate
		float newX = this->width  * (static_cast<float>(i) / xSize); // Our new x is the width  * (x/max x size)
		float newY = this->height * (static_cast<float>(j) / ySize); // Our new y is the height * (y/max y size)
		return vec2(newX, newY); // Return the result as a 2D coordinate (x,y)
	}
	else
		cerr << "ERROR::POORLY_PROVIDED_X_AND_Y_VALUES" << endl;

	// Default return (not reached if we provided correct x/y values
	return vec2(0.0f);
}

// Return a 3D pixel coordinate
vec3 Camera::getPixelCoord3D(int i, int j) {
	// To get a 3D coordinate for a pixel, we first get its 2D coordinate (x, y)
	// Then, the Z is -Focal Length
	vec3 coord3D = vec3(this->getPixelCoord2D(i, j), -this->focalLength);

	// Finally, we need to use the camera's position and add it to the result to get
	// a relative 3D coordinate (vec3)
	return this->position + coord3D;
}

// Compute a ray to pass through a pixel
Rays Camera::throughPixel(int i, int j) {
	vec3 pixelCoords = this->getPixelCoord3D(i, j); // First, acquire 3D-space coordinates for the pixel
	vec3 direction = pixelCoords - this->position; // The direction would be determined by simply taking the pixel coords - our position (camera)
	return Rays(pixelCoords, direction); // Return a ray that passes through the pixel with our direction
}