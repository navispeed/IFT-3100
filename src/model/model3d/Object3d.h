#pragma once
#include "ofMain.h"
#include "model\material\Material.h"

class Object3d {
public:
	virtual void drawObject(vector<ofLight> lights) = 0;

	virtual void rotate(float angle, ofVec3f axis) = 0;

	virtual void translate(ofVec3f translation) = 0;

	virtual void modifyScale(ofVec3f scaleAdjust) = 0;

	virtual ofNode* getAsOfNode()= 0;
	
	virtual ofImage getTexture()=0;

	virtual void setTexture(ofImage texture) = 0;

	virtual Material &getMaterial() = 0;
};