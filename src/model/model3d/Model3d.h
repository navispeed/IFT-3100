#pragma once

#include "ofxAssimpModelLoader.h"
#include "Object3d.h"

class Model3d:public Object3d{

private:
	ofxAssimpModelLoader * model;
	ofVec3f scale;
	float angleX;
	float angleY;
	float angleZ;
	ofVec3f position;
	ofImage texture;
	Material material;
public:

	Model3d(ofxAssimpModelLoader * model,ofVec3f position);

	void adjustAngleX(const float adjust);
	void adjustAngleY(const float adjust);
	void adjustAngleZ(const float adjust);
	void adjustangle(const float adjust, float& angle);

	void drawObject(vector<ofLight> lights) override;
	void rotate(float angle, ofVec3f axis) override;
	void translate(ofVec3f translation) override;
	void modifyScale(ofVec3f scaleAdjust) override;
	ofImage getTexture() override;
	void setTexture(ofImage texture) override;
	Material &getMaterial() override;

	ofNode *getAsOfNode() override;
};