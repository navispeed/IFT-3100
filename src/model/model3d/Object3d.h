#pragma once
#include "ofMain.h"

class Object3d {
public:
	virtual void drawObject() = 0;

	virtual void rotate(float angle, ofVec3f axis) = 0;

	virtual void translate(ofVec3f translation) = 0;

	virtual void modifyScale(ofVec3f scaleAdjust) = 0;
};