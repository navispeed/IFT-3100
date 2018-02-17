//
// Created by Grégoire GUEMAS on 18-02-16.
//

#ifndef IFT_3100_RECURSIVETREE_H
#define IFT_3100_RECURSIVETREE_H


#include "Vectorial2dForn.h"

class RecursiveTree : public Vectorial2dForm {
public:
    RecursiveTree(int height = 120, int angle = 45);

    void draw(ofVec2f f) override;

private:
    int height;
    int angle;
    void branch(int h, double d);
};


#endif //IFT_3100_RECURSIVETREE_H
