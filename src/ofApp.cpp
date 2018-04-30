#include "ofApp.h"
#include "controllers/ControllerFactory.h"

//--------------------------------------------------------------
void ofApp::setup() {
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
        case 52:
            std::cout << "Controller Demo" << std::endl;
            this->pManager->setDefaultCursor();
            this->controller = ControllerFactory::getDemoController();
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

}
