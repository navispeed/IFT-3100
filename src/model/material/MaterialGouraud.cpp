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
	shader.setUniform3f("lightPosition", lights.at(0).getGlobalPosition() * ofGetCurrentMatrix(OF_MATRIX_MODELVIEW));
	shader.begin();
}

void MaterialGouraud::endMaterial() {
	shader.end();
}

void MaterialGouraud::setEmissiveColor(ofColor color) {
}

void MaterialGouraud::setDiffuseColor(ofColor color) {
	ofFloatColor col = color;
	shader.setUniform3f("colorDiffuse", col.r, col.g, col.b);
}

void MaterialGouraud::setSpecularColor(ofColor color) {
	ofFloatColor col = color;
	shader.setUniform3f("colorSpecular", col.r, col.g, col.b);
}

void MaterialGouraud::setAmbientColor(ofColor color) {
	ofFloatColor col = color;
	shader.setUniform3f("colorAmbient", col.r, col.g, col.b);
}

void MaterialGouraud::setShininess(float shininess) {}