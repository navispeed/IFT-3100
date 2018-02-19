//
// Created by Grégoire GUEMAS on 18-02-15.
//

#include <graphics/ofGraphics.h>
#include "OfCanvas.h"

OfCanvas::OfCanvas(const std::list<otherObjectDrawCall> &object, ofImage *capture) : otherObject(object), capture(std::shared_ptr<ofImage>(capture)) {
}

std::list<otherObjectDrawCall> OfCanvas::getObject() const {
    return otherObject;
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
