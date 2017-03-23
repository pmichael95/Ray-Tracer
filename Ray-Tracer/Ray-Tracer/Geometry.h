/*
* BASE ABSTRACT GEOMETRY CLASS
-> Each shape is-a Geometry type
*/
#ifndef GEOMETRY_H
#define GEOMETRY_H
#include "CommonIncludes.h"
#include "Rays.h"
#include "Lights.h"

class Geometry {
protected:
	// Geometric Object Properties
	vec3 ambientColor; // Ambient color
	vec3 diffuseColor; // Diffuse color
	vec3 specularColor; // Specular color
	float shininess; // Alpha for shininess factor
public:
	// --- CONSTRUCTORS --- //
	Geometry() : ambientColor(vec3(0.0f, 0.0f, 0.0f)), diffuseColor(vec3(0.0f, 0.0f, 0.0f)), specularColor(vec3(0.0f, 0.0f, 0.0f)), shininess(0.0f) {};
	Geometry(vec3 ambient, vec3 diffuse, vec3 specular, float alpha) : 
		ambientColor(ambient), diffuseColor(diffuse), specularColor(specular), shininess(alpha) { };

	virtual ~Geometry(); // Virtual destructor to be called after derived classes

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
	virtual string getType() const =0; // To acquire strings representing type of shape, for debugging

	// --- HELPERS --- //
	virtual pair<bool, float> intersection(Rays ray) = 0; // Pure virtual method to be implemented in derived classes
														// Represents an intersection that will return a bool for true if it intersected
														// And a float value for the distance with the passed ray
	virtual vec3 phong(vec3 q, Lights* light) = 0; // Phong lighting system calculations by each derivative shape
};

#endif