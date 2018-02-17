//
// Created by Grégoire GUEMAS on 18-02-15.
//

#include <boost/bind.hpp>
#include <graphics/ofPolyline.h>
#include <graphics/ofGraphics.h>
#include "CanvasController.h"
#include "model/of2d/of2dFactory.h"
#include "model/of2d/of2dObject.h"
#include "services/history/HistoryManager.h"
#include "ControllerFactory.h"


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
    this->history = HistoryManager::getInstance()->getFromController(this);
    ofSetCircleResolution(100);
}

void CanvasController::draw() {
    for (const auto &o : this->object) {
        o->draw();
    }
    for (const auto &f : this->otherObject) {
        f();
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
            LIST_CONTAIN_0_ELEMENT(this->pointList.empty(), setState(POLYGONE))
            LIST_CONTAIN_0_ELEMENT(this->pointList.size() < 3, ;)
            drawPolygon(color, this->pointList);
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
            drawRectangleFromPoint(color, this->pointList);
            this->pointList.clear();
            break;
        }
        case TRIANGLE: {
            LIST_CONTAIN_0_ELEMENT(this->pointList.size() != 3,
                                   std::string("3 points sont nécessaire pour un triangle "))
            drawTriangleFromPoint(color, this->pointList);
            this->pointList.clear();
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
            ofVec2f point = *this->initialPoint;
            otherObjectDrawCall x = [point, radius]() { ofDrawCircle(point.x, point.y, radius); };
            this->otherObject.push_back(x);
            break;
        }
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
    return {ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)};
}

void CanvasController::drawTriangleFromPoint(const ofColor &color, const vector<ofVec2f> &pointList) {
    const auto vec = pointList;
    otherObjectDrawCall x = [vec, color, this]() {
        ofSetColor(color);
        ofDrawTriangle(vec[0].x, vec[0].y, vec[1].x, vec[1].y, vec[2].x, vec[2].y);
        ofSetColor(defColor);
    };
    this->otherObject.push_back(x);
    auto iteratorOnLast = otherObject.end()--;
    iteratorOnLast--;
    this->history->add([iteratorOnLast, this]() { this->otherObject.erase(iteratorOnLast); },
                       [color, vec, this]() { this->drawTriangleFromPoint(color, vec); });
}

void CanvasController::drawRectangleFromPoint(const ofColor &color, const vector<ofVec2f> &pointList) {
    const auto vec = pointList;
    otherObjectDrawCall x = [vec, color, this]() {
        ofSetColor(color);
        auto leftX = vec[0].x < vec[1].x ? vec[0].x : vec[1].x;
        auto leftY = vec[0].y < vec[1].y ? vec[0].y : vec[1].y;
        float h = DISTANCE_BTW_POINT(vec[0].x, vec[1].x);
        float d = DISTANCE_BTW_POINT(vec[0].y, vec[1].y);
        ofDrawRectangle(leftX, leftY, h, d);
        ofSetColor(defColor);
    };
    this->otherObject.push_back(x);
    auto iteratorOnLast = otherObject.end()--;
    iteratorOnLast--;
    this->history->add([iteratorOnLast, this]() { this->otherObject.erase(iteratorOnLast); },
                       [color, vec, this]() { this->drawRectangleFromPoint(color, vec); });
}

void CanvasController::drawPolygon(const ofColor &color, const vector<ofVec2f> &pointList) {
    std::vector<ofVec2f> vec = pointList;
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
    otherObject.push_back(x);
    auto iteratorOnLast = otherObject.end()--;
    iteratorOnLast--;
    this->history->add([iteratorOnLast, this]() { this->otherObject.erase(iteratorOnLast); },
                       [color, vec, this]() { this->drawPolygon(color, vec); });
}
