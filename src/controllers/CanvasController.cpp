//
// Created by Grégoire GUEMAS on 18-02-15.
//

#include <graphics/ofPolyline.h>
#include "CanvasController.h"
#include "../model/of2d/of2d.h"
#include "../model/of2d/of2dFactory.h"
#include "../model/of2d/of2dObject.h"
#include "ControllerFactory.h"

const std::map<int, const char *> CanvasController::stateToString = {
        {NONE,             ""},
        {STATE::RECTANGLE, "Rectangle"},
        {STATE::POINT,     "Point"},
        {STATE::CIRCLE,    "Cercle"},
        {STATE::LINE,      "Ligne"},
};

void CanvasController::setup() {
    this->setState(NONE);
//    ofAddListener()
}

void CanvasController::draw() {
    for (auto o : object) {
        o->draw();
    }
}

void CanvasController::enableEvents() {
    ofAddListener(ofEvents().mousePressed, this, &CanvasController::onMousePressed);
    ofAddListener(ofEvents().mouseReleased, this, &CanvasController::onMouseRelease);
    ofAddListener(ofEvents().keyReleased, this, &CanvasController::onKeyRelease);
}

void CanvasController::disableEvents() {
    ofRemoveListener(ofEvents().mousePressed, this, &CanvasController::onMousePressed);
    ofRemoveListener(ofEvents().mouseReleased, this, &CanvasController::onMouseRelease);
    ofRemoveListener(ofEvents().keyReleased, this, &CanvasController::onKeyRelease);
}

void CanvasController::setState(CanvasController::STATE state) {
    this->state = state;
    if (state == NONE) {
        ofSetWindowTitle("CanvasController mode");
        return;
    }
    std::stringstream ss;
    ss << "[" << CanvasController::stateToString.at(state) << "] " << "CanvasController mode";
    ofSetWindowTitle(ss.str());
}

void CanvasController::onMousePressed(ofMouseEventArgs &evt) {
    if (this->state == NONE) {
        return;
    }
    if (this->initialPoint == nullptr) {
        this->initialPoint = std::make_shared<ofPoint>(evt.x, evt.y);
        return;
    }
}

void CanvasController::onKeyRelease(ofKeyEventArgs &evt) {
    std::cout << "key:" << evt.key << std::endl;
    switch (evt.key) {
        case NONE:
            setState(NONE);
            break;
        case POINT:
            setState(POINT);
            break;
        case LINE:
            setState(LINE);
            break;
        case CIRCLE:
            setState(CIRCLE);
            break;
        case RECTANGLE:
            setState(RECTANGLE);
            break;
        case 115: { //Save
            auto image = this->getCanvas()->getCapture();
            ControllerFactory::getPictureController()->addImage(image);
            break;
        }
    }
}

void CanvasController::onMouseRelease(ofMouseEventArgs &evt) {
    switch (this->state) {
        case NONE:
            break;
        case POINT:
            break;
        case LINE: {
            const shared_ptr<of2d> &ptr = of2dFactory::getLine();
            shared_ptr<ofPolyline> line = dynamic_cast<of2dObject<ofPolyline> *>(&(*ptr))->getInstance();
            line->addVertex(this->initialPoint->x, this->initialPoint->y);
            line->addVertex(evt.x, evt.y);
            this->object.push_back(ptr);
            break;
        }
        case CIRCLE:
            break;
        case RECTANGLE:
            break;
    }
    this->initialPoint = nullptr;

}

void CanvasController::load(OfCanvasPtr canvas) {
    this->canvas = canvas;
    this->object = canvas->getObject();
}

void CanvasController::reset() {
    this->object.clear();
}

OfCanvasPtr CanvasController::getCanvas() {
    auto *img = new ofImage();
    img->grabScreen(0, 0, ofGetWidth(), ofGetHeight());
    this->canvas = make_shared<OfCanvas>(this->object, img);
    return this->canvas;
}
