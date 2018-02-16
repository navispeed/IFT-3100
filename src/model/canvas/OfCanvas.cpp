//
// Created by Grégoire GUEMAS on 18-02-15.
//

#include <graphics/ofGraphics.h>
#include "OfCanvas.h"

OfCanvas::OfCanvas(const list<shared_ptr<of2d>> &object, ofImage *capture) : object(object), capture(std::shared_ptr<ofImage>(capture)) {
}

list<shared_ptr<of2d>> OfCanvas::getObject() const {
    return object;
}

void OfCanvas::customDraw(const ofBaseRenderer *renderer) const {
//    renderer->rotate()

    ofImage &poly = *((ofImage *) this);
    const ofQuaternion &orientation = this->getGlobalOrientation();
//    renderer->rotate( orientation1.(), );
//    poly.draw(this->getPosition().x, this->getPosition().y, this->getPosition().z);
    renderer->draw(poly, this->getPosition().x, this->getPosition().y, this->getPosition().z, poly.getHeight(),
                   poly.getWidth(), 0, 0, poly.getHeight(), poly.getWidth());
    ofNode::customDraw(renderer);
}

const ofImagePtr &OfCanvas::getCapture() const {
    return capture;
}
