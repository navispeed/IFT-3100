#include "Model3dController.h"
#include <services/history/HistoryManager.h>
#include <future>

void Model3dController::adjustCurrent() {
    if (container.size() == 0) {
        current = -1;
    } else {
        current %= container.size();
    }
    selection.clear();
    selection.push_back(container[current]);
}

Model3dController::Model3dController() {
    this->modelsList.push_back(loadModel("model1.obj"));
    this->modelsList.push_back(loadModel("model2.obj"));

    this->cam = ofEasyCam();
    this->cam.setPosition(0, 0, 50);
    this->drawCalls.push_back([this]() {
        drawOriginOn(ofVec3f(0, 0, 0), 100);
        ofSetColor(ofColor::grey);
        ofRotate(90, 0, 0, 1);
        ofDrawGridPlane(10, 10, false);
    });
    camera_near = 50.0f;
    camera_far = 1750.0f;
    camera_fov = 60.0f;

//    this->cam.setupOffAxisViewPortal(topLeft, bottomLeft, bottomRight);
}

void Model3dController::drawOriginOn(ofVec3f position, int length) const {
    ofSetColor(ofColor::red);
    ofDrawArrow(position, position + ofVec3f(length, 0), 4);
    ofSetColor(ofColor::green);
    ofDrawArrow(position, position + ofVec3f(0, length), 4);
    ofSetColor(ofColor::blue);
    ofDrawArrow(position, position + ofVec3f(0, 0, length), 4);
}

// 100  x
//  5

Model3dController::~Model3dController() {
}

void Model3dController::setup() {
    ofSetWindowTitle("3d mode");

    ofDisableArbTex();
    ofDisableAlphaBlending();

    this->history = HistoryManager::getInstance()->getFromController(this);


    enableEvents();


    string list[3];
    for (int i = 1; i <= 3; i++) {
        list[i - 1] = "texture" + to_string(i) + ".jpg";
    }
    texMod = textureModifier(list, 3);
}

shared_ptr<ofxAssimpModelLoader> Model3dController::loadModel(string path) {
    auto modelTemp = std::make_shared<ofxAssimpModelLoader>();
    if (!modelTemp->loadModel(path)) {
        std::cout << "<Erreur> impossible de lire: " + path << endl;
    }
    return modelTemp;
}

void Model3dController::draw() {

//    ofDrawGridPlane(60, 8);
    this->cam.begin();
//
//     light.enable();
//     light.setPosition(ofVec3f(100, 100, 200));
//     light.lookAt(ofVec3f(0, 0, 0));
    ofEnableDepthTest();
//    ofDrawGrid(60, 8, false, true, true, false);
//    ofDrawGridPlane(60, 8);
    for (auto &it : drawCalls) {
        ofPushMatrix();
        ofPushStyle();
        it();
        ofPopMatrix();
        ofPopStyle();
    }

    for (auto &it : container) {
        it->drawObject();
    }
    for (auto &selected : this->selection) {
        ofPushMatrix();
        ofPushStyle();
        auto max = std::max(std::max(selected->getAsOfNode()->getScale().x, selected->getAsOfNode()->getScale().y), selected->getAsOfNode()->getScale().z);
        drawOriginOn(selected->getAsOfNode()->getPosition(), static_cast<int>(10 + max));
        ofPopMatrix();
        ofPopStyle();
    }
    this->cam.end();
}

void Model3dController::enableEvents() {
    ofAddListener(ofEvents().mousePressed, this, &Model3dController::onMousePressed);
    ofAddListener(ofEvents().mouseReleased, this, &Model3dController::onMouseReleased);
    ofAddListener(ofEvents().keyPressed, this, &Model3dController::onKeyRelease);
}

