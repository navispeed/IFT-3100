//
// Created by Grégoire GUEMAS on 18-02-15.
//

#include <boost/bind.hpp>
#include <graphics/ofPolyline.h>
#include <graphics/ofGraphics.h>
#include <memory>
#include <GLFW/glfw3.h>
#include "CanvasController.h"
#include "../model/of2d/of2d.h"
#include "../model/of2d/of2dFactory.h"
#include "../model/of2d/of2dObject.h"
#include "ControllerFactory.h"
#include "../cursors/CursorManager.h"


const std::map<int, const char *> CanvasController::stateToString = {
        {NONE,             ""},
        {STATE::RECTANGLE, "Rectangle"},
        {STATE::POLYGONE,  "Polygone"},
        {STATE::CIRCLE,    "Cercle"},
        {STATE::LINE,      "Ligne"},
        {STATE::TRIANGLE,  "Triangle"},
};

void CanvasController::setup() {
    this->setState(NONE);
    ofSetCircleResolution(100);
//    ofAddListener()
}

void CanvasController::draw() {
    for (auto o : this->object) {
        o->draw();
    }
    for (auto f : this->otherObject) {
        f();
    }
    ofSetColor(ofColor::black);
    for (auto point : this->pointList) {
        ofDrawCircle(point, 3);
    }
    ofSetColor(CanvasController::defColor);
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
        this->pointList.push_back(ofVec2f(evt.x, evt.y));
        return;
    }
    if (this->initialPoint == nullptr) {
        this->initialPoint = std::make_shared<ofVec2f>(evt.x, evt.y);
        return;
    }
}

void CanvasController::onKeyRelease(ofKeyEventArgs &evt) {
    std::cout << "key:" << evt.key << std::endl;
    CursorManager::getInstance()->setCursor(CursorManager::CURSOR_TYPE::DEFAULT);
    auto color = randomColor();
    switch (evt.key) {
        case NONE:
            this->pointList.clear();
            LIST_CONTAIN_0_ELEMENT(true, setState(NONE))
            break;
        case POLYGONE: {
            LIST_CONTAIN_0_ELEMENT(this->pointList.size() == 0, setState(POLYGONE))
            LIST_CONTAIN_0_ELEMENT(this->pointList.size() < 3, ;)
            drawPolygon(color);
            break;
        }
        case LINE:
            LIST_CONTAIN_0_ELEMENT(this->pointList.size() == 0, setState(LINE); CursorManager::getInstance()->setCursor(CursorManager::CURSOR_TYPE::LINE))
            break;
        case CIRCLE: {
            LIST_CONTAIN_0_ELEMENT(this->pointList.size() == 0, setState(CIRCLE); CursorManager::getInstance()->setCursor(CursorManager::CURSOR_TYPE::CIRCLE));
            break;
        }
        case RECTANGLE: {
            drawRectangleFromPoint(color);
            break;
        }
        case TRIANGLE: {
            drawTriangleFromPoint(color);
            break;
        }
        case 115: { //Save
            auto image = this->getCanvas()->getCapture();
            ControllerFactory::getPictureController()->addImage(image);
            break;
        }
        default:
            break;
    }
}

void CanvasController::onMouseRelease(ofMouseEventArgs &evt) {
    auto color = randomColor();
    switch (this->state) {
        case NONE:
            break;
        case LINE: {
            const shared_ptr<of2d> &ptr = of2dFactory::getLine();
            shared_ptr<ofPolyline> line = dynamic_cast<of2dObject<ofPolyline> *>(&(*ptr))->getInstance();
            line->addVertex(this->initialPoint->x, this->initialPoint->y);
            line->addVertex(evt.x, evt.y);
            this->object.push_back(ptr);
            break;
        }
        case CIRCLE: {
            float radius = this->initialPoint->distance(ofVec2f(evt.x, evt.y));
            ofVec2f point = *this->initialPoint.get();
            otherObjectDrawCall x = [point, radius]() { ofDrawCircle(point.x, point.y, radius); };
            this->otherObject.push_back(x);
            break;
        }
        case RECTANGLE:
            break;
        default:
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
    this->otherObject.clear();
}

OfCanvasPtr CanvasController::getCanvas() {
    auto *img = new ofImage();
    img->grabScreen(0, 0, ofGetWidth(), ofGetHeight());
    this->canvas = make_shared<OfCanvas>(this->object, img);
    return this->canvas;
}

ofColor CanvasController::randomColor() const {
    return ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255));
}

void CanvasController::drawTriangleFromPoint(const ofColor &color) {
    LIST_CONTAIN_0_ELEMENT(this->pointList.size() != 3,
                           std::string("3 points sont nécessaire pour un triangle "))
    auto vec = pointList;
    otherObjectDrawCall x = [vec, color, this]() {
        ofSetColor(color);
        ofDrawTriangle(vec[0].x, vec[0].y, vec[1].x, vec[1].y, vec[2].x, vec[2].y);
        ofSetColor(defColor);
    };
    this->pointList.clear();
    this->otherObject.push_back(x);
}

void CanvasController::drawRectangleFromPoint(const ofColor &color) {
    LIST_CONTAIN_0_ELEMENT(this->pointList.size() != 2,
                           std::string("2 points sont nécessaire pour un rectangle "))
    auto vec = pointList;
    otherObjectDrawCall x = [vec, color, this]() {
        ofSetColor(color);
        auto leftX = vec[0].x < vec[1].x ? vec[0].x : vec[1].x;
        auto leftY = vec[0].y < vec[1].y ? vec[0].y : vec[1].y;
        float h = DISTANCE_BTW_POINT(vec[0].x, vec[1].x);
        float d = DISTANCE_BTW_POINT(vec[0].y, vec[1].y);
        ofDrawRectangle(leftX, leftY, h, d);
        ofSetColor(defColor);
    };
    this->pointList.clear();
    this->otherObject.push_back(x);
}

void CanvasController::drawPolygon(const ofColor &color)  {
    auto vec = pointList;
    ofPolyline line;
    for (auto p: vec) {
        line.addVertex(p);
    }
    line.addVertex(*vec.begin());
    otherObjectDrawCall x = [line, color, this]() {
        ofSetColor(color);
        line.draw();
        ofSetColor(defColor);
    };
    pointList.clear();
    otherObject.push_back(x);
}

