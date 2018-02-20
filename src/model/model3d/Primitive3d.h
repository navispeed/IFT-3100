#pragma once
#include "Object3d.h"
#include "of3dPrimitives.h"

class Primitive3d :public Object3d {
public:
	~Primitive3d();
	Primitive3d(of3dPrimitive * primitive);
	void drawObject() override;
	void rotate(float angle, const ofVec3f& axis);
	void translate(ofVec3f& translation);
	void modifyScale(ofVec3f& scaleAdjust);
private:
	of3dPrimitive * primitive;
};