void Model3dController::disableEvents() {
    ofRemoveListener(ofEvents().mousePressed, this, &Model3dController::onMousePressed);
    ofRemoveListener(ofEvents().mouseReleased, this, &Model3dController::onMouseReleased);
    ofRemoveListener(ofEvents().keyPressed, this, &Model3dController::onKeyRelease);
    ofDisableDepthTest();
}

void Model3dController::onMousePressed(ofMouseEventArgs &evt) {
    const ofVec3f &args = this->cam.screenToWorld(evt);
    switch (formMode) {
        case FormMode::MODEL1: {
            std::cout << "newModel1" << std::endl;
            createModel(args, this->modelsList[0].get());
            break;
        }
        case FormMode::MODEL2: {
            std::cout << "newModel2" << std::endl;
            createModel(args, this->modelsList[1].get());
            break;
        }
        default: {
            initialPoint = std::make_shared<ofVec3f>(args);
            break;
        }
    }
    std::cout << "Mouse on " << args << std::endl;
}

void Model3dController::onKeyRelease(ofKeyEventArgs &evt) {
    this->cam.disableMouseInput();
    CursorManager::getInstance()->setCursor(CursorManager::CURSOR_TYPE::DEFAULT);
    switch (evt.key) {
        case 97://a
            formMode = FormMode::MODEL1;
            std::cout << "modeModel1" << std::endl;
            break;
        case 98://b
            formMode = FormMode::MODEL2;
            std::cout << "modeModel2" << std::endl;
            break;
        case 99://c
            formMode = FormMode::BOX;
            std::cout << "modeBoite" << std::endl;
            CursorManager::getInstance()->setCursor(CursorManager::CURSOR_TYPE::CUBE);
            break;
        case 115://s
            formMode = FormMode::SPHERE;
            std::cout << "modeSphere" << std::endl;
            CursorManager::getInstance()->setCursor(CursorManager::CURSOR_TYPE::SPHERE);
            break;
        case 109://m
            formMode = FormMode::CYLINDER;
            std::cout << "modeCylinder" << std::endl;
            CursorManager::getInstance()->setCursor(CursorManager::CURSOR_TYPE::CYLINDER);
            break;
        case 110://n
            formMode = FormMode::CONE;
            std::cout << "modeCONE" << std::endl;
            CursorManager::getInstance()->setCursor(CursorManager::CURSOR_TYPE::CONE);
            break;
        case 'p'://p
            formMode = FormMode::PORTAL;
            std::cout << "portalMode" << std::endl;
            CursorManager::getInstance()->setCursor(CursorManager::CURSOR_TYPE::PORTAL);
            break;

        case 356://fleche
            for (int i = 0; i < selection.size(); i++) {
                this->transform(selection[i].get(), 1);
            }
            break;
        case 358://fleche
            for (int i = 0; i < selection.size(); i++) {
                this->transform(selection[i].get(), -1);
            }
            break;
        case 357:
            current++;
            adjustCurrent();
            break;
        case 359:
            current--;
            adjustCurrent();
            break;
        case 90: {
            auto it = container.end();
            if (it != container.begin()) {
                it--;
                selection.clear();
                selection.push_back(*it);
            }
            break;
        }
        case 101://e
        {
            Composition comp = texMod.cycleComposition();
            for (auto it : selection) {
                it->setTexture(texMod.compositionTexture(it->getTexture(), texMod.getNextTexture(), comp));
            }
            break;
        }
        case 119: {//w
            //passe a travers les filtres sur les objets selectionnees
            ConvolutionKernel filtre = texMod.cycleFiltre();
            for (auto it : selection) {
                it->setTexture(texMod.filter(it->getTexture(), filtre));
            }
            break;
        }
        case 113://q
            for (auto it : selection) {
                it->setTexture(texMod.applyTexture());
            }
            break;
        case 81: //shift+q
            texMod.cycleTexture();
            for (auto it : selection) {
                it->setTexture(texMod.applyTexture());
            }
            break;
        case 'R': //r
            this->transformType = TransformType::ROTATE;
            break;
        case 'T'://t
            this->transformType = TransformType::TRANSLATE;
            break;
        case 'P'://p
            this->transformType = TransformType::SCALE;
            xScale = SCALEDISTANCE;
            yScale = SCALEDISTANCE;
            zScale = SCALEDISTANCE;
            break;
        case 120://x
            xTranslate = TRANSLATEDISTANCE;
            yTranslate = 0;
            zTranslate = 0;
            xRotate = ROTATEDISTANCE;
            yRotate = 0;
            zRotate = 0;
            xScale = SCALEDISTANCE;
            yScale = 0;
            zScale = 0;
            break;
        case 121://y
            xTranslate = 0;
            yTranslate = TRANSLATEDISTANCE;
            zTranslate = 0;
            xRotate = 0;
            yRotate = ROTATEDISTANCE;
            zRotate = 0;
            xScale = 0;
            yScale = SCALEDISTANCE;
            zScale = 0;
            break;
        case 122://z
            xTranslate = 0;
            yTranslate = 0;
            zTranslate = TRANSLATEDISTANCE;
            xRotate = 0;
            yRotate = 0;
            zRotate = ROTATEDISTANCE;
            xScale = 0;
            yScale = 0;
            zScale = SCALEDISTANCE;
            break;
        case 127://supprimer
            this->reset();
            current = -1;
            break;
        case 65://shift-a
            selection.clear();
            this->selection.insert(this->selection.end(), this->container.begin(), this->container.end());
        case 67: {//shift-c
//            ofSetMatrixMode(OF_MATRIX_PROJECTION);
//            ofLoadMatrix(ofMatrix4x4({}));
//            ofSetMatrixMode(OF_MATRIX_MODELVIEW);
            static bool is_camera_perspective = false;
            auto position = this->cam.getPosition();
            auto orientation = this->cam.getOrientationQuat();
            if (is_camera_perspective) {
                this->cam.disableOrtho();
                this->cam.setupPerspective(false, camera_fov, camera_near, camera_far, ofVec2f(0, 0));
                std::cout << "camera_projection = perspective" << std::endl;
            } else {
                this->cam.enableOrtho();
                std::cout << "camera_projection = orthogonale" << std::endl;
            }
            is_camera_perspective = !is_camera_perspective;
            this->cam.setPosition(position);
            this->cam.setOrientation(orientation);
            this->cam.enableMouseInput();
            break;
        }
        default:
            formMode = FormMode::NONE;
            this->cam.enableMouseInput();
            break;
    }
}

