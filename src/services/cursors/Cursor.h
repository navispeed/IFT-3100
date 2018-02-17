//
// Created by Grégoire GUEMAS on 18-02-16.
//

#ifndef IFT_3100_ICURSOR_H
#define IFT_3100_ICURSOR_H

#include <events/ofEvents.h>
#include <app/ofAppRunner.h>


class Cursor {
public:
    virtual void enable() {
        ofHideCursor();
        ofAddListener(ofEvents().mouseMoved, this, &Cursor::mouseEvent);
        ofAddListener(ofEvents().mouseDragged, this, &Cursor::mouseEvent);
    };

    virtual void disable() final {
        ofRemoveListener(ofEvents().mouseMoved, this, &Cursor::mouseEvent);
        ofRemoveListener(ofEvents().mouseDragged, this, &Cursor::mouseEvent);
        ofShowCursor();
    };

    virtual void draw() = 0;

protected:
    ofMouseEventArgs point;

    virtual void mouseEvent(ofMouseEventArgs &evt) {
        this->point = evt;
    };
};

#endif //IFT_3100_ICURSOR_H
