#include "ofApp.h"
#include "controllers/ControllerFactory.h"
#include "services/cursors/CursorManager.h"

//--------------------------------------------------------------
void ofApp::setup() {
//    ofPolyline line;
//    ofSetLineWidth(30.0f);
//    line.addVertex(0, 0);
//    line.addVertex(1024, 768);
//    ofEnableAntiAliasing();
//    ofSetFrameRate(30);
//    ofSetBackgroundColor(0, 0, 0);
//    ofSetColor(255, 0, 0);
////    this->test = ofObjectFactory::createFrom(line);
//
//    gui.setup(); // most of the time you don't need a name
//    gui.add(filled.setup("fill", true));
//    gui.add(radius.setup("radius", 140, 10, 300));
//    gui.add(center.setup("center", ofVec2f(ofGetWidth() * .5, ofGetHeight() * .5), ofVec2f(0, 0),
//                         ofVec2f(ofGetWidth(), ofGetHeight())));
//    gui.add(color.setup("color", ofColor(100, 100, 140), ofColor(0, 0), ofColor(255, 255)));
//    gui.add(circleResolution.setup("circle res", 5, 3, 90));
//    gui.add(twoCircles.setup("two circles"));
//    gui.add(ringButton.setup("ring"));
//    gui.add(screenSize.setup("screen size", ofToString(ofGetWidth()) + "x" + ofToString(ofGetHeight())));
    ofSetFrameRate(30);
    pManager = CursorManager::getInstance();
    this->controller = ControllerFactory::getDefaultController();
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
    ofSetColor(ofColor::white);
    this->controller->draw();
    pManager->draw();
//    ofSpherePrimitive sphere;
//
////    sphere.setPosition(0, 0, 0);
////    sphere.setRadius(10);
////    sphere.draw();
//    cam.begin();
//    std::vector<ofColor> colors;
//
//    ofDrawGrid(20, nbStep, false, true, true, true);
//    ofDisableDepthTest();
//
//    cam.end();
//    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    auto old = this->controller;
    switch (key) {
        case 49:
            std::cout << "Controller Picture" << std::endl;
            this->pManager->setDefaultCursor();
            this->controller = ControllerFactory::getPictureController();
            break;
        case 50:
            std::cout << "Controller 2D" << std::endl;
            this->pManager->setDefaultCursor();
            this->controller = ControllerFactory::getCanvasController();
            break;
        case 51:
            std::cout << "Controller 3D" << std::endl;
            this->pManager->setDefaultCursor();
			this->controller = ControllerFactory::getModel3dController();
            break;
        default:
            return;
    }
    old->setEnable(false);

    controller->setup();
    controller->setEnable(true);
    std::cout << "key:" << key << std::endl;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY) {
//    std::cout << cam.getDistance() << "\t:" << nbStep << "\t:" << ((10.0 / 650) * cam.getDistance()) << std::endl;
//    this->nbStep = (10.0 / 650) * cam.getDistance();
}
