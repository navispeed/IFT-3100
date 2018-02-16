//
// Created by Grégoire GUEMAS on 18-02-15.
//

#include <ofMain.h>
#include "PictureController.h"

void PictureController::setup() {
    ofSetWindowTitle("Aperçu image");
}

void PictureController::draw() {
    if (this->list.size() == 0) {
        return;
    }
    auto img = *it;
    img->draw(0, 0, img->getWidth(), img->getHeight());
}

void PictureController::enableEvents() {
    std::cout << this->list.size() << " elemnt present" << std::endl;
    ofAddListener(ofEvents().keyReleased, this, &PictureController::onKeyRelease);
}

void PictureController::disableEvents() {
    ofRemoveListener(ofEvents().keyReleased, this, &PictureController::onKeyRelease);
}

void PictureController::addImage(const ofImagePtr &image) {
    this->list.push_back(image);
    if (this->list.size() == 1) {
        this->it = this->list.begin();
    }
}

void PictureController::onKeyRelease(ofKeyEventArgs &evt) {
    if (this->list.size() == 0) {
        return;
    }
    switch (evt.key) {
        case 356:
            if (this->it == this->list.begin()) {
                this->it = this->list.end();
            }
            this->it--;
            break;
        case 358:
            this->it++;
            if (this->it == this->list.end()) {
                this->it = this->list.begin();
                return;
            }
            break;
        default:break;
    }
}
