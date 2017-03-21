/*
* CAMERA IMPLEMENTATION FILE
*/
#include "Camera.h"

// --- CONSTRUCTORS --- //
Camera::Camera(vec3 pos, float fov, float focalLength, float aRatio)
	: position(pos), fov((PI / 180.0f) * fov), focalLength(focalLength), aspectRatio(aRatio) 
{ 
	this->updateImgDim();
	// The x FOV is 2 * arcTan((width/2) / focalLength)
	fov_x = 2 * std::atan((this->width / 2) / this->focalLength);
}

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
// Updates the camera image dimensions on need
void Camera::updateImgDim() {
	// Set the height as 2fov * tan(fov/2)
	this->height	= 2 * focalLength * std::tan(fov/2);
	// Set the width as aspect ratio * height
	this->width		= aspectRatio * this->height;
}

////////////
// --- PENDING TO BE REMOVED IF NOT NEEDED --- //
// Return a 2D pixel coordinate
vec2 Camera::getPixelCoord2D(int i, int j) {
	// First need to make sure it's within the bounds
	// x and y both need to be greater than or equal to 0 
	// They also need to be strictly less than our maximum x and y dimensions (width and height)
	if ((i >= 0 && i < this->width) && (j >= 0 && j < this->height)) {
		// Then recalculate
		float newX = this->width  * (static_cast<float>(i) / this->width); // Our new x is the width  * (x/max x size)
		float newY = this->height * (static_cast<float>(j) / this->height); // Our new y is the height * (y/max y size)
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

///////////////////////////////////////////////////////////////////

// Calculate a ray through the pixel in world coordinates
Rays Camera::throughPixel(int i, int j) {
	// Compute new angles
	float yAngle = this->fov / 2;
	float xAngle = this->fov_x / 2;

	// Find new x and y coordinate values
	float newX = this->focalLength * std::tan(xAngle) * ((j - (this->width / 2)) / (this->width / 2));
	float newY = this->focalLength * std::tan(yAngle) * (((this->height / 2) - i) / (this->height / 2));

	// Now send the ray
	// Ray is: (position, [newX, newY, - focal])
	return Rays(this->getPosition(), vec3(newX, newY, -this->focalLength));
}