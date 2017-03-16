/*
* LIGHTS CLASS HEADER
-> Defines lighting for the ray casting
*/
#ifndef LIGHTS_H
#define LIGHTS_H

#include "CommonIncludes.h"

class Lights {
private:
	// Attributes for light is the position of the light source and the color
	vec3 position; 
	vec3 color;
public:
	// --- CONSTRUCTORS --- //
	Lights() : position(vec3(0.0f)), color(vec3(0.0f)) { }
	Lights(vec3 pos, vec3 col) : position(pos), color(col) { }
	~Lights() { } // Destructor

	// --- SETTERS --- //
	void setPosition(vec3 pos);
	void setColor(vec3 color);

	// --- GETTERS --- //
	vec3 getPosition()	const;
	vec3 getColor()		const;
};

#endif