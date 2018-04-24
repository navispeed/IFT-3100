#pragma once
#include "ofMain.h"
class MaterialType {
protected:
	ofFloatColor diffuse;
	ofFloatColor ambient;
	ofFloatColor specular;
public:
	virtual void beginMaterial(vector<ofLight> lights) = 0;

	virtual void endMaterial() = 0;

	virtual void setEmissiveColor(ofColor color) = 0;

	virtual void setDiffuseColor(ofColor color) = 0;
	
	virtual void setSpecularColor(ofColor color) = 0;

	virtual void setAmbientColor(ofColor color) = 0;
	
	virtual void setShininess(float shininess) = 0;
};