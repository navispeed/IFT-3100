//
// Created by Grégoire GUEMAS on 18-02-15.
//

#include <graphics/ofPolyline.h>
#include "of2dFactory.h"
#include "of2dObject.h"

std::shared_ptr<of2d> of2dFactory::getLine() {
    auto polyline = std::make_shared<ofPolyline>();
    auto instance2d = new of2dObject<ofPolyline>(polyline);
    return std::shared_ptr<of2d>(instance2d);
}

std::shared_ptr<of2d> of2dFactory::getCircle() {
//    return std::make_shared<of2d>(new of());
	return nullptr;
}

std::shared_ptr<of2d> of2dFactory::getRectangle() {
//    return std::make_shared<of2d>(new ofPolyline());
	return nullptr;
}
