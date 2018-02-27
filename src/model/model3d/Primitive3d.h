#pragma once
#include "Object3d.h"
#include "of3dPrimitives.h"

class Primitive3d :public Object3d {
public:
	~Primitive3d();
	Primitive3d(of3dPrimitive * primitive);

	void drawObject() override;
	void rotate(float angle, ofVec3f axis) override;
	void translate(ofVec3f translation) override;
	void modifyScale(ofVec3f scaleAdjust) override;
	ofNode *getAsOfNode() override;
private:
	of3dPrimitive * primitive;
};