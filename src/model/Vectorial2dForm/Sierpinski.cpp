//
// Created by Grégoire GUEMAS on 18-02-16.
//

#include "Sierpinski.h"

Sierpinski::Sierpinski(const ofVec2f startPoint, float startLength) : axiom("A"),
                                                                      ruleA("B-A-B"),
                                                                      ruleB("A+B+A"),
                                                                      startLength(startLength),
                                                                      angle((60.0)),
                                                                      height(100),
                                                                      startPoint(startPoint) {
    reset();
}

void Sierpinski::reset() {
    production = axiom;
    drawLength = startLength;
    generations = 0;
    steps = 0;
}

int Sierpinski::getAge() {
    return generations;
}

void Sierpinski::render(const std::string &p) {
    this->production = p;
    ofPushMatrix();
    ofTranslate(this->startPoint);
    steps = static_cast<int>(production.length());
    for (unsigned long i = 0; i < steps; i++) {
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

std::string Sierpinski::simulate(int gen) {
    while (getAge() < gen) {
        production = iterate(production, ruleA, ruleB);
    }
    return production;
}

std::string Sierpinski::iterate(std::string &prod_, std::string &ruleA_, std::string &ruleB_) {
    drawLength = drawLength * 0.6;
    generations++;
    std::string newProduction;
    for (char i : prod_) {
        if (i == 'A') {
            newProduction += ruleA_;
        } else if (i == 'B') {
            newProduction += ruleB_;
        } else {
            newProduction += i;
        }
    }
    return newProduction;
}
