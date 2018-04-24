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

void Model3dController::hideLightGui() {
	gui->setVisible(false);
	if (guiSelLight != nullptr) {
		guiSelLight->setVisible(false);
	}
	if (guiOptionLight != nullptr) {
		guiOptionLight->setVisible(false);
	}
}

void Model3dController::changeGuiMat()
{
	if (selection.at(0) != nullptr) {
		pickerAmbientMat->setColor(selection.at(0)->getMaterial().getAmbientColor());
		pickerSpecularMat->setColor(selection.at(0)->getMaterial().getSpecularColor());
		pickerEmissiveMat->setColor(selection.at(0)->getMaterial().getEmissiveColor());
		pickerDiffuseMat->setColor(selection.at(0)->getMaterial().getEmissiveColor());
		sliderShininess->setValue(selection.at(0)->getMaterial().getShininess());
	}
}

Model3dController::Model3dController() {
    this->modelsList.push_back(loadModel("model1.obj"));
    this->modelsList.push_back(loadModel("model2.obj"));

	for (int i = 0; i < LIGHTNUMBER; i++) {
		lights.push_back(ofLight());
		lightEnable.push_back(false);
	}

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

	setupUI();

    string list[3];
    for (int i = 1; i <= 3; i++) {
        list[i - 1] = "texture" + to_string(i) + ".jpg";
    }
    texMod = textureModifier(list, 3);
}


void Model3dController::setupUI() {

	//setup light ui
	gui = new ofxDatGui(10, 10);
	toggleVisible = gui->addToggle("Show lights");
	std::vector<string> lightNumbers;
	for (int i = 0; i < LIGHTNUMBER; i++) {
		lightNumbers.push_back(to_string(i));
	}
	selectionLight = gui->addDropdown("Lights:", lightNumbers);
	selectionLight->onDropdownEvent(this, &Model3dController::LightSelectorDropDownEvent);
	toggleVisible->onToggleEvent([&](ofxDatGuiToggleEvent e) {

	});
	togglePlacement = gui->addToggle("Placement");
	togglePlacement->onToggleEvent([&](ofxDatGuiToggleEvent e) {

	});
	gui->setVisible(false);

	//setup material ui
	guiMaterial = new ofxDatGui(10, 10);

	vector<string> materialTypes;
	materialTypes.push_back("base");
	materialTypes.push_back("gouraud");
	materialTypes.push_back("lambert");
	materialTypes.push_back("phong");
	vector<Object3d_Ptr> * tempSelection = &selection;
	dropDownMaterialType = guiMaterial->addDropdown("illumination type", materialTypes);
	dropDownMaterialType->onDropdownEvent([&, tempSelection](ofxDatGuiDropdownEvent e) {
		tempSelection->at(0)->getMaterial().changeMaterialType((typeIllum)e.child);
	});
	
	pickerAmbientMat = guiMaterial->addColorPicker("Ambient Color");
	pickerAmbientMat->onColorPickerEvent([&, tempSelection](ofxDatGuiColorPickerEvent e) {
		tempSelection->at(0)->getMaterial().setAmbientColor(e.color);
	});

	pickerDiffuseMat = guiMaterial->addColorPicker("Diffuse Color");
	pickerDiffuseMat->onColorPickerEvent([&, tempSelection](ofxDatGuiColorPickerEvent e) {
		tempSelection->at(0)->getMaterial().setDiffuseColor(e.color);
	});

	pickerSpecularMat = guiMaterial->addColorPicker("Specular Color");
	pickerSpecularMat->onColorPickerEvent([&, tempSelection](ofxDatGuiColorPickerEvent e) {
		tempSelection->at(0)->getMaterial().setSpecularColor(e.color);
	});

	pickerEmissiveMat = guiMaterial->addColorPicker("Emissive Color");
	pickerEmissiveMat->onColorPickerEvent([&, tempSelection](ofxDatGuiColorPickerEvent e) {
		tempSelection->at(0)->getMaterial().setEmissiveColor(e.color);
	});

	sliderShininess = guiMaterial->addSlider("Shininess", 0, 128,0);
	sliderShininess->onSliderEvent([&, tempSelection](ofxDatGuiSliderEvent e) {
		tempSelection->at(0)->getMaterial().setShininess(e.value);
	});


	vector<string> materialName;
	materialName.push_back("brass");
	materialName.push_back("silver");
	materialName.push_back("yellow rubber");

	dropDownMaterialSample = guiMaterial->addDropdown("Material sample", materialName);
	dropDownMaterialSample->onDropdownEvent([&, tempSelection](ofxDatGuiDropdownEvent e) {
		switch (e.child)
		{
		case 0:
		{
			tempSelection->at(0)->getMaterial().setAmbientColor(ofFloatColor(0.329412, 0.223529, 0.027451));
			tempSelection->at(0)->getMaterial().setDiffuseColor(ofFloatColor(0.780392, 0.568627, 0.113725));
			tempSelection->at(0)->getMaterial().setSpecularColor(ofFloatColor(0.992157, 0.941176, 0.807843));
			tempSelection->at(0)->getMaterial().setEmissiveColor(ofColor(0, 0, 0));
			tempSelection->at(0)->getMaterial().setShininess(0.21794872 * 128);
			this->changeGuiMat();
			break;
		}
		case 1:
		{
			tempSelection->at(0)->getMaterial().setAmbientColor(ofFloatColor(0.19225, 0.19225, 0.19225));
			tempSelection->at(0)->getMaterial().setDiffuseColor(ofFloatColor(0.50754, 0.50754, 0.50754));
			tempSelection->at(0)->getMaterial().setSpecularColor(ofColor(0.508273, 0.508273, 0.508273));
			tempSelection->at(0)->getMaterial().setEmissiveColor(ofColor(0, 0, 0));
			tempSelection->at(0)->getMaterial().setShininess(0.4 * 128);
			this->changeGuiMat();
			break;
		}
		case 2:
		{
			tempSelection->at(0)->getMaterial().setAmbientColor(ofFloatColor(0.05, 0.05, 0.0));
			tempSelection->at(0)->getMaterial().setDiffuseColor(ofFloatColor(0.5, 0.5, 0.4));
			tempSelection->at(0)->getMaterial().setSpecularColor(ofFloatColor(0.7, 0.7, 0.04));
			tempSelection->at(0)->getMaterial().setEmissiveColor(ofColor(0, 0, 0));	
			tempSelection->at(0)->getMaterial().setShininess(.078125 * 128);
			this->changeGuiMat();
			break;
		}
		default:
			break;
		}
	});
	guiMaterial->setVisible(false);
	
}

