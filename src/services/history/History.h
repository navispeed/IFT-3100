//
// Created by Grégoire GUEMAS on 18-02-16.
//

#ifndef IFT_3100_HISTORY_H
#define IFT_3100_HISTORY_H


#include <functional>
#include <stack>

class History {
public:
    typedef std::function<void()> PtrXXdo;

    void add(PtrXXdo undo, PtrXXdo redo);

    void clearRedo();

    void undo();

    void redo();

private:
    std::stack<std::pair<PtrXXdo, PtrXXdo>> undoAction;
    std::stack<PtrXXdo> redoAction;
};


#endif //IFT_3100_HISTORY_H
