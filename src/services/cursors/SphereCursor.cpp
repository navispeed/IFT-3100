#include <graphics/of3dGraphics.h>
#include <graphics/ofGraphics.h>
#include "SphereCursor.h"

void SphereCursor::draw() {
	ofSetColor(ofColor::black);
	ofDrawSphere(this->point, 5);
	ofSetColor(ofColor::white);
}