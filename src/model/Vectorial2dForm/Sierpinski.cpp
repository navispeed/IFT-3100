//
// Created by Grégoire GUEMAS on 18-02-16.
//

#include "Sierpinski.h"

LSystem::LSystem(const ofVec2f startPoint, float startLength) : axiom("A"),
                                             ruleA("B-A-B"),
                                             ruleB("A+B+A"),
                                             startLength(startLength),
                                             angle((60.0)),
                                             height(100),
                                             startPoint(startPoint) {
    reset();
}

void LSystem::reset() {
    production = axiom;
    drawLength = startLength;
    generations = 0;
    steps = 0;
}

int LSystem::getAge() {
    return generations;
}

void LSystem::render(const std::string &p) {
    this->production = p;
    ofPushMatrix();
    ofTranslate(this->startPoint);
    steps = static_cast<int>(production.length());
    for (int i = 0; i < steps; i++) {
        char step = production.at(i);
        if ((step == 'A') || (step == 'B')) {
            ofDrawLine(0, 0, drawLength, 0);
            ofTranslate(drawLength, 0);
        } else if (step == '+') {
            ofRotate(-angle);
        } else if (step == '-') {
            ofRotate(+angle);
        }
    }
    ofPopMatrix();
}

std::string LSystem::simulate(int gen, int step_inc_) {
    while (getAge() < gen) {
        production = iterate(production, ruleA, ruleB);
    }
    step_inc = step_inc_;
    return production;
}

std::string LSystem::iterate(std::string &prod_, std::string &ruleA_, std::string &ruleB_) {
    drawLength = drawLength * 0.6;
    generations++;
    std::string newProduction = "";
    for (int i = 0; i < prod_.length(); i++) {
        if (prod_.at(i) == 'A') {
            newProduction += ruleA_;
        } else if (prod_.at(i) == 'B') {
            newProduction += ruleB_;
        } else {
            newProduction += prod_.at(i);
        }
    }
    return newProduction;
}
