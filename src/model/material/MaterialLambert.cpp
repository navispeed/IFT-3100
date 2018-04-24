#include "MaterialLambert.h"

MaterialLambert::MaterialLambert() {
	string shaderVersion = "120";
	if (ofIsGLProgrammableRenderer())
	{
		shaderVersion = "330";
	}

	shader.load(
		"shader/Lambert_" + shaderVersion + "_vs.glsl",
		"shader/Lambert_" + shaderVersion + "_fs.glsl");
}

void MaterialLambert::beginMaterial(vector<ofLight> lights) {
	shader.begin();
	shader.setUniform3f("lightPosition", lights.at(0).getGlobalPosition() * ofGetCurrentMatrix(OF_MATRIX_MODELVIEW));
	shader.setUniform3f("colorDiffuse", diffuse.r, diffuse.g, diffuse.b);
	shader.setUniform3f("colorAmbient", ambient.r, ambient.g, ambient.b);
}

void MaterialLambert::endMaterial() {
	shader.end();
}

void MaterialLambert::setEmissiveColor(ofColor color) {

}

void MaterialLambert::setDiffuseColor(ofColor color) {
	diffuse = color;
}

void MaterialLambert::setSpecularColor(ofColor color) {

}

void MaterialLambert::setAmbientColor(ofColor color) {
	ambient = color;
}

void MaterialLambert::setShininess(float shininess) {}