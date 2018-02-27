#include "Model3d.h"


Model3d::Model3d(ofxAssimpModelLoader * model,ofVec3f position)
{
	this->position = position;
	this->model = model;
	this->scale = ofVec3f(1,1,1);
	this->angleX = 0;
	this->angleY = 0;
	this->angleZ = 0;
}


void Model3d::drawObject()
{
	model->setPosition(position.x,position.y,position.z);
	model->setScale(scale.x, scale.y, scale.z);
	model->setRotation(0, angleX, 1, 0, 0);
	model->setRotation(1, angleY, 0, 1, 0);
	model->setRotation(2, angleZ, 0, 0, 1);
	model->draw(OF_MESH_FILL);
}

void Model3d::rotate(float angle, ofVec3f axis)
{
	if (axis.x > 0) {
		adjustAngleX(angle);
	}
	if (axis.y > 0) {
		adjustAngleY(angle);
	}
	if (axis.z > 0) {
		adjustAngleZ(angle);
	}
}

void Model3d::translate(ofVec3f translation)
{
	this->position += translation;
}

void Model3d::modifyScale(ofVec3f scaleAdjust)
{
	this->scale += scaleAdjust;
}

void Model3d::adjustAngleX(const float adjust)
{
	adjustangle(adjust, this->angleX);
}

void Model3d::adjustAngleY(const float adjust)
{
	adjustangle(adjust, this->angleY);
}

void Model3d::adjustAngleZ(const float adjust)
{
	adjustangle(adjust, this->angleZ);
}

void Model3d::adjustangle(const float adjust, float & angle)
{
	angle -= adjust;
	if (angle > 360) {
		angle -= 360;
	}
	if (angle < -360) {
		angle+= 360;
	}
}

ofNode *Model3d::getAsOfNode() {
	return nullptr;
}

