//
// Created by Grégoire GUEMAS on 18-02-15.
//

#ifndef IFT_3100_OF2DFACTORY_H
#define IFT_3100_OF2DFACTORY_H


#include <memory>
#include "of2d.h"

class of2dFactory {
public:
    static std::shared_ptr<of2d> getLine();
    static std::shared_ptr<of2d> getCircle();
    static std::shared_ptr<of2d> getRectangle();
};


#endif //IFT_3100_OF2DFACTORY_H
