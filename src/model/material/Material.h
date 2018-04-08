#pragma once


#include <ofMain.h>
#include "MaterialType.h"
#include "BaseMaterial.h"
#include "MaterialGouraud.h"
#include "MaterialLambert.h"
#include "MaterialPhong.h"
enum class typeIllum:int {
	BASE,GOURAUD,LAMBERT,PHONG
};

class Material {
public:
	
	void beginMaterial(vector<ofLight> &lights);
	void endMaterial();
	void changeMaterialType(typeIllum type);

	void setEmissiveColor(ofColor color);
	const ofColor getEmissiveColor();

	void setSpecularColor(ofColor color);
	const ofColor getSpecularColor();

	void setDiffuseColor(ofColor color);
	const ofColor getDiffuseColor();

	void setAmbientColor(ofColor color);
	const ofColor getAmbientColor();

	void setShininess(float shininess);
	const float getShininess();

private:
	typeIllum currentMaterial = typeIllum::BASE;

	MaterialType * material = new BaseMaterial();

	ofColor emissiveColor;
	ofColor specularColor;
	ofColor diffuseColor;
	ofColor ambientColor;
	float shininess = 0;
};
