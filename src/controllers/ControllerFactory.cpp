#include "ControllerFactory.h"

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

Model3dController *ControllerFactory::getModel3dController() {
	static auto instance = new Model3dController();
	init(instance);
	return instance;
}

void ControllerFactory::init(AController *controller) {

}
