//
// Created by Grégoire GUEMAS on 18-02-16.
//

#include <graphics/ofGraphics.h>
#include "CircleCursor.h"

void CircleCursor::draw() {
    ofSetColor(ofColor::black);
    ofDrawCircle(this->point, 4);
    ofSetColor(ofColor::white);
}
