#include <graphics/of3dGraphics.h>
#include <graphics/ofGraphics.h>
#include "CylinderCursor.h"

void CylinderCursor::draw() {
	ofSetColor(ofColor::black);
	ofDrawCylinder(this->point, 5, 12);
	ofSetColor(ofColor::white);
}