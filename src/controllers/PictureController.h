//
// Created by Grégoire GUEMAS on 18-02-15.
//

#ifndef IFT_3100_PICTURECONTROLLER_H
#define IFT_3100_PICTURECONTROLLER_H


#include <graphics/ofImage.h>
#include "AController.h"

typedef std::shared_ptr<ofImage> ofImagePtr;

class PictureController : public AController {
public:
    void setup() override;

    void draw() override;

    void addImage(const ofImagePtr &image);

    void saveCurrent(const std::string &path);

    /**
     * Load image from path
     * @throw std::runtime_error in case of invalid path
     * @param path to an image file
     */
    void loadFrom(const std::string &path);

protected:
    void enableEvents() override;

    void disableEvents() override;

private:
    std::list<ofImagePtr> list = std::list<ofImagePtr>();
    std::list<ofImagePtr>::const_iterator it = list.end();

    void onKeyRelease(ofKeyEventArgs &evt);
};


#endif //IFT_3100_PICTURECONTROLLER_H
