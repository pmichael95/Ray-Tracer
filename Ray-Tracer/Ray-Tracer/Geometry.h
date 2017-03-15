/*
* BASE ABSTRACT GEOMETRY CLASS
*/
#ifndef GEOMETRY_H
#define GEOMETRY_H
#include "CommonIncludes.h"
#include "Rays.h"

class Geometry {
protected:
	// Geometric Object Properties
	vec3 ambientColor; // Ambient color
	vec3 diffuseColor; // Diffuse color
	vec3 specularColor; // Specular color
	float shininess; // Alpha of shininess
public:
	// Default, sets all to empty
	Geometry() : ambientColor(vec3(0.0f, 0.0f, 0.0f)), diffuseColor(vec3(0.0f, 0.0f, 0.0f)), specularColor(vec3(0.0f, 0.0f, 0.0f)), shininess(0.0f) {};
	// Constructor setting all members
	Geometry(vec3 ambient, vec3 diffuse, vec3 specular, float alpha) : 
		ambientColor(ambient), diffuseColor(diffuse), specularColor(specular), shininess(alpha) { };
	virtual ~Geometry(); // Virtual destructor since this is inherited

	// --- SETTERS --- //
	void setAmbient(vec3 ambient);
	void setDiffuse(vec3 diffuse);
	void setSpecular(vec3 specular);
	void setShininess(float alpha);

	// --- GETTERS --- //
	vec3 getAmbient() const;
	vec3 getDiffuse() const;
	vec3 getSpecular() const;
	float getShininess() const;
};

#endif