//
// Created by Grégoire GUEMAS on 18-02-15.
//

#include "ControllerFactory.h"
#include "CanvasController.h"

AController *ControllerFactory::getDefaultController() {
    auto *canvas = getCanvasController();
    return canvas;
}

CanvasController *ControllerFactory::getCanvasController() {
    static auto instance = new CanvasController();
    init(instance);
    return instance;
}

PictureController *ControllerFactory::getPictureController() {
    static auto instance = new PictureController();
    init(instance);
    return instance;
}

void ControllerFactory::init(AController *controller) {

}