void Model3dController::LightSelectorDropDownEvent(ofxDatGuiDropdownEvent e)
{
	lightSelected = e.child;
	if (guiSelLight != nullptr) {
		delete guiSelLight;
		guiSelLight = nullptr;
	}
	guiSelLight = new ofxDatGui(ofGetWidth() - gui->getWidth(), 10);
	guiSelLight->setVisible(true);
	guiSelLight->addLabel("Light: " + to_string(e.child));
	toggleEnabled = guiSelLight->addToggle("enabled", lightEnable[e.child]);
	vector<bool> * temp = &lightEnable;
	int ind = e.child;
	vector<ofLight> * tempLights = &lights;
	toggleEnabled->onToggleEvent([&,temp, ind](ofxDatGuiToggleEvent e) {
		temp->at(ind) = toggleEnabled->getChecked();
	});

	std::vector<string> lightType;
	lightType.push_back("point");
	lightType.push_back("spot");
	lightType.push_back("directional");

	dropDownType = guiSelLight->addDropdown("Light type: ", lightType);
	if (lights.at(lightSelected).getIsSpotlight()) {
		dropDownType->select(LIGHTTYPE::SPOT);
	}
	else if (lights.at(lightSelected).getIsPointLight()) {
		dropDownType->select(LIGHTTYPE::POINT);
	}
	else {
		dropDownType->select(LIGHTTYPE::DIRECTIONAL);
	}
	
	dropDownType->onDropdownEvent(this, &Model3dController::LightTypeDropDownEvent);

	pickerDiffuseColor = guiSelLight->addColorPicker("Diffuse Color");
	pickerDiffuseColor->setColor(lights.at(ind).getDiffuseColor());
	pickerDiffuseColor->onColorPickerEvent([&, tempLights, ind](ofxDatGuiColorPickerEvent e) {
		tempLights->at(ind).setDiffuseColor(e.color);
	});
	pickerSpecularColor = guiSelLight->addColorPicker("Specular Color");
	pickerSpecularColor->setColor(lights.at(ind).getSpecularColor());
	pickerSpecularColor->onColorPickerEvent([&, tempLights, ind](ofxDatGuiColorPickerEvent e) {
		tempLights->at(ind).setSpecularColor(e.color);
	});
	pickerAmbientColor = guiSelLight->addColorPicker("Ambient color");
	pickerAmbientColor->setColor(lights.at(ind).getAmbientColor());
	pickerAmbientColor->onColorPickerEvent([&, tempLights, ind](ofxDatGuiColorPickerEvent e) {
		tempLights->at(ind).setAmbientColor(e.color);
	});

	guiSelLight->addLabel("Position");
	textXCoord = guiSelLight->addTextInput("X", to_string(lights[e.child].getPosition().x));
	
	textXCoord->onTextInputEvent([&, tempLights, ind](ofxDatGuiTextInputEvent e) {
		tempLights->at(ind).setPosition(stof(e.text), tempLights->at(ind).getPosition().y, tempLights->at(ind).getPosition().z);
	});
	textYCoord = guiSelLight->addTextInput("y", to_string(tempLights->at(ind).getPosition().y));
	textYCoord->onTextInputEvent([&, tempLights, ind](ofxDatGuiTextInputEvent e) {
		tempLights->at(ind).setPosition(tempLights->at(ind).getPosition().x, stof(e.text), tempLights->at(ind).getPosition().z);
	});
	textZCoord = guiSelLight->addTextInput("Z", to_string(tempLights->at(ind).getPosition().z));
	textZCoord->onTextInputEvent([&, tempLights, ind](ofxDatGuiTextInputEvent e) {
		tempLights->at(ind).setPosition(tempLights->at(ind).getPosition().x, tempLights->at(ind).getPosition().y, stof(e.text));
	});

	guiSelLight->addLabel("Attenuation");
	sliderAttenuation1 = guiSelLight->addSlider("linear",1,100,100);
	sliderAttenuation1->onSliderEvent([&, tempLights, ind](ofxDatGuiSliderEvent e) {
		tempLights->at(ind).setAttenuation(e.value/100, tempLights->at(ind).getAttenuationLinear(), tempLights->at(ind).getAttenuationQuadratic());
	});
}

