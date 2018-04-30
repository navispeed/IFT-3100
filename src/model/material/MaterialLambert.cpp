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

void MaterialLambert::beginMaterial(map<int, ofLight*>& lights) {
	shader.begin();
	ofVec3f * positions = new ofVec3f[lights.size()];
	int i = 0;
	for (auto it : lights) {
		positions[i] = it.second->getGlobalPosition() * ofGetCurrentMatrix(OF_MATRIX_MODELVIEW);
		i++;
	}
	shader.setUniform3fv("lightPositions", (float*)positions);
	shader.setUniform1i("lightNumber", lights.size());
	shader.setUniform3f("colorDiffuse", diffuse.r, diffuse.g, diffuse.b);
	shader.setUniform3f("colorAmbient", ambient.r, ambient.g, ambient.b);
	shader.setUniform3f("colorEmissive", emissive.r, emissive.g, emissive.b);
}

void MaterialLambert::endMaterial() {
	shader.end();
}

void MaterialLambert::setEmissiveColor(ofColor color) {
	emissive = color;
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