void Model3dController::onMouseReleased(ofMouseEventArgs &evt) {
    const ofVec3f &coordonnateInWorld = this->cam.screenToWorld(evt);
    switch (formMode) {
        case FormMode::BOX:
            this->createBox(coordonnateInWorld, *(this->initialPoint));
            break;
        case FormMode::SPHERE:
            this->createSphere(coordonnateInWorld, *(this->initialPoint));
            break;
        case FormMode::CONE:
            this->createCone(coordonnateInWorld, *(this->initialPoint));
            break;
        case FormMode::CYLINDER:
            this->createCylinder(coordonnateInWorld, *(this->initialPoint));
            break;
        default:
            break;
    }
}

void Model3dController::createModel(const ofVec3f &position, ofxAssimpModelLoader *model) {
    auto redoFunction = [model, position, this]() {
        this->createModel(position, model);
    };
    this->addItem(std::make_shared<Model3d>(model, position));
    DEFINE_UNDO_REDO_CONTAINER(this->history, this->container, redoFunction);
}

void Model3dController::createBox(const ofVec3f &position, const ofVec2f &startPoint) {
    auto temp = new ofBoxPrimitive();
    temp->set(startPoint.distance(ofVec2f(position.x, position.y)));
    temp->setPosition(position);
    auto ptr = std::make_shared<Primitive3d>(temp);

    this->addItem(ptr);

    auto redoFunction = [position, this, startPoint]() {
        this->createBox(position, startPoint);
    };
    DEFINE_UNDO_REDO_CONTAINER(this->history, this->container, redoFunction);
}

