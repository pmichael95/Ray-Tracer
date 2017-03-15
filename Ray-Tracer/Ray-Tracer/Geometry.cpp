/*
* GEOMETRY BASE CLASS IMPLEMENTATION
*/
#include "Geometry.h"

Geometry::~Geometry() { } // Virtual destructor

// --- SETTERS --- //
void Geometry::setAmbient(vec3 ambient)		{ this->ambientColor	= ambient;	}
void Geometry::setDiffuse(vec3 diffuse)		{ this->diffuseColor	= diffuse;	}
void Geometry::setSpecular(vec3 specular)	{ this->specularColor	= specular; }
void Geometry::setShininess(float alpha)	{ this->shininess		= alpha;	}
// --------------- //

// --- GETTERS --- //
vec3 Geometry::getAmbient()		const { return this->ambientColor;	}
vec3 Geometry::getDiffuse()		const { return this->diffuseColor;	}
vec3 Geometry::getSpecular()	const { return this->specularColor; }
float Geometry::getShininess()	const { return this->shininess;		}
// --------------- //
