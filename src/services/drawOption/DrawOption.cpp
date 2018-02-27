//
// Created by Grégoire GUEMAS on 18-02-25.
//

#include "DrawOption.h"

DrawOption *DrawOption::getInstance() {
    static DrawOption drawOption;
    return &drawOption;
}

float DrawOption::getWeight() const {
    return weight;
}

void DrawOption::setWeight(float weight) {
    DrawOption::weight = weight;
}

const ofColor &DrawOption::getOutLineColor() const {
    return outLineColor;
}

void DrawOption::setOutLineColor(const ofColor &outLineColor) {
    DrawOption::outLineColor = outLineColor;
}

const ofColor &DrawOption::getFillColor() const {
    return fillColor;
}

void DrawOption::setFillColor(const ofColor &fillColor) {
    DrawOption::fillColor = fillColor;
}

const ofColor &DrawOption::getBackgroundColor() const {
    return backgroundColor;
}

void DrawOption::setBackgroundColor(const ofColor &backgroundColor) {
    DrawOption::backgroundColor = backgroundColor;
}
