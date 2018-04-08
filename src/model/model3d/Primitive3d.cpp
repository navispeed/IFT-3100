#include "Primitive3d.h"

Primitive3d::~Primitive3d()
{
	delete this->primitive;
}

Primitive3d::Primitive3d(of3dPrimitive * primitive)
{
	this->primitive = primitive;
}

void Primitive3d::drawObject(vector<ofLight> lights)
{

	this->texture.bind();
	this->material.beginMaterial(lights);
	this->primitive->draw();
	this->material.endMaterial();
	this->texture.unbind();
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
	ofVec3f scale = this->primitive->getScale() + scaleAdjust;
	this->primitive->setScale(scale);
}

ofImage Primitive3d::getTexture()
{
	return texture;
}

void Primitive3d::setTexture(ofImage texture)
{
	this->texture = texture;
}

ofNode *Primitive3d::getAsOfNode() {
	return this->primitive;
}

Material &Primitive3d::getMaterial() {
	return this->material;
}
