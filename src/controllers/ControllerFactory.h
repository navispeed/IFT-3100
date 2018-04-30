//
// Created by Grégoire GUEMAS on 18-02-15.
//

#ifndef IFT_3100_CONTROLLERFACTORY_H
#define IFT_3100_CONTROLLERFACTORY_H


#include "AController.h"
#include "CanvasController.h"
#include "PictureController.h"
#include "Model3dController.h"
#include "DemoController.h"

class ControllerFactory {
private:
    static void init(AController *);
	template<class T>
	static T* get();
public:
    static AController* getDefaultController();
    static CanvasController* getCanvasController();
    static PictureController* getPictureController();
	static Model3dController * getModel3dController();
	static DemoController * getDemoController();
};


#endif //IFT_3100_CONTROLLERFACTORY_H
