#pragma once

#include <app/ofAppRunner.h>
#include <ofEvent.h>
#include "AController.h"
#include <vector>
#include "../model/model3d/Model3d.h"
#include "../model/model3d/Primitive3d.h"
#include "ofxAssimpModelLoader.h"

class Model3dController :public AController {
private:
	enum class FormMode { none,model1, model2,box,sphere };
	FormMode formMode = FormMode::none;
	std::vector<Object3d*> * container = new vector<Object3d*>();
	ofVec2f * initialPoint = nullptr;

	ofxAssimpModelLoader * model1;
	ofxAssimpModelLoader * model2;

public:
	~Model3dController();

	void setup() override;

	void draw() override;

	void enableEvents() override;
	void disableEvents() override;

	void onMousePressed(ofMouseEventArgs &evt);
	void onMouseReleased(ofMouseEventArgs & evt);
	void onKeyRelease(ofKeyEventArgs &evt);

	Object3d * createBox(const ofVec3f & position);
	Object3d * createSphere(const ofVec3f & position);

	void reset();

};