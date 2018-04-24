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
	shader.begin();
	shader.setUniform3f("lightPosition", lights.at(0).getGlobalPosition() * ofGetCurrentMatrix(OF_MATRIX_MODELVIEW));
	shader.setUniform3f("colorDiffuse", diffuse.r, diffuse.g, diffuse.b);
	shader.setUniform3f("colorAmbient", ambient.r, ambient.g, ambient.b);
	shader.setUniform3f("colorSpecular", specular.r, specular.g, specular.b);
}

void MaterialPhong::endMaterial() {
	shader.end();	
}

void MaterialPhong::setEmissiveColor(ofColor color) {}

void MaterialPhong::setDiffuseColor(ofColor color) {
	diffuse = color;
}

void MaterialPhong::setSpecularColor(ofColor color) {
	specular = color;
}

void MaterialPhong::setAmbientColor(ofColor color) {
	ambient = color;
}

void MaterialPhong::setShininess(float shininess) {}