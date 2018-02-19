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
#include <model/constant.h>

class OfCanvas : public ofNode {
    std::list<otherObjectDrawCall> otherObject = std::list<otherObjectDrawCall>();
    ofImagePtr capture;
public:
    OfCanvas(const std::list<otherObjectDrawCall> &object, ofImage *capture);

    std::list<otherObjectDrawCall> getObject() const;

    const ofImagePtr &getCapture() const;

    void customDraw(const ofBaseRenderer *renderer) const override;


};

typedef std::shared_ptr<OfCanvas> OfCanvasPtr;

#endif //IFT_3100_OFCANVAS_H
