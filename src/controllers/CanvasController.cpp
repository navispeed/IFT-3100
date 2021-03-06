//
// Created by Grégoire GUEMAS on 18-02-15.
//

#include <boost/bind.hpp>
#include <graphics/ofPolyline.h>
#include <graphics/ofGraphics.h>
#include <model/Vectorial2dForm/RecursiveTree.h>
#include "CanvasController.h"
#include "model/of2d/of2dFactory.h"
#include "model/of2d/of2dObject.h"
#include "services/history/HistoryManager.h"
#include "ControllerFactory.h"
#include <model/Vectorial2dForm/Sierpinski.h>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"
const std::map<int, const char *> CanvasController::stateToString = {
        {NONE,              "Points selector"},
        {STATE::RECTANGLE,  "Rectangle"},
        {STATE::POLYGONE,   "Polygon"},
        {STATE::CIRCLE,     "Circle"},
        {STATE::LINE,       "Line"},
        {STATE::TRIANGLE,   "Triangle"},
        {STATE::REC_TREE,   "Recursive Tree"},
        {STATE::SIERPINSKI, "Sierpinski"},
		{STATE::HERMIT,		"Hermit"},
		{STATE::BEZIER,		"Bezier"},
		{STATE::CATMULL_ROM, "Catmull Rom"}
};

CanvasController::CanvasController()
{
	std::vector<std::string> dropDownElements;
	std::vector<char> dropDownChar;
	for (auto p : stateToString) {
		dropDownElements.push_back(p.second);
		dropDownChar.push_back(p.first);
	}
	gui = new ofxDatGui(10, 10);
	colorFillPicker = gui->addColorPicker("Fill color");
	colorOutLinePicker = gui->addColorPicker("Out line color");
	weightSlider = gui->addSlider("Line weight", 0, 80, 1);
	dropDown = gui->addDropdown("Shape", dropDownElements);
	saveBtn = gui->addButton("Save Image");
	importBtn = gui->addButton("Import Image");

	weightSlider->setPrecision(0);
	colorFillPicker->setColor(this->drawOption->getFillColor());
	colorOutLinePicker->setColor(this->drawOption->getOutLineColor());
	dropDown->select(7);

	colorFillPicker->onColorPickerEvent([&](ofxDatGuiColorPickerEvent e) {
		this->drawOption->setFillColor(e.color);
	});

	colorOutLinePicker->onColorPickerEvent([&](ofxDatGuiColorPickerEvent e) {
		this->drawOption->setOutLineColor(e.color);
	});

	weightSlider->onSliderEvent([&](ofxDatGuiSliderEvent e) {
		this->drawOption->setWeight(e.value);
	});

	saveBtn->onButtonEvent([&](ofxDatGuiButtonEvent e) {
		ofFileDialogResult saveFileResult = ofSystemSaveDialog("Save","Save your file");
		if (saveFileResult.bSuccess) {
			std::string filePath = saveFileResult.filePath;
			std::string ext = filePath.substr(filePath.find_last_of(".") + 1);
			if (ext != "png" || ext != "jpg") {
				filePath += ".png";
			}
			save(filePath);
		}
	});

	importBtn->onButtonEvent([&](ofxDatGuiButtonEvent e) {
		ofFileDialogResult openFileResult = ofSystemLoadDialog("Select a jpg or png");

		if (openFileResult.bSuccess) {
			load(openFileResult.filePath);
		}
		else {
		}
	});

	dropDown->onDropdownEvent([&, dropDownChar](ofxDatGuiDropdownEvent e) {
		ofKeyEventArgs fakeKey;
		fakeKey.key = dropDownChar.at(e.child);
		onKeyRelease(fakeKey);
	});
	
	gui->setVisible(false);
}

void CanvasController::setup() {
    this->setState(NONE);
    this->history = HistoryManager::getInstance()->getFromController(this);
    ofSetCircleResolution(100);
	
	this->otherObject.emplace_back([]() {
		ofDrawRectangle(0, 0, 300, ofGetHeight());
	});
}

void CanvasController::draw() {
    ofSetBackgroundColor(this->drawOption->getBackgroundColor());
    for (const auto &f : this->otherObject) {
        ofPushMatrix();
        ofPushStyle();
        f();
        ofPopStyle();
        ofPopMatrix();
        ofSetColor(ofColor::white);
    }
    ofSetColor(ofColor::black);
    for (const auto &point : this->pointList) {
        ofDrawCircle(point, 3);
    }
    ofSetColor(CanvasController::defColor);
}

