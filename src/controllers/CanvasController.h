//
// Created by Grégoire GUEMAS on 18-02-15.
//

#ifndef IFT_3100_CANVAS_H
#define IFT_3100_CANVAS_H

#include <app/ofAppRunner.h>
#include <ofPoint.h>
#include <ofEvent.h>
#include "AController.h"
#include "../model/of2d/of2d.h"
#include "../model/canvas/OfCanvas.h"


class CanvasController : public AController {

public:
    enum STATE : int {
        NONE = 127,
        POINT = 112,
        LINE = 108,
        CIRCLE = 99,
        RECTANGLE = 114
    };
    static const std::map<int, const char *> stateToString;

    void setup() override;

    void draw() override;

    void setState(CanvasController::STATE state);

    void reset();

    void load(OfCanvasPtr canvas);

    OfCanvasPtr getCanvas();

protected:
    void enableEvents() override;

    void disableEvents() override;

private:
    std::shared_ptr<ofPoint> initialPoint = nullptr;
    std::list<std::shared_ptr<of2d>> object = std::list<std::shared_ptr<of2d>>();
    STATE state = NONE;
    OfCanvasPtr canvas = nullptr;

    void onMouseRelease(ofMouseEventArgs &evt);

    void onMousePressed(ofMouseEventArgs &evt);

    void onKeyRelease(ofKeyEventArgs &);
};


#endif //IFT_3100_CANVAS_H
