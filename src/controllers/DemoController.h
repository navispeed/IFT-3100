//
// Created by Grégoire GUEMAS on 18-03-30.
//

#ifndef IFT_3100_DEMO_H
#define IFT_3100_DEMO_H


#include <ofEasyCam.h>
#include "AController.h"

class DemoController : public AController {
public:
    void setup() override;

    void draw() override;

protected:
    void enableEvents() override;

    void disableEvents() override;

private:

    //Box

    ofVec3f previous, current;

    deque<ofVec3f> pathVertices;
    ofMesh pathLines;

    std::set<std::pair<float, float>> traveledPath;

    //end

    //Cameras
    ofCamera top;
    ofEasyCam easyCam;

    ofRectangle viewport[2];


    int range = 400;

    void generatePath();

    void drawEnv();

    void drawCube();

    void drawTraveledPath() const;
    void drawRange() const;

    void drawScene(ofCamera cam);
};


#endif //IFT_3100_DEMO_H
