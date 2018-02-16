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

#define LIST_CONTAIN_0_ELEMENT(cond, action) if (cond) {action; return;}
#define DISTANCE_BTW_POINT(point1, point2) ((point1 > point2) ? point1 - point2 : point2 - point1);

class CanvasController : public AController {
    const ofColor defColor = ofColor(255, 255, 255);
public:
    enum STATE : int {
        NONE = 127,
        CIRCLE = 99,
        LINE = 108,
        POLYGONE = 112,
        RECTANGLE = 114,
        TRIANGLE = 116,
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
    typedef std::function<void()> otherObjectDrawCall;
    std::shared_ptr<ofVec2f> initialPoint = nullptr;
    std::vector<ofVec2f> pointList = std::vector<ofVec2f>();
    std::list<std::shared_ptr<of2d>> object = std::list<std::shared_ptr<of2d>>();
    std::list<otherObjectDrawCall> otherObject = std::list<otherObjectDrawCall>();
    STATE state = NONE;
    OfCanvasPtr canvas = nullptr;

    void onMouseRelease(ofMouseEventArgs &evt);

    void onMousePressed(ofMouseEventArgs &evt);

    void onKeyRelease(ofKeyEventArgs &);

    ofColor randomColor() const;

    void drawRectangleFromPoint(const ofColor &color);

    void drawTriangleFromPoint(const ofColor &color);

    void drawPolygon(const ofColor &color);
};


#endif //IFT_3100_CANVAS_H
