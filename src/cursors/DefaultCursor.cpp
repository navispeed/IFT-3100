//
// Created by Grégoire GUEMAS on 18-02-16.
//

#include "DefaultCursor.h"

void DefaultCursor::enable() {
    Cursor::enable();
    ofShowCursor();
}

void DefaultCursor::mouseEvent(ofMouseEventArgs &evt) {
    //Nothing to do
}

void DefaultCursor::draw() {

}
