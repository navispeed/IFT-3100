//
// Created by Grégoire GUEMAS on 18-02-16.
//

#include <graphics/ofGraphics.h>
#include "LineCursor.h"

static const int LINE_LENGTH = 4;

void LineCursor::draw() {
    ofSetColor(ofColor::black);
    ofDrawLine(this->point + ofPoint(-LINE_LENGTH, LINE_LENGTH), this->point + ofPoint(LINE_LENGTH, -LINE_LENGTH));
    ofSetColor(ofColor::white);
}