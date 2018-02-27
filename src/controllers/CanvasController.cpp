//
// Created by Grégoire GUEMAS on 18-02-15.
//

#include <boost/bind.hpp>
#include <graphics/ofPolyline.h>
#include <graphics/ofGraphics.h>
#include <model/Vectorial2dForm/RecursiveTree.h>
#include "CanvasController.h"
#include "model/of2d/of2dFactory.h"
#include "model/of2d/of2dObject.h"
#include "services/history/HistoryManager.h"
#include "ControllerFactory.h"
#include <model/Vectorial2dForm/Sierpinski.h>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"
const std::map<int, const char *> CanvasController::stateToString = {
        {NONE,              ""},
        {STATE::RECTANGLE,  "Rectangle"},
        {STATE::POLYGONE,   "Polygone"},
        {STATE::CIRCLE,     "Cercle"},
        {STATE::LINE,       "Ligne"},
        {STATE::TRIANGLE,   "Triangle"},
        {STATE::REC_TREE,   "Arbre récursif"},
        {STATE::SIERPINSKI, "Sierpinski"},
};

void CanvasController::setup() {
    this->setState(NONE);
    this->history = HistoryManager::getInstance()->getFromController(this);
    ofSetCircleResolution(100);
}

void CanvasController::draw() {
    ofSetBackgroundColor(this->drawOption->getBackgroundColor());
    for (const auto &f : this->otherObject) {
        ofPushMatrix();
        ofPushStyle();
        f();
        ofPopStyle();
        ofPopMatrix();
        ofSetColor(ofColor::white);
    }
    ofSetColor(ofColor::black);
    for (const auto &point : this->pointList) {
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
        this->pointList.emplace_back(evt.x, evt.y);
        return;
    }
    if (this->initialPoint == nullptr) {
        this->initialPoint = std::make_shared<ofVec2f>(evt.x, evt.y);
        return;
    }
}

void CanvasController::onMouseRelease(ofMouseEventArgs &evt) {
    switch (this->state) {
        case NONE:
            break;
        case LINE: {
            ofPolyline line;
            line.addVertex(this->initialPoint->x, this->initialPoint->y);
            line.addVertex(evt.x, evt.y);
            otherObjectDrawCall x = [line]() { line.draw(); };
            this->otherObject.push_back(drawIt(x, false));
            auto redoFct = [x, this]() { this->otherObject.push_back(drawIt(x, false)); };
            DEFINE_UNDO_REDO_CONTAINER(this->history, this->otherObject, redoFct);
            break;
        }
        case CIRCLE: {
            float radius = this->initialPoint->distance(ofVec2f(evt.x, evt.y));
            ofVec2f point = *this->initialPoint;
            otherObjectDrawCall x = [point, radius, this]() {
                ofDrawCircle(point.x, point.y, radius);
            };
            auto redoFct = [x, this]() {
                this->otherObject.push_back(drawIt(x, false));
            };
            this->otherObject.push_back(drawIt(x, true));
            DEFINE_UNDO_REDO_CONTAINER(this->history, this->otherObject, redoFct);
            break;
        }
        default:
            break;
    }
    this->initialPoint = nullptr;
}

void CanvasController::onKeyRelease(ofKeyEventArgs &evt) {
    std::cout << "key:" << evt.key << std::endl;
    CursorManager::getInstance()->setCursor(CursorManager::CURSOR_TYPE::DEFAULT);
    switch (evt.key) {
        case NONE:
            this->pointList.clear();
            LIST_CONTAIN_0_ELEMENT(true, setState(NONE))
            break;
        case POLYGONE: {
            LIST_CONTAIN_0_ELEMENT(this->pointList.empty(), setState(POLYGONE))
            LIST_CONTAIN_0_ELEMENT(this->pointList.size() < 3, ;)
            drawPolygon(this->drawOption->getFillColor(), this->pointList);
            pointList.clear();
            break;
        }
        case LINE:
            LIST_CONTAIN_0_ELEMENT(this->pointList.empty(), setState(LINE);
                    CursorManager::getInstance()->setCursor(CursorManager::CURSOR_TYPE::LINE))
            break;
        case CIRCLE: {
            LIST_CONTAIN_0_ELEMENT(this->pointList.empty(), setState(CIRCLE);
                    CursorManager::getInstance()->setCursor(CursorManager::CURSOR_TYPE::CIRCLE));
            break;
        }
        case RECTANGLE: {
            LIST_CONTAIN_0_ELEMENT(this->pointList.size() != 2,
                                   std::string("2 points sont nécessaire pour un rectangle "));
            drawRectangleFromPoint(this->drawOption->getFillColor(), this->pointList);
            this->pointList.clear();
            break;
        }
        case TRIANGLE: {
            LIST_CONTAIN_0_ELEMENT(this->pointList.size() != 3,
                                   std::string("3 points sont nécessaire pour un triangle "))
            drawTriangleFromPoint(this->drawOption->getFillColor(), this->pointList);
            this->pointList.clear();
            break;
        }
        case REC_TREE: {
            LIST_CONTAIN_0_ELEMENT(this->pointList.size() != 1,
                                   std::string("1 point est nécessaire pour un arbre "))
            const ofVec2f point = this->pointList[0];
            auto draw = [point]() { RecursiveTree().draw(point); };
            auto redoFunction = [draw, this]() { this->otherObject.emplace_back(draw); };
            redoFunction();
            this->pointList.clear();
            DEFINE_UNDO_REDO_CONTAINER(this->history, this->otherObject, redoFunction);

        }
        case SIERPINSKI: {
            LIST_CONTAIN_0_ELEMENT(this->pointList.size() != 1,
                                   std::string("1 point est nécessaire pour un arbre "))
            const auto point = this->pointList[0];
            const std::string simulation = Sierpinski(ofVec2f()).simulate(9);
            auto draw = [point, simulation]() { Sierpinski(point, 0.9f).render(simulation); };
            auto redoFunction = [draw, this]() { this->otherObject.emplace_back(draw); };
            redoFunction();
            this->pointList.clear();
            DEFINE_UNDO_REDO_CONTAINER(this->history, this->otherObject, redoFunction);
        }
        case ' ': { //Save
            auto image = this->getCanvas()->getCapture();
            ControllerFactory::getPictureController()->addImage(image);
            break;
        }
        default:
            break;
    }
}

