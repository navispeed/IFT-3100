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

void MaterialGouraud::beginMaterial(map<int, ofLight*>& lights) {
	shader.begin();
	ofVec3f * positions = new ofVec3f[lights.size()];
	int i = 0;
	for (auto it : lights) {
		positions[i] = it.second->getGlobalPosition() * ofGetCurrentMatrix(OF_MATRIX_MODELVIEW);
		i++;
	}
	shader.setUniform3fv("lightPositions", (float*)positions);
	shader.setUniform1i("lightNumber", lights.size());
	shader.setUniform3f("colorSpecular", specular.r, specular.g, specular.b);
	shader.setUniform3f("colorAmbient", ambient.r, ambient.g, ambient.b);
	shader.setUniform3f("colorDiffuse", diffuse.r, diffuse.g, diffuse.b);
	shader.setUniform3f("colorEmissive", emissive.r, emissive.g, emissive.b);
	shader.setUniform1f("brightness", 1.0);
}

void MaterialGouraud::endMaterial() {
	shader.end();
}

void MaterialGouraud::setEmissiveColor(ofColor color) {
	emissive = color;
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