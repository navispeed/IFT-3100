#include "Model3dController.h"

Model3dController::~Model3dController()
{
	delete model1;
	delete model2;
	delete initialPoint;
	for (int i = 0; i < this->container->size(); i++) {
		delete (*container)[i];
	}
	delete container;
}

void Model3dController::setup()
{
	ofSetWindowTitle("3d mode");
	model1 = new ofxAssimpModelLoader();
	model1->loadModel("model1.obj");
	model2 = new ofxAssimpModelLoader();
	model2->loadModel("model2.obj");
	enableEvents();
}

void Model3dController::draw()
{
	ofEnableDepthTest();
	for (int i = 0; i < container->size(); i++) {
		(*container)[i]->drawObject();
	}
}

void Model3dController::enableEvents() {
	ofAddListener(ofEvents().mousePressed, this, &Model3dController::onMousePressed);
	ofAddListener(ofEvents().mouseReleased, this, &Model3dController::onMouseReleased);
	ofAddListener(ofEvents().keyPressed, this, &Model3dController::onKeyRelease);
}

void Model3dController::disableEvents() {
	ofRemoveListener(ofEvents().mousePressed, this, &Model3dController::onMousePressed);
	ofRemoveListener(ofEvents().mouseReleased, this, &Model3dController::onMouseReleased);
	ofRemoveListener(ofEvents().keyPressed, this, &Model3dController::onKeyRelease);
}

void Model3dController::onMousePressed(ofMouseEventArgs &evt) {
	switch (formMode) {
	case FormMode::model1:
		container->push_back(new Model3d(model1,ofVec3f(evt.x,evt.y,0)));
		std::cout << "newArbre" << std::endl;
		break;
	case FormMode::model2:
		container->push_back(new Model3d(model2, ofVec3f(evt.x, evt.y, 0)));
		std::cout << "newArbre" << std::endl;
		break;
	default:
		ofVec2f * ptr = new ofVec2f(evt.x, evt.y);
		if (this->initialPoint != nullptr) {
			delete this->initialPoint;
		}
		initialPoint = ptr;
		break;
	}
}

void Model3dController::onKeyRelease(ofKeyEventArgs &evt) {
	CursorManager::getInstance()->setCursor(CursorManager::CURSOR_TYPE::DEFAULT);
	switch (evt.key) {
	case 97://a
		formMode = FormMode::model1;
		std::cout << "modeModel1" << std::endl;
		break;
	case 98://b
		formMode = FormMode::model2;
		std::cout << "modeModel2" << std::endl;
		break;
	case 99://c
		formMode = FormMode::box;
		std::cout << "modeBoite" << std::endl;
		CursorManager::getInstance()->setCursor(CursorManager::CURSOR_TYPE::CUBE);
		break;
	case 115://s
		formMode = FormMode::sphere;
		std::cout << "modeSphere" << std::endl;
		CursorManager::getInstance()->setCursor(CursorManager::CURSOR_TYPE::SPHERE);
		break;
	case 356://fleche
		for (int i = 0; i < container->size(); i++) {
			(*container)[i]->rotate(5,ofVec3f(1, 0, 0));
			//(*container)[i]->translate(ofVec3f(1, 0, 0));
			//(*container)[i]->modifyScale(ofVec3f(0.5, 0.5, 0.5));
		}
		break;
	case 358://fleche
		for (int i = 0; i < container->size(); i++) {
			(*container)[i]->rotate(-5,ofVec3f(1, 0, 0));
			//(*container)[i]->translate(ofVec3f(-1, 0, 0));
			//(*container)[i]->modifyScale(ofVec3f(-0.5, -0.5, -0.5));
		}
		break;
	case 357://fleche
		for (int i = 0; i < container->size(); i++) {
			(*container)[i]->rotate(5,ofVec3f(0, 1, 0));
			//(*container)[i]->translate(ofVec3f(0, 1, 0));
			//(*container)[i]->modifyScale(ofVec3f(0.05, 0.05, 0.05));
		}
		break;
	case 359://fleche
		for (int i = 0; i < container->size(); i++) {
			(*container)[i]->rotate(-5,ofVec3f(0, 1, 0));
			//(*container)[i]->translate(ofVec3f(0, -1, 0));
			//(*container)[i]->modifyScale(ofVec3f(-0.05,-0.05, -0.05));
		}
		break;
	case 127://supprimer
		this->reset();
		break;
	default:
		formMode = FormMode::none;
		break;
	}
	std::cout << to_string(evt.key);
}

void Model3dController::onMouseReleased(ofMouseEventArgs & evt)
{	
	switch (formMode) {
	case FormMode::box:
		container->push_back(this->createBox(ofVec3f(evt.x, evt.y, 0)));
		break;
	case FormMode::sphere:
		container->push_back(this->createSphere(ofVec3f(evt.x, evt.y, 0)));
		break;
	default:
		break;
	}
}

Object3d * Model3dController::createBox(const ofVec3f & position)
{
	ofBoxPrimitive * temp = new ofBoxPrimitive();
	temp->set(this->initialPoint->distance(ofVec2f(position.x, position.y)));
	temp->setPosition(position);
	Primitive3d * ptr = new Primitive3d(temp);
	return ptr;
}

Object3d * Model3dController::createSphere(const ofVec3f & position)
{
	ofSpherePrimitive * temp = new ofSpherePrimitive();
	temp->setRadius((this->initialPoint->distance(ofVec2f(position.x, position.y))) / 2);
	temp->setPosition(position);
	Primitive3d * ptr = new Primitive3d(temp);
	return ptr;
}

void Model3dController::reset() {
	container->clear();
}