void CanvasController::enableEvents() {
    ofAddListener(ofEvents().mousePressed, this, &CanvasController::onMousePressed);
    ofAddListener(ofEvents().mouseReleased, this, &CanvasController::onMouseRelease);
    ofAddListener(ofEvents().keyReleased, this, &CanvasController::onKeyRelease);
	gui->setVisible(true);
}

void CanvasController::disableEvents() {
    ofRemoveListener(ofEvents().mousePressed, this, &CanvasController::onMousePressed);
    ofRemoveListener(ofEvents().mouseReleased, this, &CanvasController::onMouseRelease);
    ofRemoveListener(ofEvents().keyReleased, this, &CanvasController::onKeyRelease);
	gui->setVisible(false);
	
}

void CanvasController::setState(CanvasController::STATE state) {
    this->state = state;
    if (state == NONE) {
        ofSetWindowTitle("CanvasController mode");
        return;
    }
    std::stringstream ss;
    ss << "[" << CanvasController::stateToString.at(state) << "] " << "CanvasController mode";
    ofSetWindowTitle(ss.str());
}

void CanvasController::onMousePressed(ofMouseEventArgs &evt) {
	if (evt.x < 300) {
		return;
	}
    if (this->state == NONE) {
        this->pointList.emplace_back(evt.x, evt.y);
        return;
    }
    if (this->initialPoint == nullptr) {
        this->initialPoint = std::make_shared<ofVec2f>(evt.x, evt.y);
        return;
    }
}

void CanvasController::onMouseRelease(ofMouseEventArgs &evt) {
	if (this->initialPoint == nullptr) {
		return;
	}
    switch (this->state) {
        case NONE:
            break;
        case LINE: {
            ofPolyline line;
            line.addVertex(this->initialPoint->x, this->initialPoint->y);
            line.addVertex(evt.x, evt.y);
            otherObjectDrawCall x = [line]() { line.draw(); };
            this->otherObject.push_back(drawIt(x, false));
            auto redoFct = [x, this]() { this->otherObject.push_back(drawIt(x, false)); };
            DEFINE_UNDO_REDO_CONTAINER(this->history, this->otherObject, redoFct);
            break;
        }
        case CIRCLE: {
            float radius = this->initialPoint->distance(ofVec2f(evt.x, evt.y));
            ofVec2f point = *this->initialPoint;
            otherObjectDrawCall x = [point, radius, this]() {
                ofDrawCircle(point.x, point.y, radius);
            };
            auto redoFct = [x, this]() {
                this->otherObject.push_back(drawIt(x, false));
            };
            this->otherObject.push_back(drawIt(x, true));
            DEFINE_UNDO_REDO_CONTAINER(this->history, this->otherObject, redoFct);
            break;
        }
        default:
            break;
    }
    this->initialPoint = nullptr;
}

