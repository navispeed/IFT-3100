//
// Created by Grégoire GUEMAS on 18-02-16.
//

#ifndef IFT_3100_DEFAULTCURSOR_H
#define IFT_3100_DEFAULTCURSOR_H


#include "Cursor.h"

class DefaultCursor: public Cursor  {
public:
    void enable() override final;

    void draw() override;

protected:
    void mouseEvent(ofMouseEventArgs &evt) override;
};


#endif //IFT_3100_DEFAULTCURSOR_H
