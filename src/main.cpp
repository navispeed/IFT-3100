#include <model/Vectorial2dForm/Sierpinski.h>
#include <services/drawOption/DrawOption.h>
#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main() {

    std::cout << "Application is running few calculation" << std::endl;
//    Sierpinski::generate();

    ofSetLogLevel(OF_LOG_VERBOSE);

    ofSetupOpenGL(1024, 768, OF_WINDOW);            // <-------- setup the GL context

    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too


    ofRunApp(new ofApp());

}
