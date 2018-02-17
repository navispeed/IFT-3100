//
// Created by Grégoire GUEMAS on 18-02-16.
//

#include "HistoryManager.h"

HistoryManager *HistoryManager::getInstance() {
    static HistoryManager hm;
    return &hm;
}

HistoryManager::HistoryManager() {
    ofAddListener(ofEvents().keyPressed, this, &HistoryManager::onKeyPress);
    ofAddListener(ofEvents().keyReleased, this, &HistoryManager::onKeyRelease);
}

History *HistoryManager::getFromController(AController *currentController) {
    if (this->manager.count(currentController) == 0) {
        this->manager[currentController] = History();
    }
    this->last = &this->manager.at(currentController);
    return this->last;
}

void HistoryManager::onKeyPress(ofKeyEventArgs &evt) {
    if (this->last == nullptr) {
        return;
    }
    this->keyPressed[evt.key] = true;
//    std::cout << "TEST" << (this->keyPressed[4252] || this->keyPressed[4253]) << this->keyPressed[122] << std::endl;
//    if ((this->keyPressed[4252] || this->keyPressed[4253]) && this->keyPressed[122]) { //undo
    if (this->keyPressed[90]) { //undo
        this->last->undo();
    }
    if ( this->keyPressed[82]) { //redo
        this->last->redo();
    }
}

void HistoryManager::onKeyRelease(ofKeyEventArgs &evt) {
    this->keyPressed[evt.key] = false;
}