void CanvasController::onKeyRelease(ofKeyEventArgs &evt) {
    std::cout << "key:" << evt.key << std::endl;
    CursorManager::getInstance()->setCursor(CursorManager::CURSOR_TYPE::DEFAULT);
    switch (evt.key) {
        case NONE:
            this->pointList.clear();
            LIST_CONTAIN_0_ELEMENT(true, setState(NONE))
            break;
        case POLYGONE: {
            LIST_CONTAIN_0_ELEMENT(this->pointList.empty(), setState(POLYGONE))
            LIST_CONTAIN_0_ELEMENT(this->pointList.size() < 3, showError("A polygon needs at least 3 points !");)
            drawPolygon(this->drawOption->getFillColor(), this->pointList);
            pointList.clear();
            break;
        }
        case LINE:
            LIST_CONTAIN_0_ELEMENT(this->pointList.empty(), setState(LINE);
                    CursorManager::getInstance()->setCursor(CursorManager::CURSOR_TYPE::LINE))
            break;
        case CIRCLE: {
            LIST_CONTAIN_0_ELEMENT(this->pointList.empty(), setState(CIRCLE);
                    CursorManager::getInstance()->setCursor(CursorManager::CURSOR_TYPE::CIRCLE));
            break;
        }
        case RECTANGLE: {
            LIST_CONTAIN_0_ELEMENT(this->pointList.size() != 2,
                                   showError("A rectangle needs exactly 2 points !"));
            drawRectangleFromPoint(this->drawOption->getFillColor(), this->pointList);
            this->pointList.clear();
            break;
        }
        case TRIANGLE: {
            LIST_CONTAIN_0_ELEMENT(this->pointList.size() != 3,
                                   showError("A triangle needs exactly 3 points !"))
            drawTriangleFromPoint(this->drawOption->getFillColor(), this->pointList);
            this->pointList.clear();
            break;
        }
        case REC_TREE: {
            LIST_CONTAIN_0_ELEMENT(this->pointList.size() != 1,
                                   showError("A tree needs exactly 1 point to be draw !"))
            const ofVec2f point = this->pointList[0];
            auto draw = [point]() { RecursiveTree().draw(point); };
            auto redoFunction = [draw, this]() { this->otherObject.emplace_back(draw); };
            redoFunction();
            this->pointList.clear();
            DEFINE_UNDO_REDO_CONTAINER(this->history, this->otherObject, redoFunction);

        }
        case SIERPINSKI: {
            LIST_CONTAIN_0_ELEMENT(this->pointList.size() != 1,
                                   showError("A sierpinski triangle needs exactly 1 point to be draw !"))
            const auto point = this->pointList[0];
            const std::string simulation = Sierpinski(ofVec2f()).simulate(9);
            auto draw = [point, simulation]() { Sierpinski(point, 0.9f).render(simulation); };
            auto redoFunction = [draw, this]() { this->otherObject.emplace_back(draw); };
            redoFunction();
            this->pointList.clear();
            DEFINE_UNDO_REDO_CONTAINER(this->history, this->otherObject, redoFunction);
        }
		case HERMIT: {
			LIST_CONTAIN_0_ELEMENT(this->pointList.size() != 4,
				showError("An Hermit curve needs exactly 4 point to be draw !"))
			drawHermitFromPoint(this->drawOption->getFillColor(), this->pointList);
			this->pointList.clear();
			break;
		}
		case BEZIER: {
			LIST_CONTAIN_0_ELEMENT((this->pointList.size() != 4 && this->pointList.size() != 3),
				showError("An Bezier curve needs exactly 3 or 4 point to be draw !"))
			drawBezierFromPoint(this->drawOption->getFillColor(), this->pointList);
			this->pointList.clear();
			break;
		}
		case CATMULL_ROM: {
			LIST_CONTAIN_0_ELEMENT(this->pointList.size() < 4,
				showError("A Catmull Rom curve needs at least 4 point to be draw !"))
				drawCatmullRomFromPoint(this->drawOption->getFillColor(), this->pointList);
			this->pointList.clear();
			break;
		}
        case ' ': { //Save
            auto image = this->getCanvas()->getCapture();
            ControllerFactory::getPictureController()->addImage(image);
            break;
        }
        default:
            break;
    }
}

void CanvasController::load(OfCanvasPtr canvas) {
    this->canvas = canvas;
    this->otherObject = canvas->getObject();
}

void CanvasController::load(std::string &path) {
	auto p = this->pointList;
    auto draw = [this, p, path]() {
		ofImage i = ofImage();

		if (p.size() < 1 || p.size() > 2) {
			showError("An import needs 1 or 2 points !");
			return;
		}

		if (!i.load(path)) {
			showError("Invalid image");
		}

		float w = i.getWidth();
		float h = i.getHeight();
        auto x = p[0].x ;
        auto y = p[0].y;
		if (p.size() == 2) {
			const ofVec2f &f = p[0] - p[1];
			w = abs(f.x);
			h = abs(f.y);
            x = p[0].x < p[1].x ? p[0].x : p[1].x;
            y = p[0].y < p[1].y ? p[0].y : p[1].y;
		}
        i.draw(x, y, w, h);
    };
    auto redoFunction = [draw, this]() {
        this->otherObject.emplace_back(draw);
    };
    redoFunction();
    this->pointList.clear();
    DEFINE_UNDO_REDO_CONTAINER(this->history, this->otherObject, redoFunction);


}

void CanvasController::save(std::string &path) {
	this->getCanvas()->getCapture()->save(path);
}

