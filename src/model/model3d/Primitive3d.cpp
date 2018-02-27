#include "Primitive3d.h"

Primitive3d::~Primitive3d()
{
	delete this->primitive;
}

Primitive3d::Primitive3d(of3dPrimitive * primitive)
{
	this->primitive = primitive;
}

void Primitive3d::drawObject()
{
	this->primitive->draw();
}

void Primitive3d::rotate(float angle, ofVec3f axis)
{
	this->primitive->rotate(angle, axis);
}

void Primitive3d::translate(ofVec3f translation)
{
	this->primitive->setPosition(this->primitive->getPosition() + translation);
}

void Primitive3d::modifyScale(ofVec3f scaleAdjust)
{
	this->primitive->setScale(this->primitive->getScale() + scaleAdjust);
}

ofNode *Primitive3d::getAsOfNode() {
	return this->primitive;
}
