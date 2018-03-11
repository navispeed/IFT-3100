//
// Created by Grégoire GUEMAS on 18-02-15.
//

#ifndef IFT_3100_ACONTROLLER_H
#define IFT_3100_ACONTROLLER_H

#include <services/cursors/CursorManager.h>
#include "vector"

class AController {

public:

    virtual void setup() = 0;

    virtual void draw() = 0;

    virtual void setEnable(bool enabled) final {
        CursorManager::getInstance()->setDefaultCursor();
        this->enabled = enabled;
        if (this->enabled) {
            this->enableEvents();
        } else {
            this->disableEvents();
        }
    }

protected:
    virtual void enableEvents() = 0;

    virtual void disableEvents() = 0;

	void showError(const std::string &message);

private:
    bool enabled = false;
};


#endif //IFT_3100_ACONTROLLER_H