void Model3dController::LightTypeDropDownEvent(ofxDatGuiDropdownEvent e) {
	int ind = lightSelected;
	ofLight light = lights.at(ind);
	vector<ofLight> * tempLights = &lights;
	 if(guiOptionLight != nullptr) {
		delete guiOptionLight;
		guiOptionLight = nullptr;
	}
	if (e.child == LIGHTTYPE::POINT) {
		lights.at(ind).setPointLight();
	}
	else {
		guiOptionLight = new ofxDatGui(ofGetWidth() - gui->getWidth(), 10 + guiSelLight->getHeight());
		guiOptionLight->addLabel("Orientation");
		sliderXOrientation= guiOptionLight->addSlider("X", -180, 180);
		sliderXOrientation->setValue(light.getOrientationEuler().x);

		sliderYOrientation = guiOptionLight->addSlider("Y", -180, 180);
		sliderYOrientation->setValue(light.getOrientationEuler().y);
		
		sliderZOrientation = guiOptionLight->addSlider("Z", -180, 180);
		sliderZOrientation->setValue(light.getOrientationEuler().z);
		

		ofxDatGuiSlider * x = sliderXOrientation;
		ofxDatGuiSlider * y = sliderYOrientation;
		ofxDatGuiSlider * z = sliderZOrientation;
		sliderXOrientation->onSliderEvent([&, tempLights, ind, y, z](ofxDatGuiSliderEvent e) {
			tempLights->at(ind).setOrientation(ofVec3f(e.value, y->getValue(), z->getValue()));
		});

		sliderYOrientation->onSliderEvent([&, tempLights, ind, x, z](ofxDatGuiSliderEvent e) {
			tempLights->at(ind).setOrientation(ofVec3f(x->getValue(), e.value, z->getValue()));
		});

		sliderZOrientation->onSliderEvent([&, tempLights, ind, x, y](ofxDatGuiSliderEvent e) {
			tempLights->at(ind).setOrientation(ofVec3f(x->getValue(), y->getValue(), e.value));
		});


		if (e.child == LIGHTTYPE::DIRECTIONAL) {
			lights.at(ind).setDirectional();
		}

		else {
			lights.at(ind).setSpotlight();
		}
	}
	
}


shared_ptr<ofxAssimpModelLoader> Model3dController::loadModel(string path) {
    auto modelTemp = std::make_shared<ofxAssimpModelLoader>();
    if (!modelTemp->loadModel(path)) {
        std::cout << "<Erreur> impossible de lire: " + path << endl;
    }
    return modelTemp;
}

