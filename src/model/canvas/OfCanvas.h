//
// Created by Grégoire GUEMAS on 18-02-15.
//

#ifndef IFT_3100_OFCANVAS_H
#define IFT_3100_OFCANVAS_H


#include <list>
#include <ofNode.h>
#include <graphics/ofImage.h>
#include "../of2d/of2d.h"
#include "../../controllers/PictureController.h"

class OfCanvas : public ofNode {
    std::list<std::shared_ptr<of2d>> object = std::list<std::shared_ptr<of2d>>();
    ofImagePtr capture;
public:
    OfCanvas(const list<shared_ptr<of2d>> &object, ofImage *capture);

    list<shared_ptr<of2d>> getObject() const;

    const ofImagePtr &getCapture() const;

    void customDraw(const ofBaseRenderer *renderer) const override;


};

typedef std::shared_ptr<OfCanvas> OfCanvasPtr;

#endif //IFT_3100_OFCANVAS_H