void CanvasController::reset() {
    this->otherObject.clear();
}

OfCanvasPtr CanvasController::getCanvas() {
    auto *img = new ofImage();
    img->grabScreen(300, 0, ofGetWidth() - 300, ofGetHeight());
    this->canvas = make_shared<OfCanvas>(this->otherObject, img);
    return this->canvas;
}

ofColor CanvasController::randomColor() const {
    return {ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)};
}

void CanvasController::drawTriangleFromPoint(const ofColor &color, const vector<ofVec2f> &pointList) {
    const auto vec = pointList;
    otherObjectDrawCall x = [vec, color, this]() {
        ofDrawTriangle(vec[0].x, vec[0].y, vec[1].x, vec[1].y, vec[2].x, vec[2].y);
    };
    this->otherObject.push_back(drawIt(x, true));
    auto redoFunction = [color, vec, this]() { this->drawTriangleFromPoint(color, vec); };
    DEFINE_UNDO_REDO_CONTAINER(this->history, this->otherObject, redoFunction);
}

void CanvasController::drawHermitFromPoint(const ofColor & color, const vector<ofVec2f>& pointList)
{
	auto vec = pointList;
	ofPolyline hermitCurve;
	ofVec2f position;

	for (int i = 0; i <= sample; ++i) {
		float t = i / (float)sample;

		position.x = (2 * pow(t, 3) - 3 * pow(t, 2) + 1) * vec[0].x +
			(pow(t, 3) - 2 * pow(t, 2) + t) * vec[1].x +
			(pow(t, 3) - pow(t, 2)) * vec[2].x +
			(-2 * pow(t, 3) + 3 * pow(t, 2)) * vec[3].x;
		position.y = (2 * pow(t, 3) - 3 * pow(t, 2) + 1) * vec[0].y +
			(pow(t, 3) - 2 * pow(t, 2) + t) * vec[1].y +
			(pow(t, 3) - pow(t, 2)) * vec[2].y +
			(-2 * pow(t, 3) + 3 * pow(t, 2)) * vec[3].y;

		hermitCurve.addVertex(position);
	}

	this->otherObject.push_back([hermitCurve, color, pointList]() {
		ofSetColor(color);
		ofSetLineWidth(8.0f);
		hermitCurve.draw();
		auto radius = 12.0f;
		ofSetColor(0, 0, 197);
		for each (auto vec in pointList)
		{
			ofDrawEllipse(vec, radius, radius);
		}
	});
	auto redoFunction = [color, pointList, this]() {this->drawHermitFromPoint(color, pointList); };
	DEFINE_UNDO_REDO_CONTAINER(this->history, this->otherObject, redoFunction);
}

void CanvasController::drawBezierFromPoint(const ofColor & color, const vector<ofVec2f>& pointList)
{
	auto vec = pointList;
	ofPolyline bezierCurve;
	ofVec2f position;
	auto size = vec.size();

	for (int i = 0; i <= sample; ++i) {

		float t = i / (float)sample;
		float u = 1 - t;

		if (size == 4) {
			position.x = pow(u, 3) * vec[0].x + 3 * pow(u, 2) * t * vec[1].x + 3 * u * pow(t, 2) * vec[2].x + pow(t, 3) * vec[3].x;
			position.y = pow(u, 3) * vec[0].y + 3 * pow(u, 2) * t * vec[1].y + 3 * u * pow(t, 2) * vec[2].y + pow(t, 3) * vec[3].y;
		}
		else {
			position.x = (1 - 2 * t + pow(t, 2)) * vec[0].x + (2 * t - 2 * pow(t, 2)) * vec[1].x + pow(t, 2) * vec[2].x;
			position.y = (1 - 2 * t + pow(t, 2)) * vec[0].y + (2 * t - 2 * pow(t, 2)) * vec[1].y + pow(t, 2) * vec[2].y;
		}
		

		bezierCurve.addVertex(position);
	}

	this->otherObject.push_back([bezierCurve, color, pointList](){
		ofSetColor(color);
		ofSetLineWidth(8.0f);
		bezierCurve.draw();
		auto radius = 12.0f;
		ofSetColor(0, 0, 197);
		for each (auto vec in pointList)
		{
			ofDrawEllipse(vec, radius, radius);
		}
	});
	auto redoFunction = [color, pointList, this]() {this->drawBezierFromPoint(color, pointList); };
	DEFINE_UNDO_REDO_CONTAINER(this->history, this->otherObject, redoFunction);
}

