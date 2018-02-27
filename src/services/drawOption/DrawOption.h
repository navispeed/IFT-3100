//
// Created by Grégoire GUEMAS on 18-02-25.
//

#ifndef IFT_3100_DRAWOPTION_H
#define IFT_3100_DRAWOPTION_H


#include <types/ofColor.h>

class DrawOption {

public:
    static DrawOption* getInstance();

    float getWeight() const;

    void setWeight(float weight);

    const ofColor &getOutLineColor() const;

    void setOutLineColor(const ofColor &outLineColor);

    const ofColor &getFillColor() const;

    void setFillColor(const ofColor &fillColor);

    const ofColor &getBackgroundColor() const;

    void setBackgroundColor(const ofColor &backgroundColor);

private:
    DrawOption() = default;
    float weight = 3.0;
    ofColor outLineColor = ofColor::red;
    ofColor fillColor = ofColor(200, 0, 0, 200);
    ofColor backgroundColor = ofColor::lightGrey;
};


#endif //IFT_3100_DRAWOPTION_H
