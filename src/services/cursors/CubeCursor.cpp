
#include <graphics/of3dGraphics.h>
#include <graphics/ofGraphics.h>
#include "CubeCursor.h"

void CubeCursor::draw() {
	ofSetColor(ofColor::black);
	ofDrawBox(this->point, 7);
	ofSetColor(ofColor::white);
}