void CanvasController::drawCatmullRomFromPoint(const ofColor & color, const vector<ofVec2f>& pointList)
{
	auto vec = pointList;
	ofPolyline catmullRomCurve;
	ofVec2f position;
	auto size = vec.size();

	for (int i = 0; i < size - 3; ++i) {
		for (int j = 0; j < sample; ++j) {
			float t = j / (float)sample;

			position.x = 0.5 * vec[i].x * (2 * pow(t, 2) - pow(t, 3) - t) +
				0.5 * vec[i + 1].x * (2 - 5 * pow(t, 2) + 3 * pow(t, 3)) +
				0.5 * vec[i + 2].x * (t + 4 * pow(t, 2) - 3 * pow(t, 3)) +
				0.5 * vec[i + 3].x * (pow(t, 3) - pow(t, 2));
			position.y = 0.5 * vec[i].y * (2 * pow(t, 2) - pow(t, 3) - t) +
				0.5 * vec[i + 1].y * (2 - 5 * pow(t, 2) + 3 * pow(t, 3)) +
				0.5 * vec[i + 2].y * (t + 4 * pow(t, 2) - 3 * pow(t, 3)) +
				0.5 * vec[i + 3].y * (pow(t, 3) - pow(t, 2));

			catmullRomCurve.addVertex(position);
		}
	}

	this->otherObject.push_back([catmullRomCurve, color, pointList]() {
		ofSetColor(color);
		ofSetLineWidth(8.0f);
		catmullRomCurve.draw();
		auto radius = 12.0f;
		ofSetColor(0, 0, 197);
		for each (auto vec in pointList)
		{
			ofDrawEllipse(vec, radius, radius);
		}
	});
	auto redoFunction = [color, pointList, this]() {this->drawCatmullRomFromPoint(color, pointList); };
	DEFINE_UNDO_REDO_CONTAINER(this->history, this->otherObject, redoFunction);
}

void CanvasController::drawRectangleFromPoint(const ofColor &color, const vector<ofVec2f> &pointList) {
    const auto &vec = pointList;
    otherObjectDrawCall x = [vec, color, this]() {
        auto leftX = vec[0].x < vec[1].x ? vec[0].x : vec[1].x;
        auto leftY = vec[0].y < vec[1].y ? vec[0].y : vec[1].y;
        float h = DISTANCE_BTW_POINT(vec[0].x, vec[1].x);
        float d = DISTANCE_BTW_POINT(vec[0].y, vec[1].y);
        ofDrawRectangle(leftX, leftY, h, d);
    };
    this->otherObject.push_back(drawIt(x, true));
    auto redoFunction = [color, vec, this]() { this->drawRectangleFromPoint(color, vec); };
    DEFINE_UNDO_REDO_CONTAINER(this->history, this->otherObject, redoFunction);
}

void CanvasController::drawPolygon(const ofColor &color, const vector<ofVec2f> &pointList) {
    std::vector<ofVec2f> vec = pointList;
    otherObjectDrawCall x = [color, vec, this]() {
        ofBeginShape();
        for (const auto &point : vec) {
            ofVertex(point.x, point.y);
        }
        ofEndShape(true);
    };
    otherObject.push_back(drawIt(x, true));
    auto redoFunction = [color, vec, this]() { this->drawPolygon(color, vec); };
    DEFINE_UNDO_REDO_CONTAINER(this->history, this->otherObject, redoFunction);
}

otherObjectDrawCall CanvasController::drawIt(otherObjectDrawCall fct, bool toFill) {
    ofColor fillColor = this->drawOption->getFillColor();
    ofColor outlineColor = this->drawOption->getOutLineColor();
    float weight = this->drawOption->getWeight();
    auto color = (toFill ? fillColor : outlineColor);
    auto f = [fct, weight, color, fillColor, outlineColor, toFill]() {
        ofSetLineWidth(weight);
        if (toFill) {
            ofSetColor(fillColor);
            ofFill();
            fct();
            ofNoFill();
        }
        ofSetColor(outlineColor);
        fct();
    };
    return f;
}

#pragma clang diagnostic pop