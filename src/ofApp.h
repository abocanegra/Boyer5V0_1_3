#pragma once

#include "ofMain.h"
#include "ofxBlur.h"
#include "ofxCsv.h"
#include "ofxNetwork.h"
#include "ofxGui.h"
#include "ofxXmlSettings.h"
#include "datahandler.h"
#include "ofxThreadedSlideshow.h"
#include "ofxPixelsExtended.h"
#include "ofxAssimpModelLoader.h"
#include "ofxHistogram.h"
#include "pxrandom.h"
#include "ofxOpenCv.h"
#include <time.h>
#include <iostream>
#include <unistd.h>

class ofApp : public ofBaseApp{

public:
    void setup();
    void setupGui();
    void setupGnav();
    void setupGstat();
    void update();
    void draw();
    void drawGui(ofEventArgs & args);
    void drawGnav(ofEventArgs & args);
    void drawGstat(ofEventArgs & args);

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);


    //GUI
    void exit(); //Autosave Function
    bool programLoaded;
    /*
    void bUseTextureEnablePressed(const void * sender, bool & pressed);
    void bgEnablePressed(const void * sender, bool & pressed);
    void blurEnablePressed(const void * sender, bool & pressed);
    void hpEnablePressed(const void * sender, bool & pressed);
    void blobApplyPressed();
    //ofxFloatSlider radius;
    ofxIntSlider    thresholdValue;
    ofxIntSlider    learnSpeed;
    ofxIntSlider    blur;
    ofxIntSlider    hpblur;
    ofxIntSlider    blobThreshold;
    ofxIntSlider    minAreaRadius;
    ofxIntSlider    maxAreaRadius;
    ofxIntSlider    maxDistance;
    ofxFloatSlider  hpBright;
    ofxFloatSlider  hpCont;
    ofxLabel        screenSize;
    ofxLabel        fpsLabel;
    ofxToggle       bUseTexture;
    ofxToggle       bgEnable;
    ofxToggle       blurEnable;
    ofxToggle       hpEnable;
    ofxButton       blobApply;
  //ofxToggle filled;
    //ofxButton twoCircles;
    //ofxButton ringButton;

    */

    string         currentNav;
    ofxPanel       GlobalNav;
    ofxPanel       ColorMgmtGui;
    ofxPanel       NetworkingGui;
    ofxPanel       DebugGui;

    /*
    ofxPanel                DiagnosticGui;
    ofxPanel                CalibrationGui;
    ofxPanel                ParticleGui;
    ofxPanel                SameColorGui;
    ofxPanel                RandomNoiseGui;
    ofxPanel                FPS;
    ofxPanel                SCREENSIZE;
    */
    void                        ofxColorManPressed();
    void                        networkingPressed();
    void                        debugPressed();

    ofxButton                   colorManagement;
    ofxButton                   networking;
    ofxButton                   debug;
    bool                        showDebug;
    bool                        showColorMgmt;
    bool                        showNetworking;

    void                        enableLutPressed(const void * sender, bool & pressed);
    void                        showLutPressed(const void * sender, bool & pressed);
    void                        cubeLutPressed(const void * sender, bool & pressed);
    void                        matLutPressed(const void * sender, bool & pressed);
    void                        powerLevelChanged(int & powerLevel);
    void                        clippingChanged(int & clipping);
    ofxToggle                   doLUT;
    ofxToggle                   showLut;
    ofxLabel                    LUTModes;
    ofxToggle                   cubeLUT;
    ofxToggle                   matLUT;
    ofxLabel                    manColorLimits;
    ofParameter<ofColor>        manualColor;
    ofParameter<int>            activeLUT;
    ofParameter<float>          lutIntensity;
    ofParameter<int>            clipping;
    ofParameter<int>            powerLevel;


    int       setLUT;
    string lutModeStr;
    string showLutStr;
    string doLutStr;

    void                        allHexPressed(const void * sender, bool & pressed);
    void                        allHexAPressed(const void * sender, bool & pressed);
    void                        mcAddrRGBPressed(const void * sender, bool & pressed);
    void                        mcAddrRGBAPressed(const void * sender, bool & pressed);
    void                        mcAddrHEXPressed(const void * sender, bool & pressed);
    void                        mcAddrHEXAPressed(const void * sender, bool & pressed);
    void                        eightBitPressed(const void * sender, bool & pressed);
    void                        sixteenBitPressed(const void * sender, bool & pressed);
    void                        sendDataPressed(const void * sender, bool & pressed);
    void                        tcpPressed(const void * sender, bool & pressed);
    void                        udpPressed(const void * sender, bool & pressed);

    ofxLabel                    dataStructLbl;
    ofxToggle                   allHex;
    ofxToggle                   allHexA;
    ofxToggle                   mcAddrRGB;
    ofxToggle                   mcAddrRGBA;
    ofxToggle                   mcAddrHEX;
    ofxToggle                   mcAddrHEXA;
    ofxLabel                    bitDepthLbl;
    ofxToggle                   eightbit;
    ofxToggle                   sixteenbit;
    ofxLabel                    networkFormat;
    ofxToggle                   tcp;
    ofxToggle                   udp;
    ofxToggle                   sendData;

    void                              enableSolidDebugPressed(const void * sender, bool & pressed);
    void                              enableDebugRandomPressed(const void * sender, bool & pressed);
    void                              updateRandomPressed();
    ofxToggle                   debugSolidColor;
    ofParameter<ofColor>        solidColor;
    ofxToggle                   toggleDebugRandom;
    ofParameter<int>     randomMode;
    ofParameter<int>     randomRefreshRate;
     ofParameter<float>        randomLowColor;
     ofParameter<float>        randomHighColor;
     ofParameter<float>     debugTrail;
     ofParameter<float>     debugBlur;

    ofxButton                   updateRandom;






    float blurScale;

    /*
     *
     * Global Nav
     *
     */


    /*
     *
     * Control Window
     *
     */


    /*
     *
     * Visualizer
     *
     */

    //FBO GPU
    void setupLUTs();
    void loadLUT();
    int dirLoadIndex;
    ofDirectory dir;
    bool lutLoaded;
    string currentLUT;
    string cubeStr;
    ofFbo fbo;
    float history;
    int fbow;
    int fboh;
    float fbox;
    float fboy;
    //Data
    char pxSize[100]; // an array of chars
    char fps[32];
    char networkInfo[21];
    uint total;

    //BLUR
    ofxBlur blur;

    /*OpenGL LUT*/

    float rVF;

    //Pixel Transforms
    ofxPixelsExtended px;
    ofxPixelsExtended lastPx;
    bool isNewFrame;

    // Shader
    ofShader lutFilter;
    ofPlanePrimitive plane;

    // LUT
    GLuint texture3D;
    int LUTsize =64;
    string LUTpath;
    struct RGB { float r, g, b; };

    //MatrixLUT
    double lutMat[4][3];
    double calColMat[4];
    double adjColMat[3];

    int W;
    int H;

    /******CSV******/
    ofxCsv csv;
    ofxCsv csvRecorder;

    unsigned int structure[34][910][6];          //[raspi][address][x,y,r,g,b,a]
    ofPoint vectorField[91][324][1];    //[line][col][top point]
    GLuint sendColor[34][910][6];       //[raspi][address][raspi, address, g, r, b]

    float xPxSpace;
    float yPxSpace;

    void formatData();
    string threadCount;
    string CPUMEM;
    void resetThreads();
    void closeThreads();

    bool mcAvailable(string ipAddress);

    DataHandler dataHandler[34];
    int dataFMTSize;
    int bitDepth;
    /*
     *
     * Stats and Detail Window Vars
     *
     */
    ofTrueTypeFont robotoBold;
    ofTrueTypeFont robotoNormal;
    ofTrueTypeFont robotoSmallBold;

    //Network Configuration
    int configPort;
    string txAddy;
    int txPort;
    int protocolMode;
    string mode;
    void initiateDataComms();
    bool dataInitiated;
    string mcIP;

    int dataFMT;
    float tcpCounter;
    int tcpConnectTime;
    int tcpDeltaTime;

    //Slideshow
    //3D Model
    void loadContent();
    void scalePosContent();
    void drawSlideshow();
    void updateSlideshow();
    void clearSlides();

    float windowW;
    float windowH;
    ofxThreadedSlideshow * slideshow;
    ofImage * slideImg;
    ofVideoPlayer * slideMov;
    string contentType;
    int imageDuration;
    int modelDuration;

    //3D Model
    ofxAssimpModelLoader * slideModel;
    ofMesh mesh;
    ofLight	light;
    float rotateIter;
    float rat;
    float yPos;
    float scM;
    /*****Test Data*****/
    ofImage img;

    /*********Time*********/
    time_t rawtime;

    /**********Shows*********/
    PxRandom * random;
    PxRandom * debugRandom;


    /************Histogram*************/
    void drawHistogram(vector<float> & h);

    ofxHistogram histogram;

    ofxCvColorImage rgb, hsv;
    ofxCvGrayscaleImage r, g, b;
    ofxCvGrayscaleImage h, s, v;

    vector<float> histogramR, histogramG, histogramB;
    vector<float> histogramH, histogramS, histogramV;
    int bins;
    void restartShowTimer();

protected:
    void   drawShows();
    void   initiateShows();
    void   stopShowsThreads();

    int    showTimeDiff();
    string showsXMLFile;
    ofXml  showsXML;
    int    totalShows;
    int    showsCycle;
    int    currentShow;
    float  showBlur;
    float  showTrail;
    string currentShowElement;
    string showType;
    string showName;
    float  showDuration;
    bool   playShow;
    bool   showInitiated;
    time_t showStartTime;
    time_t showCurrentTime;
    int    lastSlideShow;

    pid_t PID;
private:

};
