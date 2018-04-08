#include "MaterialPhong.h"

MaterialPhong::MaterialPhong() {
	string shaderVersion = "120";
	if (ofIsGLProgrammableRenderer())
	{
		shaderVersion = "330";
	}

	shader.load(
		"shader/phong_" + shaderVersion + "_vs.glsl",
		"shader/phong_" + shaderVersion + "_fs.glsl");
}


void MaterialPhong::beginMaterial(vector<ofLight> lights) {
	shader.setUniform3f("lightPosition", lights.at(0).getGlobalPosition() * ofGetCurrentMatrix(OF_MATRIX_MODELVIEW));
	shader.begin();
}

void MaterialPhong::endMaterial() {
	shader.end();	
}

void MaterialPhong::setEmissiveColor(ofColor color) {}

void MaterialPhong::setDiffuseColor(ofColor color) {
	ofFloatColor col = color;
	shader.setUniform3f("colorDiffuse", col.r, col.g, col.b);
}

void MaterialPhong::setSpecularColor(ofColor color) {
	ofFloatColor col = color;
	shader.setUniform3f("colorSpecular", col.r, col.g, col.b);
}

void MaterialPhong::setAmbientColor(ofColor color) {
	ofFloatColor col = color;
	shader.setUniform3f("colorAmbient", col.r, col.g, col.b);
}

void MaterialPhong::setShininess(float shininess) {}