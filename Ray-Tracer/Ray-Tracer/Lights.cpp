/*
* LIGHTS FILE IMPLEMENTATION
*/
#include "Lights.h"

// --- SETTERS --- //
void Lights::setPosition(vec3 pos)	{ this->position = pos;		}
void Lights::setColor(vec3 color)	{ this->color	 = color;	}

// --- GETTERS --- //
vec3 Lights::getPosition()	const { return this->position;	}
vec3 Lights::getColor()		const { return this->color;		}