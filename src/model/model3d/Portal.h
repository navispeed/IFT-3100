//
// Created by Grégoire GUEMAS on 18-03-22.
//

#ifndef IFT_3100_PORTAL_H
#define IFT_3100_PORTAL_H


#include <ofVec3f.h>
#include <ofMesh.h>

class Portal {
private:
    ofVec3f start;
    ofVec3f end;
    ofMesh portals[2];

public:
    Portal(const ofVec3f &start, const ofVec3f &end);
    void draw();
};

#endif //IFT_3100_PORTAL_H
