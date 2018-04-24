#include "MaterialGouraud.h"
MaterialGouraud::MaterialGouraud() {
	string shaderVersion = "120";
	if (ofIsGLProgrammableRenderer())
	{
		shaderVersion = "330";
	}

	shader.load(
		"shader/gouraud_" + shaderVersion + "_vs.glsl",
		"shader/gouraud_" + shaderVersion + "_fs.glsl");
}

void MaterialGouraud::beginMaterial(vector<ofLight> lights) {
	shader.begin();
	shader.setUniform3f("lightPosition", lights.at(0).getPosition());
	shader.setUniform3f("colorSpecular", specular.r, specular.g, specular.b);
	shader.setUniform3f("colorAmbient", ambient.r, ambient.g, ambient.b);
	shader.setUniform3f("colorDiffuse", diffuse.r, diffuse.g, diffuse.b);
}

void MaterialGouraud::endMaterial() {
	shader.end();
}

void MaterialGouraud::setEmissiveColor(ofColor color) {
}

void MaterialGouraud::setDiffuseColor(ofColor color) {
	this->diffuse = color;
}

void MaterialGouraud::setSpecularColor(ofColor color) {
	this->specular = color;
}

void MaterialGouraud::setAmbientColor(ofColor color) {
	this->ambient = color;
}

void MaterialGouraud::setShininess(float shininess) {}