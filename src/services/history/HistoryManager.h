//
// Created by Grégoire GUEMAS on 18-02-16.
//

#ifndef IFT_3100_HISTORYMANAGER_H
#define IFT_3100_HISTORYMANAGER_H


#include <controllers/AController.h>
#include <model/singleton/Singleton.h>
#include "History.h"

class HistoryManager {
public:
    static HistoryManager *getInstance();
    HistoryManager();
    History *getFromController(AController *currentController);


private:
    History *last;
    std::map<AController *, History> manager;
    std::unordered_map<int, bool> keyPressed;
    void onKeyPress(ofKeyEventArgs &evt);
    void onKeyRelease(ofKeyEventArgs &evt);
};

#endif //IFT_3100_HISTORYMANAGER_H