void Model3dController::createSphere(const ofVec3f &position, const ofVec2f &startPoint) {
    auto temp = new ofSpherePrimitive();
    temp->setRadius((startPoint.distance(ofVec2f(position.x, position.y))) / 2);
    temp->setPosition(position);
    auto ptr = std::make_shared<Primitive3d>(temp);
    this->addItem(ptr);

    auto redoFunction = [position, this, startPoint]() {
        this->createSphere(position, startPoint);
    };
    DEFINE_UNDO_REDO_CONTAINER(this->history, this->container, redoFunction);
}

void Model3dController::createCone(const ofVec3f &position, const ofVec2f &startPoint) {
    auto temp = new ofConePrimitive();
    float size = startPoint.distance(ofVec2f(position.x, position.y));
    temp->setRadius(size / 2);
    temp->setHeight(size / 2);
    temp->setPosition(position);
    auto ptr = std::make_shared<Primitive3d>(temp);
    this->addItem(ptr);

    auto redoFunction = [position, this, startPoint]() {
        this->createCone(position, startPoint);
    };
    DEFINE_UNDO_REDO_CONTAINER(this->history, this->container, redoFunction);
}

void Model3dController::createCylinder(const ofVec3f &position, const ofVec2f &startPoint) {
    auto temp = new ofCylinderPrimitive();
    float size = startPoint.distance(ofVec2f(position.x, position.y));
    temp->setRadius(size / 2);
    temp->setHeight(size / 2);
    temp->setPosition(position);
    auto ptr = std::make_shared<Primitive3d>(temp);
    this->addItem(ptr);

    auto redoFunction = [position, this, startPoint]() {
        this->createCylinder(position, startPoint);
    };
    DEFINE_UNDO_REDO_CONTAINER(this->history, this->container, redoFunction);
}

void Model3dController::transform(Object3d *obj, int direction) {
    switch (transformType) {
        case TransformType::ROTATE:
            rotate(obj, direction);
            break;
        case TransformType::SCALE:
            scale(obj, direction);
            break;
        case TransformType::TRANSLATE:
            translate(obj, direction);
            break;
    }
}

void Model3dController::rotate(Object3d *obj, int direction) {
    ofVec3f axe(xRotate, yRotate, zRotate);
    obj->rotate(direction * 5, axe);
    auto undoFunction = [obj, direction, axe] {
        obj->rotate(direction * -5, axe);
    };
    auto redoFunction = [obj, direction, this] {
        this->rotate(obj, direction);
    };
    DEFINE_REDO(this->history, undoFunction, redoFunction);
}

void Model3dController::translate(Object3d *obj, int direction) {
    ofVec3f axe(xTranslate, yTranslate, zTranslate);
    obj->translate(direction * axe);
    auto undoFunction = [obj, direction, axe] {
        obj->translate(axe * -direction);
    };
    auto redoFunction = [obj, direction, this] {
        this->translate(obj, direction);
    };
    DEFINE_REDO(this->history, undoFunction, redoFunction);
}

void Model3dController::scale(Object3d *obj, int direction) {
    ofVec3f axe(xScale, yScale, zScale);
    obj->modifyScale(ofVec3f(axe * direction));
    auto undoFunction = [obj, direction, axe] {
        obj->modifyScale(axe * -direction);
    };
    auto redoFunction = [obj, direction, this] {
        this->scale(obj, direction);
    };
    DEFINE_REDO(this->history, undoFunction, redoFunction);
}


void Model3dController::addItem(Object3d_Ptr ptr) {
    container.push_back(ptr);
    selection.clear();
    selection.push_back(ptr);
}

void Model3dController::reset() {
    container.clear();
}