#include "BaseMaterial.h"

void BaseMaterial::beginMaterial(vector<ofLight> lights) {
	material.begin();
}

void BaseMaterial::endMaterial() {
	material.end();
}

void BaseMaterial::setEmissiveColor(ofColor color) {
	material.setEmissiveColor(color);
}

void BaseMaterial::setDiffuseColor(ofColor color) {
	material.setDiffuseColor(color);
}

void BaseMaterial::setSpecularColor(ofColor color) {
	material.setSpecularColor(color);
}

void BaseMaterial::setAmbientColor(ofColor color) {
	material.setAmbientColor(color);
}

void BaseMaterial::setShininess(float shininess) {
	material.setShininess(shininess);
}