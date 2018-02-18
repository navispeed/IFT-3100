//
// Created by Grégoire GUEMAS on 18-02-16.
//

#ifndef IFT_3100_LSYSTEM_H
#define IFT_3100_LSYSTEM_H


#include <string>
#include <graphics/ofGraphics.h>

class Sierpinski {


    int steps = 0;

    std::string axiom;
    std::string ruleA;
    std::string ruleB;
    std::string production = "";
    const float height;
    const float startLength;
    const float angle;
    const ofVec2f startPoint;
    double drawLength = 0;
    int generations = 0;

public:

    explicit Sierpinski(const ofVec2f startPoint = ofVec2f(0, 0), float startLength = 9.0f);

    void reset();

    std::string simulate(int gen);

    void render(const std::string &p);

private:

    int getAge();


    std::string iterate(std::string &prod_, std::string &ruleA_, std::string &ruleB_);
};


#endif //IFT_3100_LSYSTEM_H
