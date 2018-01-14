#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){
    ofGLFWWindowSettings settings;
    //Main Window
    settings.windowMode;
    settings.width = 1296;
    settings.height = 364;
    settings.setPosition(ofVec2f( 585,320));
    settings.resizable = false;
    shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
    mainWindow->setVerticalSync(false);
    mainWindow->makeCurrent();

    //Detailed Control Window
    settings.width = 520;
    settings.height = 1000;
    settings.setPosition(ofVec2f(0,0));
    settings.resizable = false;
    // uncomment next line to share main's OpenGL resources with gui
    //settings.shareContextWith = mainWindow;
    shared_ptr<ofAppBaseWindow> guiWindow = ofCreateWindow(settings);
    guiWindow->setVerticalSync(false);

    shared_ptr<ofApp> mainApp(new ofApp);
    mainApp->setupGui();
    ofAddListener(guiWindow->events().draw,mainApp.get(),&ofApp::drawGui);

    //Global Nav
    settings.width = 1300;
    settings.height = 255;
    settings.setPosition(ofVec2f(585,0));
    settings.resizable = false;
    // uncomment next line to share main's OpenGL resources with gui
    //settings.shareContextWith = mainWindow;
    shared_ptr<ofAppBaseWindow> gnavWindow = ofCreateWindow(settings);
    gnavWindow->setVerticalSync(false);

    mainApp->setupGnav();
    ofAddListener(gnavWindow->events().draw,mainApp.get(),&ofApp::drawGnav);

    //Stats Window
    settings.width = 1300;
    settings.height = 305;
    settings.setPosition(ofVec2f(585,720));
    settings.resizable = false;
    // uncomment next line to share main's OpenGL resources with gui
    //settings.shareContextWith = mainWindow;
    shared_ptr<ofAppBaseWindow> gstatWindow = ofCreateWindow(settings);
    gstatWindow->setVerticalSync(false);

     mainApp->setupGstat();
    ofAddListener(gstatWindow->events().draw,mainApp.get(),&ofApp::drawGstat);

    ofRunApp(mainWindow, mainApp);
    ofRunMainLoop();
}
