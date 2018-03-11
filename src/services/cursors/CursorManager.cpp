//
// Created by Grégoire GUEMAS on 18-02-16.
//

#include "CursorManager.h"
#include "DefaultCursor.h"
#include "LineCursor.h"

void CursorManager::setDefaultCursor() {
    this->instance->disable();
    delete (this->instance);
    this->instance = new CircleCursor();

}

void CursorManager::setCursor(CursorManager::CURSOR_TYPE type) {
    this->instance->disable();
    delete (this->instance);
    switch (type) {
        case DEFAULT:
            this->instance = new DefaultCursor();;
            break;
        case CIRCLE:
            this->instance = new CircleCursor();
            break;
        case LINE:
            this->instance = new LineCursor();
            break;
		case SPHERE:
			this->instance = new SphereCursor();
			break;
		case CUBE:
			this->instance = new CubeCursor();
			break;
		case CYLINDER:
			this->instance = new CylinderCursor();
			break;
		case CONE:
			this->instance = new ConeCursor();
			break;
    }
    this->instance->enable();
}

CursorManager *CursorManager::getInstance() {
    static auto instance = new CursorManager();
    instance->setDefaultCursor();
    return instance;
}

void CursorManager::draw() {
    this->instance->draw();
}
