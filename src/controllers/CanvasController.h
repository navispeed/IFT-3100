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
#include <services/history/History.h>
#include <model/constant.h>
#include <services/drawOption/DrawOption.h>
#include "ofxDatGui.h"


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
        REC_TREE = 121,
        SIERPINSKI = 115,
    };
    static const std::map<int, const char *> stateToString;

	CanvasController();

    void setup() override;

    void draw() override;

    void setState(CanvasController::STATE state);

    void reset();

    void load(OfCanvasPtr canvas);

	void load(std::string &path);

	void save(std::string &path);

    OfCanvasPtr getCanvas();

protected:
    void enableEvents() override;

    void disableEvents() override;

private:
    std::shared_ptr<ofVec2f> initialPoint = nullptr;
    std::vector<ofVec2f> pointList = std::vector<ofVec2f>();
    std::list<otherObjectDrawCall> otherObject = std::list<otherObjectDrawCall>();
    STATE state = NONE;
    OfCanvasPtr canvas = nullptr;
    History *history = nullptr;
    DrawOption *drawOption = DrawOption::getInstance();
	ofxDatGui *gui = nullptr;
	ofxDatGuiColorPicker *colorFillPicker = nullptr;
	ofxDatGuiColorPicker *colorOutLinePicker = nullptr;
	ofxDatGuiSlider *weightSlider = nullptr;

    void onMouseRelease(ofMouseEventArgs &evt);

    void onMousePressed(ofMouseEventArgs &evt);

    void onKeyRelease(ofKeyEventArgs &);

    ofColor randomColor() const;

    void drawRectangleFromPoint(const ofColor &color, const vector<ofVec2f> &pointList);

    void drawTriangleFromPoint(const ofColor &color, const vector<ofVec2f> &pointList);

    void drawPolygon(const ofColor &color, const vector<ofVec2f> &pointList);

    otherObjectDrawCall drawIt(otherObjectDrawCall fct, bool toFill);
};


#endif //IFT_3100_CANVAS_H