void CanvasController::load(OfCanvasPtr canvas) {
    this->canvas = canvas;
    this->otherObject = canvas->getObject();
}

void CanvasController::reset() {
    this->otherObject.clear();
}

OfCanvasPtr CanvasController::getCanvas() {
    auto *img = new ofImage();
    img->grabScreen(0, 0, ofGetWidth(), ofGetHeight());
    this->canvas = make_shared<OfCanvas>(this->otherObject, img);
    return this->canvas;
}

ofColor CanvasController::randomColor() const {
    return {ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)};
}

void CanvasController::drawTriangleFromPoint(const ofColor &color, const vector<ofVec2f> &pointList) {
    const auto vec = pointList;
    otherObjectDrawCall x = [vec, color, this]() {
        ofDrawTriangle(vec[0].x, vec[0].y, vec[1].x, vec[1].y, vec[2].x, vec[2].y);
    };
    this->otherObject.push_back(drawIt(x, true));
    auto redoFunction = [color, vec, this]() { this->drawTriangleFromPoint(color, vec); };
    DEFINE_UNDO_REDO_CONTAINER(this->history, this->otherObject, redoFunction);
}

void CanvasController::drawRectangleFromPoint(const ofColor &color, const vector<ofVec2f> &pointList) {
    const auto &vec = pointList;
    otherObjectDrawCall x = [vec, color, this]() {
        auto leftX = vec[0].x < vec[1].x ? vec[0].x : vec[1].x;
        auto leftY = vec[0].y < vec[1].y ? vec[0].y : vec[1].y;
        float h = DISTANCE_BTW_POINT(vec[0].x, vec[1].x);
        float d = DISTANCE_BTW_POINT(vec[0].y, vec[1].y);
        ofDrawRectangle(leftX, leftY, h, d);
    };
    this->otherObject.push_back(drawIt(x, true));
    auto redoFunction = [color, vec, this]() { this->drawRectangleFromPoint(color, vec); };
    DEFINE_UNDO_REDO_CONTAINER(this->history, this->otherObject, redoFunction);
}

void CanvasController::drawPolygon(const ofColor &color, const vector<ofVec2f> &pointList) {
    std::vector<ofVec2f> vec = pointList;
    otherObjectDrawCall x = [color, vec, this]() {
        ofBeginShape();
        for (const auto &point : vec) {
            ofVertex(point.x, point.y);
        }
        ofEndShape(true);
    };
    otherObject.push_back(drawIt(x, true));
    auto redoFunction = [color, vec, this]() { this->drawPolygon(color, vec); };
    DEFINE_UNDO_REDO_CONTAINER(this->history, this->otherObject, redoFunction);
}

otherObjectDrawCall CanvasController::drawIt(otherObjectDrawCall fct, bool toFill) {
    ofColor fillColor = this->drawOption->getFillColor();
    ofColor outlineColor = this->drawOption->getOutLineColor();
    float weight = this->drawOption->getWeight();
    auto color = (toFill ? fillColor : outlineColor);
    auto f = [fct, weight, color, fillColor, outlineColor, toFill]() {
        ofSetLineWidth(weight);
        if (toFill) {
            ofSetColor(fillColor);
            ofFill();
            fct();
            ofNoFill();
        }
        ofSetColor(outlineColor);
        fct();
    };
    return f;
}

#pragma clang diagnostic pop