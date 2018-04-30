//
// Created by Grégoire GUEMAS on 18-03-30.
//

#include <ofGraphics.h>
#include <of3dGraphics.h>
#include "DemoController.h"

void DemoController::setup() {
    this->viewport[0] = ofRectangle(0, 0, 512, 768);
    this->viewport[1] = ofRectangle(512, 0, 512, 768);
    this->top.setPosition(130, 4420, 1000);
//    this->easyCam.setPosition(18, 850, 3000);
//    this->easyCam.lookAt(ofVec3f(0, 0, 0));

}

void DemoController::draw() {

    this->top.begin(this->viewport[0]);
    drawScene(this->top);
    this->top.lookAt(ofVec3f(0, 0, 0));

    this->top.end();
    this->easyCam.begin(this->viewport[1]);
    drawScene(this->easyCam);
    this->easyCam.end();

    ofNoFill();
    ofSetLineWidth(5);
    ofDrawRectangle(this->viewport[0]);
    ofDrawRectangle(this->viewport[1]);
    ofDrawBitmapString(ofToString("Top Camera"), 10, 50, 0);
    ofDrawBitmapString(ofToString("EasyCam"), 522, 50, 0);
//    std::cout << this->easyCam.getPosition() << std::endl;
}

void DemoController::drawScene(ofCamera cam) {
    ofPushMatrix();
    ofPushStyle();
    ofPushView();
    drawEnv();
    generatePath();
    cam.begin();
    ofRotateX(15);

    ofSetColor(0);
    ofDrawGrid(50, 100, false, false, true, false);
    drawTraveledPath();

    drawCube();
    cam.end();
    ofPopMatrix();
    ofPopStyle();
    ofPopView();
}

void DemoController::drawTraveledPath() const {
    ofPushMatrix();
    ofPushStyle();
    ofPushView();
    ofRotateX(90);
    ofFill();
    ofSetColor(ofColor::black);
    for (auto p : traveledPath) {
        ofDrawRectangle(p.first, p.second, 50, 50);
    }
    ofPopMatrix();
    ofPopStyle();
    ofPopView();
}

void DemoController::enableEvents() {
    ofPushMatrix();
    ofPushStyle();
    ofPushView();
}

void DemoController::disableEvents() {
    ofPopMatrix();
    ofPopStyle();
    ofPopView();
}

void DemoController::drawEnv() {
    // clear the pathLines ofMesh from any old vertices
    pathLines.clear();
    // add all the vertices from pathVertices
    for (unsigned int i = 0; i < pathVertices.size(); i++) {
        pathLines.addVertex(pathVertices[i]);
    }

    ofBackgroundGradient(ofColor::lightGray, ofColor::lightGray);
    ofNoFill();
}

void DemoController::drawCube() {

    // draw the path of the box
    ofSetLineWidth(2);
    ofSetColor(ofColor::cyan);
    pathLines.draw();

    // draw a line connecting the box to the grid
    ofSetColor(ofColor::yellow);
    ofDrawLine(current.x, current.y, current.z, current.x, 0, current.z);
    ofSetColor(ofColor::red);
    ofPushMatrix();
    ofPushStyle();
    ofFill();
    ofRotateX(90.0);
    ofDrawRectangle(static_cast<float>(current.x - std::fmod(current.x, 50)), static_cast<float>(current.z - std::fmod(current.z, 50)), 50, 50);
    this->traveledPath.insert(std::make_pair<float, float>(static_cast<float>(current.x - std::fmod(current.x, 50)), static_cast<float>(current.z - std::fmod(current.z, 50))));
    ofPopStyle();
    ofPopMatrix();
    // translate and rotate to the current position and orientation
    ofTranslate(current.x, current.y, current.z);
    if ((current - previous).length() > 0.0) {
//        rotateToNormal(current - previous);
    }
    ofSetColor(255);
    ofDrawBox(32);
    ofDrawAxis(32);
}

void DemoController::generatePath() {
    previous = current;

    // generate a noisy 3d position over time
    float t = (2 + ofGetElapsedTimef()) * .1;
    current.x = ofSignedNoise(t, 0, 0);
    current.y = ofSignedNoise(0, t, 0);
    current.z = ofSignedNoise(0, 0, t);
    current *= 1000; // scale from -1,+1 range to -400,+400

    // add the current position to the pathVertices deque
    pathVertices.push_back(current);
    // if we have too many vertices in the deque, get rid of the oldest ones
    while (pathVertices.size() > 200) {
        pathVertices.pop_front();
    }
}

void DemoController::drawRange() const {
    for (auto x = -this->range; x < this->range; x += 50) {

    }

}
