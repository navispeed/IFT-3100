
#include <graphics/of3dGraphics.h>
#include <graphics/ofGraphics.h>
#include "ConeCursor.h"

void ConeCursor::draw() {
	ofSetColor(ofColor::black);
	ofDrawCone(point, 7, 9);
	ofSetColor(ofColor::white);
}