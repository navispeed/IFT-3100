#include "ControllerFactory.h"

AController *ControllerFactory::getDefaultController() {
    auto *canvas = getCanvasController();
    return canvas;
}

CanvasController *ControllerFactory::getCanvasController() {
    return get<CanvasController>();
}

PictureController *ControllerFactory::getPictureController() {
    return get<PictureController>();
}

Model3dController *ControllerFactory::getModel3dController() {
    return get<Model3dController>();
}

DemoController *ControllerFactory::getDemoController() {
    return get<DemoController>();
}

void ControllerFactory::init(AController *controller) {

}

template<class T>
T *ControllerFactory::get() {
    static AController* instance = new T();
    return dynamic_cast<T *>(instance);
}
