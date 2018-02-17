//
// Created by Grégoire GUEMAS on 18-02-16.
//

#include "History.h"

void History::add(History::PtrXXdo undo, History::PtrXXdo redo) {
    this->undoAction.push(std::make_pair(undo, redo));
}

void History::undo() {
    if (this->undoAction.empty()) {
        return;
    }
    std::pair<PtrXXdo, PtrXXdo> pair = this->undoAction.top();
    this->undoAction.pop();
    this->redoAction.push(pair.second);
    pair.first();
}

void History::redo() {
    if (this->redoAction.empty()) {
        return;
    }
    std::function<void()> redoFct = this->redoAction.top();
    this->redoAction.pop();
    redoFct();
}

void History::clearRedo() {
    this->redoAction = std::stack<PtrXXdo>();
}
