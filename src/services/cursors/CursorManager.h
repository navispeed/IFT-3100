//
// Created by Grégoire GUEMAS on 18-02-16.
//

#ifndef IFT_3100_CURSORFACTORY_H
#define IFT_3100_CURSORFACTORY_H


#include "Cursor.h"
#include "CircleCursor.h"
#include "SphereCursor.h"
#include "CubeCursor.h"
#include "CylinderCursor.h"
#include "ConeCursor.h"

class CursorManager {
public:
    enum CURSOR_TYPE {
        DEFAULT,
        CIRCLE,
        LINE,
		SPHERE,
		CUBE,
		CYLINDER,
		CONE
    };

    void setDefaultCursor();

    void setCursor(CURSOR_TYPE type);

    void draw();

    static CursorManager *getInstance();


private:
    Cursor *instance = nullptr;
};


#endif //IFT_3100_CURSORFACTORY_H
