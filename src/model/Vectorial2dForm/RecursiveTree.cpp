//
// Created by Grégoire GUEMAS on 18-02-16.
//

#include <graphics/ofGraphics.h>
#include "RecursiveTree.h"

#include <math.h>

#define degToRad(angleInDegrees) ((angleInDegrees) * M_PI / 180.0)
#define radToDeg(angleInRadians) ((angleInRadians) * 180.0 / M_PI)

RecursiveTree::RecursiveTree(int nbIt, int angle) : height(nbIt), angle(angle) {}


void RecursiveTree::draw(ofVec2f f) {
    ofSetColor(ofColor::black);
    auto angle = this->angle;
    ofPushMatrix();
    ofTranslate(f);
    ofDrawLine(ofVec3f(0, 0), ofVec3f(0, -this->height));
    branch(this->height, angle);
    ofSetColor(ofColor::white);
    ofPopMatrix();
}

void RecursiveTree::branch(int h, double d) {
    h *= 0.66;
    if (h <= 2) return;
    
    ofPushMatrix();
    ofRotate(static_cast<float>(d));
    ofDrawLine(ofVec3f(0, 0), ofVec3f(0, 0) + ofVec2f(0, -h));
    ofTranslate(0, -h);
    branch(h, d);
    ofPopMatrix();

    ofPushMatrix();
    ofRotate(-static_cast<float>(d));
    ofDrawLine(ofVec3f(0, 0), ofVec3f(0, 0) + ofVec2f(0, -h));
    ofTranslate(0, -h);
    branch(h, d);
    ofPopMatrix();
}

/*
 *

void branch(float h) {
  // Each branch will be 2/3rds the size of the previous one
  h *= 0.66;

  // All recursive functions must have an exit condition!!!!
  // Here, ours is when the length of the branch is 2 pixels or less
  if (h > 2) {
    pushMatrix();    // Save the current state of transformation (i.e. where are we now)
    rotate(theta);   // Rotate by theta
    line(0, 0, 0, -h);  // Draw the branch
    translate(0, -h); // Move to the end of the branch
    branch(h);       // Ok, now call myself to draw two new branches!!
    popMatrix();     // Whenever we get back here, we "pop" in order to restore the previous matrix state

    // Repeat the same thing, only branch off to the "left" this time!
    pushMatrix();
    rotate(-theta);
    line(0, 0, 0, -h);
    translate(0, -h);
    branch(h);
    popMatrix();
  }
}

 *
 * */