#include "Material.h"

void Material::beginMaterial(map<int, ofLight*>& lights) {
	material->beginMaterial(lights);
}

void Material::endMaterial() {
	material->endMaterial();
}
void Material::changeMaterialType(typeIllum type) {
	delete material;
	switch (type) {
		case typeIllum::BASE:
			material = new BaseMaterial();
			break;
		case typeIllum::GOURAUD:
			material = new MaterialGouraud();
			break;
		case typeIllum::LAMBERT:
			material = new MaterialLambert();
			break;
		case typeIllum::PHONG:
			material = new MaterialPhong();
			break;
	}
	material->setAmbientColor(ambientColor);
	material->setDiffuseColor(diffuseColor);
	material->setEmissiveColor(emissiveColor);
	material->setSpecularColor(specularColor);
	material->setShininess(shininess);
}

void Material::setEmissiveColor(ofColor color) {
	emissiveColor = color;
	material->setEmissiveColor(emissiveColor);
}

const ofColor Material::getEmissiveColor() {
	return emissiveColor;
}

void Material::setSpecularColor(ofColor color) {
	specularColor = color;
	material->setSpecularColor(specularColor);
}

const ofColor Material::getSpecularColor() {
	return specularColor;
}

void Material::setDiffuseColor(ofColor color) {
	diffuseColor = color;
	material->setDiffuseColor(diffuseColor);
}

const ofColor Material::getDiffuseColor() {
	return diffuseColor;
}

void Material::setAmbientColor(ofColor color) {
	ambientColor = color;
	material->setAmbientColor(ambientColor);
}


const ofColor Material::getAmbientColor() {
	return ambientColor;
}

void Material::setShininess(float shininess) {
	this->shininess = shininess;
	material->setShininess(this->shininess);
}

const float Material::getShininess() {
	return shininess;
}
