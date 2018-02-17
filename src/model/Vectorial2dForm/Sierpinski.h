//
// Created by Grégoire GUEMAS on 18-02-16.
//

#ifndef IFT_3100_LSYSTEM_H
#define IFT_3100_LSYSTEM_H


#include <string>
#include <graphics/ofGraphics.h>

class LSystem {


    int steps = 0;
    int step_inc = 1;

    std::string axiom;
    std::string ruleA;
    std::string ruleB;
    std::string production = "";
    const float height;
    const float startLength;
    const float angle;
    const ofVec2f startPoint;
    float drawLength = 0;
    int generations = 0;

public:
//    template <int gen, int inc>
//    struct simulate {
//        enum { value = N * Factorial<N - 1>::value };
//    };

    LSystem(const ofVec2f startPoint, float startLength = 9.0f);

    void reset();

    int getAge();

    void render(const std::string &p);

    std::string simulate(int gen, int step_inc_);

    std::string iterate(std::string &prod_, std::string &ruleA_, std::string &ruleB_);
};


#endif //IFT_3100_LSYSTEM_H
