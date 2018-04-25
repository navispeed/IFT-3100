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


void MaterialPhong::beginMaterial(map<int, ofLight*>& lights) {
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
	shader.setUniform3f("colorSpecular", specular.r, specular.g, specular.b);
	shader.setUniform1f("brightness", 1.0);
}

void MaterialPhong::endMaterial() {
	shader.end();	
}

void MaterialPhong::setEmissiveColor(ofColor color) {
	emissive = color;
}

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