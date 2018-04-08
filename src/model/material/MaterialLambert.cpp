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
	shader.setUniform3f("lightPosition", lights.at(0).getGlobalPosition() * ofGetCurrentMatrix(OF_MATRIX_MODELVIEW));
	shader.begin();
}

void MaterialLambert::endMaterial() {
	shader.end();
}

void MaterialLambert::setEmissiveColor(ofColor color) {

}

void MaterialLambert::setDiffuseColor(ofColor color) {
	ofFloatColor col = color;
	shader.setUniform3f("colorDiffuse", col.r, col.g, col.b);
}

void MaterialLambert::setSpecularColor(ofColor color) {

}

void MaterialLambert::setAmbientColor(ofColor color) {
	ofFloatColor col = color;
	shader.setUniform3f("colorAmbient", col.r, col.g, col.b);
}

void MaterialLambert::setShininess(float shininess) {}