void Model3dController::draw() {
	ofEnableLighting();
	for (int i = 0; i < lights.size(); i++) {
		if (lightEnable.at(i)) {
			lights.at(i).enable();
		}
	}
	ofEnableDepthTest();
    this->cam.begin();
    for (auto &it : drawCalls) {
        ofPushMatrix();
        ofPushStyle();
        it();
        ofPopMatrix();
        ofPopStyle();
    }

	if (toggleVisible->getChecked()) {
		for (int i = 0; i < lights.size(); i++) {
			if (lightEnable.at(i)) {
				lights.at(i).draw();
			}
		}
	}
	

    for (auto &it : container) {
        it->drawObject(lights);
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
	ofDisableDepthTest();
	for (int i = 0; i < lights.size(); i++) {
		if (lightEnable.at(i)) {
			lights.at(i).disable();
		}
	}
	ofDisableLighting();

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
	gui->setVisible(false);
	if (guiSelLight != nullptr) {
		guiSelLight->setVisible(false);
	}
	if (guiOptionLight) {
		guiOptionLight->setVisible(false);
	}
	guiMaterial->setVisible(false);
}

bool Model3dController::hasKeyboardFocus()
{
	bool retour = guiSelLight != nullptr;
	if (guiSelLight) {
		retour &= textXCoord->getFocused() || textYCoord->getFocused() || textZCoord->getFocused();
	}
	return retour;
}

void Model3dController::onMousePressed(ofMouseEventArgs &evt) {
    const ofVec3f &args = this->cam.screenToWorld(evt);
	if (touchInterface(ofPoint(evt.x,evt.y),gui) || touchInterface(ofPoint(evt.x,evt.y),guiSelLight) 
		|| touchInterface(ofPoint(evt.x,evt.y),guiOptionLight) || touchInterface(ofPoint(evt.x,evt.y),guiMaterial)) {
		return;
	}
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
		case FormMode::LIGHT:
			if (togglePlacement->getChecked()) {
				lights.at(lightSelected).setPosition(args);
				if (textXCoord != nullptr) {
					textXCoord->setText(to_string(lights.at(lightSelected).getPosition().x));
					textYCoord->setText(to_string(lights.at(lightSelected).getPosition().y));
					textZCoord->setText(to_string(lights.at(lightSelected).getPosition().z));
				}
				
			}
			break;
        default: {
            initialPoint = std::make_shared<ofVec3f>(args);
            break;
        }
    }
    std::cout << "Mouse on " << args << std::endl;
}

void Model3dController::onKeyRelease(ofKeyEventArgs &evt) {
    this->cam.disableMouseInput();

	if (guiSelLight != nullptr) {
		if (textXCoord->getFocused() || textYCoord->getFocused() || textZCoord->getFocused()) {
			return;
		}
	}
    CursorManager::getInstance()->setCursor(CursorManager::CURSOR_TYPE::DEFAULT);
    switch (evt.key) {

	case ' ': {
		ofColor color;
		ofFloatColor a = color;
		cout << to_string(a.b) << " " << to_string(color.b) << endl;
		cout << to_string(a.g) << " " << to_string(color.g) << endl;
		cout << to_string(a.r) << " " << to_string(color.r) << endl;
		break;
	}
		case 'l':
			gui->setVisible(true);
			guiMaterial->setVisible(false);
			formMode = FormMode::LIGHT;
			break;
		case 'L':
			this->hideLightGui();
			break;
		case 'k':
			this->hideLightGui();
			if (selection.at(0) != nullptr) {
				guiMaterial->setVisible(true);
				changeGuiMat();
			}
			break;
		case 'K':
			guiMaterial->setVisible(false);
			break;
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
			changeGuiMat();
            break;
        case 359:
            current--;
            adjustCurrent();
			changeGuiMat();
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

bool Model3dController::touchInterface(ofPoint point, ofxDatGui * ui)
{
	bool within = false;
	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;
	if (ui != nullptr) {
		x1 = ui->getPosition().x;
		y1 = ui->getPosition().y;
		x2 = x1 + ui->getWidth();
		y2 = y1 + ui->getHeight();
		within |= point.x <= x2 && point.x >= x1 && point.y >= y1 && point.y <= y2;
	}
	return within;
}

Object3d_Ptr Model3dController::getSelectionAt(int ind) {
	return selection.at(ind);
}
