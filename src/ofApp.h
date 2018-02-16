#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "controllers/AController.h"
#include "cursors/CursorManager.h"


class ofApp : public ofBaseApp {

public:
    void setup() override;

    void update() override;

    void draw() override;

    void keyPressed(int key) override;

    void keyReleased(int key) override;

    void mouseMoved(int x, int y) override;

    void mouseDragged(int x, int y, int button) override;

    void mousePressed(int x, int y, int button) override;

    void mouseReleased(int x, int y, int button) override;

    void mouseEntered(int x, int y) override;

    void mouseExited(int x, int y) override;

    void windowResized(int w, int h) override;

    void dragEvent(ofDragInfo dragInfo) override;

    void gotMessage(ofMessage msg) override;

    void mouseScrolled(int x, int y, float scrollX, float scrollY) override;

private:
//    std::vector<std::shared_ptr<IofObject>> test;
//    ofEasyCam cam;
//    double nbStep = 10;
//
//
//    ofxFloatSlider radius;
//    ofxColorSlider color;
//    ofxVec2Slider center;
//    ofxIntSlider circleResolution;
//    ofxToggle filled;
//    ofxButton twoCircles;
//    ofxButton ringButton;
//    ofxLabel screenSize;
//
//    ofxPanel gui;
    AController *controller;
    CursorManager *pManager;
};
