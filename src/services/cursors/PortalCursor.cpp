//
// Created by Grégoire GUEMAS on 18-03-22.
//

#include <ofGraphics.h>
#include "PortalCursor.h"

PortalCursor::PortalCursor() {
//    this->cursor = ofImage();
//    this->cursor.load("Blue_Portal.png");
}

void PortalCursor::draw() {
    ofPushStyle();
    ofSetColor(ofColor::lightBlue);
    ofDrawEllipse(this->point, 18, 28);
//    ofSetColor(ofColor::red);
//    ofDrawEllipse(this->point, 28, 38);
    ofPopStyle();
//    this->cursor.draw(this->point, 48, 38);
}

