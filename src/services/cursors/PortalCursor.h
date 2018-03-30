//
// Created by Grégoire GUEMAS on 18-03-22.
//

#ifndef IFT_3100_PORTALCURSOR_H
#define IFT_3100_PORTALCURSOR_H


#import <ofImage.h>
#import "Cursor.h"

class PortalCursor : public Cursor {
public:
    PortalCursor();

    void draw() override;

    ofImage cursor;
};


#endif //IFT_3100_PORTALCURSOR_H
