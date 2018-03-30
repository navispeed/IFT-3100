#pragma once

#include <app/ofAppRunner.h>
#include <ofEvent.h>
#include "AController.h"
#include <vector>
#include <model/model3d/Model3d.h>
#include <model/model3d/Primitive3d.h>
#include <services/history/History.h>
#include <model/constant.h>
#include <ofxAssimpModelLoader.h>
#include <services/textureModifier/TextureModifier.h>
#include <future>

enum class FormMode {
	NONE, MODEL1, MODEL2, BOX, SPHERE, CYLINDER, CONE, PORTAL
};
enum class TransformType {
	TRANSLATE, SCALE, ROTATE
};
class Model3dController : public AController {
private:
    typedef std::shared_ptr<ofxAssimpModelLoader> modelType;

    std::vector<modelType> modelsList;

    FormMode formMode = FormMode::NONE;
    TransformType transformType = TransformType::SCALE;


    const int TRANSLATEDISTANCE = 5;
    const int ROTATEDISTANCE = 1;
    const float SCALEDISTANCE = 0.05;

	int current = -1;

    int xRotate = ROTATEDISTANCE;
    float xScale = SCALEDISTANCE;
    int xTranslate = TRANSLATEDISTANCE;
    float yRotate = 0;
    float yScale = SCALEDISTANCE;
    int yTranslate = 0;
    float zRotate = 0;
    float zScale = SCALEDISTANCE;
    int zTranslate = 0;

	float camera_near;
	float camera_far;

	float camera_fov;

    std::vector<Object3d_Ptr> container;
    std::vector<Object3d_Ptr> selection;
    std::shared_ptr<ofVec3f> initialPoint = nullptr;
    std::vector<otherObjectDrawCall> drawCalls;

    __deprecated ofxAssimpModelLoader *model1;
    __deprecated ofxAssimpModelLoader *model2;

	ofLight light;

	textureModifier texMod;

    History *history = nullptr;

	ofEasyCam cam;

	void adjustCurrent();

public:
	Model3dController();
    ~Model3dController();

	void setup() override;

	shared_ptr<ofxAssimpModelLoader> loadModel(string path);

    void draw() override;

    void enableEvents() override;

    void disableEvents() override;

    void onMousePressed(ofMouseEventArgs &evt);

    void onMouseReleased(ofMouseEventArgs &evt);

    void onKeyRelease(ofKeyEventArgs &evt);

    void createModel(const ofVec3f &position, ofxAssimpModelLoader *model);

    void createBox(const ofVec3f &position, const ofVec2f &startPoint);

    void createSphere(const ofVec3f &position, const ofVec2f &startPoint);

	void createCone(const ofVec3f &position, const ofVec2f &startPoint);

	void createCylinder(const ofVec3f &position, const ofVec2f &startPoint);

    void transform(Object3d *obj, int direction);

	void rotate(Object3d *obj, int direction);

	void translate(Object3d *obj, int direction);
	
	void scale(Object3d *obj, int direction);

    void addItem(Object3d_Ptr ptr);

    void reset();

    void drawOriginOn(ofVec3f position, int length) const;
};