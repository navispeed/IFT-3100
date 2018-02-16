//
// Created by Grégoire GUEMAS on 18-02-15.
//

#ifndef IFT_3100_OF2DOBJECT_H
#define IFT_3100_OF2DOBJECT_H

#include <memory>
#include "of2d.h"

template<class T>
class of2dObject : public of2d {
    std::shared_ptr<T> instance;
public:
    explicit of2dObject(const shared_ptr<T> &instance) : instance(instance) {}

    const shared_ptr<T> &getInstance() const {
        return instance;
    }

    void draw() override {
        this->instance->draw();
    }
};

#endif //IFT_3100_OF2DOBJECT_H
