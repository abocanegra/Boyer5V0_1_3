#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setupGui(){
    ofSetWindowTitle("UCLA Boyer5 | Controls");
    ofBackground( 32 );
    showColorMgmt =false;
    activeLUT = 0;
    programLoaded = false;
    dataInitiated = false;

    cout << " Setup GUI" << endl;

    ofColor bgColor(16);
    ofColor blueColor(0,128,255);
    ofVec2f guiPos(0,200);
    colorManagement.addListener(this, &ofApp::ofxColorManPressed);
    networking.addListener(this, &ofApp::networkingPressed);
    debug.addListener(this, &ofApp::debugPressed);

    GlobalNav.setup();
    GlobalNav.setName("Global Navigation");

    GlobalNav.setHeaderBackgroundColor(blueColor);
    GlobalNav.setFillColor(blueColor);
    GlobalNav.setBorderColor(blueColor);
    GlobalNav.setHeaderBackgroundColor(blueColor);
    GlobalNav.setDefaultTextPadding(10);
    GlobalNav.setSize(500,180);
    GlobalNav.setDefaultWidth(500);
    GlobalNav.setDefaultHeight(24);

    GlobalNav.add(colorManagement.setup("Color Management"));
    GlobalNav.add(networking.setup("Networking"));
    GlobalNav.add(debug.setup("Debug"));

    doLUT.addListener(this, &ofApp::enableLutPressed);
    showLut.addListener(this, &ofApp::showLutPressed);
    cubeLUT.addListener(this, &ofApp::cubeLutPressed);
    matLUT.addListener(this, &ofApp::matLutPressed);
    powerLevel.addListener(this, &ofApp::powerLevelChanged);
    clipping.addListener(this, &ofApp::clippingChanged);

    ColorMgmtGui.setup();
    ColorMgmtGui.setName("Color Management Menu");

    ColorMgmtGui.setHeaderBackgroundColor(blueColor);
    ColorMgmtGui.setFillColor(blueColor);
    ColorMgmtGui.setBorderColor(blueColor);
    ColorMgmtGui.setHeaderBackgroundColor(blueColor);
    ColorMgmtGui.setDefaultTextPadding(10);
    ColorMgmtGui.setSize(500,700);
    ColorMgmtGui.setPosition(guiPos);
    ColorMgmtGui.setDefaultWidth(500);
    ColorMgmtGui.setDefaultHeight(24);

    ColorMgmtGui.add(doLUT.setup("Enable LUT",false,500,24));
    ColorMgmtGui.add(showLut.setup("Display LUT in Visualizer",false,500,24));
    ColorMgmtGui.add(LUTModes.setup("LUT Modes","Select Method", 500,24));
    ColorMgmtGui.add(cubeLUT.setup("Cube LUT",false,500,24));
    ColorMgmtGui.add(matLUT.setup("Matrix LUT Experimental",false,500,24));
    ColorMgmtGui.add(manualColor.set("Manual Color",ofColor(255,255,255,255),ofColor(0,0),ofColor(255,255)));
    ColorMgmtGui.add(activeLUT.set("Active LUT",0,0,0));
    ColorMgmtGui.add(lutIntensity.set("LUT Intensity",1.0f,0.0f,1.0f));
    ColorMgmtGui.add(clipping.set("Clipping",0,0,90));
    ColorMgmtGui.add(powerLevel.set("Power",1,1,8));

    allHex.addListener(this, &ofApp::allHexPressed);
    allHexA.addListener(this, &ofApp::allHexAPressed);
    mcAddrRGB.addListener(this, &ofApp::mcAddrRGBPressed);
    mcAddrRGBA.addListener(this, &ofApp::mcAddrRGBAPressed);
    mcAddrHEX.addListener(this, &ofApp::mcAddrHEXPressed);
    mcAddrHEXA.addListener(this, &ofApp::mcAddrHEXAPressed);
    eightbit.addListener(this, &ofApp::eightBitPressed);
    sixteenbit.addListener(this, &ofApp::sixteenBitPressed);
    sendData.addListener(this, &ofApp::sendDataPressed);
    tcp.addListener(this, &ofApp::tcpPressed);
    udp.addListener(this, &ofApp::udpPressed);

    NetworkingGui.setup();
    NetworkingGui.setName("Networking Menu");

    NetworkingGui.setHeaderBackgroundColor(blueColor);
    NetworkingGui.setFillColor(blueColor);
    NetworkingGui.setBorderColor(blueColor);
    NetworkingGui.setHeaderBackgroundColor(blueColor);
    NetworkingGui.setDefaultTextPadding(10);
    NetworkingGui.setSize(500,700);
    NetworkingGui.setPosition(guiPos);
    NetworkingGui.setDefaultWidth(500);
    NetworkingGui.setDefaultHeight(24);

    NetworkingGui.add(dataStructLbl.setup("Data","Select Structure", 500,24));
    NetworkingGui.add(allHex.setup("allHex",false,500,24));
    NetworkingGui.add(allHexA.setup("allHexA",false,500,24));
    NetworkingGui.add(mcAddrRGB.setup("MCAddrRGB",false,500,24));
    NetworkingGui.add(mcAddrRGBA.setup("MCAddrRGBA",false,500,24));
    NetworkingGui.add(mcAddrHEX.setup("MCAddrHEX",false,500,24));
    NetworkingGui.add(mcAddrHEXA.setup("MCAddrHEXA",false,500,24));
    NetworkingGui.add(bitDepthLbl.setup("Bit Depth","Select 8 or 16 bit", 500,24));
    NetworkingGui.add(eightbit.setup("Eight Bit",false,500,24));
    NetworkingGui.add(sixteenbit.setup("Sixteen Bit",false,500,24));
    NetworkingGui.add(networkFormat.setup("Network Protocol","TCP-Reliable/UDP-Speed", 500,24));
    NetworkingGui.add(tcp.setup("TCP",true,500,24));
    NetworkingGui.add(udp.setup("UDP",false,500,24));
    NetworkingGui.add(sendData.setup("Send Data",true,500,24));

    debugSolidColor.addListener(this, &ofApp::enableSolidDebugPressed);
    toggleDebugRandom.addListener(this, &ofApp::enableDebugRandomPressed);
    updateRandom.addListener(this, &ofApp::updateRandomPressed);

    debugRandom = new PxRandom();
    DebugGui.setup();
    DebugGui.setName("Debugging Menu");

    DebugGui.setHeaderBackgroundColor(blueColor);
    DebugGui.setFillColor(blueColor);
    DebugGui.setBorderColor(blueColor);
    DebugGui.setHeaderBackgroundColor(blueColor);
    DebugGui.setDefaultTextPadding(10);
    DebugGui.setSize(500,700);
    DebugGui.setPosition(guiPos);
    DebugGui.setDefaultWidth(500);
    DebugGui.setDefaultHeight(24);

    DebugGui.add(debugTrail.set("Debug Trail",0.0f,0.0f,1.0f));
    DebugGui.add(debugBlur.set("Debug Blur",0.0f,0.1f,1.0f));
    DebugGui.add(debugSolidColor.setup("Solid Color",false,500,24));
    DebugGui.add(solidColor.set("Debug Color",ofColor(255,255,255,255),ofColor(0,0),ofColor(255,255)));
    DebugGui.add(toggleDebugRandom.setup("Debug Random",false,500,24));
    DebugGui.add(randomMode.set("Random Mode",0,0,3));
    DebugGui.add(randomRefreshRate.set("Random Refresh Rate",10,10,5000));
    DebugGui.add(randomLowColor.set("Random Low Color",50,0,255));
    DebugGui.add(randomHighColor.set("Random High Color",255,0,255));

    DebugGui.add(updateRandom.setup("Update Random"));

    GlobalNav.loadFromFile("settings.xml");
    ColorMgmtGui.loadFromFile("settings.xml");
    NetworkingGui.loadFromFile("settings.xml");
    DebugGui.loadFromFile("settings.xml");

    blurScale = 0.0f;
}

//--------------------------------------------------------------
void ofApp::setupGnav(){
    ofSetWindowTitle("UCLA Boyer5 | Diagnostics");
    robotoSmallBold.load("fonts/Roboto-Bold.ttf",14);
    ofBackground( 32 );

    cout << " SETUP GNAV " << endl;
    int width = 324;
    int height = 91;
    bins = 30;
    rgb.allocate(width, height);
    hsv.allocate(width, height);
    r.allocate(width, height);
    g.allocate(width, height);
    b.allocate(width, height);
    h.allocate(width, height);
    s.allocate(width, height);
    v.allocate(width, height);
}

//--------------------------------------------------------------
void ofApp::setupGstat(){
    ofSetWindowTitle("UCLA Boyer5 | Stats");
    ofBackground( 32 );
    robotoBold.load("fonts/Roboto-Bold.ttf", 24);
    robotoNormal.load("fonts/Roboto-Regular.ttf",24);

    cout << "Setup GStat()" << endl;
}

//--------------------------------------------------------------
void ofApp::setup(){
    cout << "Setup" << endl;
    ofSetWindowTitle("UCLA Boyer5 | Visualizer | V1.3");
    ofSetLogLevel(OF_LOG_ERROR);// ; OF_LOG_ERROR OF_LOG_VERBOSE
    // the log file will be created in the data directory
    ofLogToFile("logs/error_" + ofToString(ofGetDay()) + "-" + ofToString(ofGetYear()) + "_" + ofToString(ofGetHours()) +
                "-" + ofToString(ofGetMinutes())+ "-" +  ofToString(ofGetSeconds() )+ ".log", false);
    // now logs to the file
    ofLog() << ofGetMonth() << "-" << ofGetDay() << "-" << ofGetYear() << " " << ofGetHours() <<
               ":" << ofGetMinutes() << ":" << ofGetSeconds();
    ofBackground( 0 );
    ofSetFrameRate( 30 ); //Set screen frame rate
    PID =  getpid();
    /****************Basic Vars********************/
    W = ofGetWindowWidth();
    H = ofGetWindowHeight();


    /********************
         * Communication Setup
         * Needs to become an array for all 33 pis and controller
         * RX | TCP = Control Server (led-control Computer)
         * TX | TCPClient = raspberryPi MCs
         * ******************/

    txPort = 10001;
    txAddy = "127.0.0.1";
    configPort = 10002;

    sprintf(networkInfo, ":%d", txPort);


    /**************************************
         * Setup pixel addressing from csv data
         * ************************************/
    //Load Visualization Structure
    csv.load(ofToDataPath("boyer5_structure.csv"), ";");
    /*Examples for calling data from the csv*/
    //	cout << "Print out a specific CSV value" << endl;
    //	cout << csv.data[0][13] << endl;
    //	cout << "Print out the first value" << endl;
    //	cout << csv.data[0].front() << endl;

    /*Analyze CSV Data and output to console*/
    cout << "Maximum Size:";
    cout << csv.data.max_size() << endl;
    cout << "Num Rows:";
    cout << csv.getNumRows() << endl;
    cout << "Num Cols:";
    cout << csv.getNumCols()<< endl;

    //Set Default Values
    if(eightbit){
        if(allHex){
            dataFMTSize = 5; //6;
        }else if(allHexA){
            dataFMTSize = 7;
        }else if(mcAddrRGB){
            dataFMTSize = 16;
        }else if (mcAddrRGBA){
            dataFMTSize = 20;
        }else if(mcAddrHEX){
            dataFMTSize = 11;
        }else if(mcAddrHEXA){
            dataFMTSize = 13;
        }
    }else if(sixteenbit){
        if(allHex){
            dataFMTSize = 9;
        }else if(allHexA){
            dataFMTSize = 11;
        }else if(mcAddrRGB){
            dataFMTSize = 22;
        }else if (mcAddrRGBA){
            dataFMTSize = 28;
        }else if(mcAddrHEX){
            dataFMTSize = 17;
        }else if(mcAddrHEXA){
            dataFMTSize = 21;
        }
    }

    if(eightbit){
        bitDepth = 8;
    }else if (sixteenbit){
        bitDepth = 16;
    }

    if(tcp){
        protocolMode = 0;
    }else if(udp){
        protocolMode = 1;
    }

    if(allHex){
        dataFMT = 0;
    }else if(allHexA){
        dataFMT = 1;
    }else if(mcAddrRGB){
        dataFMT = 2;
    }else if(mcAddrRGBA){
        dataFMT = 3;
    }else if(mcAddrHEX){
        dataFMT = 4;
    }else if (mcAddrHEXA){
        dataFMT = 5;
    }

    if(tcp){
        ofSetFrameRate( 15 );
    }else if(udp){
        ofSetFrameRate( 30 );
    }
    //Create Pixel Grid from data with space to reflect the 1" distance between pixels
    fbow = int(csv.data[0].size()); //Calculate width of Data Set in pixels *4
    fboh = csv.getNumRows();//Calculate height of Data Set in pixels *4
    total = fbow * fboh;
    sprintf(pxSize, "%ipx X %ipx | %u Total | 1ppi", fbow, fboh, total);

    fbox =0;
    fboy = 0;
    cout <<"FBO Window: " << fbow << "x" << fboh << " " << fbox <<","<<fboy << endl;
    //FBO
    //Allocate drawing buffer
    try {
        if(bitDepth == 8){
            fbo.allocate(fbow,fboh, GL_RGBA);
            fbo.activateAllDrawBuffers();
            //px.allocate(fbow,fboh, GL_RGBA );
            lastPx.operator = (px);
        }else if (bitDepth == 16){
            fbo.allocate(fbow,fboh, GL_RGBA16);
            // px.allocate(fbow,fboh, GL_RGBA16 );
            lastPx.operator =(px);
        }
    }catch (const std::bad_alloc&) {
        cout << "Bad Alloc of FBO" << endl;
    }

    //Basic setup
    blur.setup(fbow+4, fboh+4,32, 0.2f, 2, 0.5f);

    //Parse Visualization Strucuture
    xPxSpace = 1.0f;
    yPxSpace = 1.0f;
    float yVF = fboy;

    // Store all rows and cols.
    for(int i=0; i<csv.getNumRows(); i++) {
        float xVF = fbox;
        for(unsigned j=0; j<unsigned(csv.data[unsigned(i)].size()); j++) {
            //Define Structure Variables
            //Microcontroller
            int raspi = ofToInt(ofSplitString(ofToString(csv.data[i][j]), ":")[0]);
            //LED Address
            int addr = ofToInt(ofSplitString(ofToString(csv.data[i][j]), ":")[1]);

            //Assign Structure Vars
            //Order by Horizontal Line
            //structure[34][910][6];
            //[raspi][address][x,y,r,g,b,a]
            structure[raspi][addr][0] = xVF;
            structure[raspi][addr][1] = yVF;
            structure[raspi][addr][2] = 0; //red
            structure[raspi][addr][3] = 0; //green
            structure[raspi][addr][4] = 0; //blue
            structure[raspi][addr][5] = 255; //alpha

            //Setup Data Streams
            dataHandler[raspi].structure[raspi][addr][0] = xVF;
            dataHandler[raspi].structure[raspi][addr][1] = yVF;
            dataHandler[raspi].structure[raspi][addr][2] = 0;
            dataHandler[raspi].structure[raspi][addr][3] = 0;
            dataHandler[raspi].structure[raspi][addr][4] = 0;
            dataHandler[raspi].structure[raspi][addr][5] = 255;


            //Create Vector Points
            vectorField[i][j][0].x=xVF;
            vectorField[i][j][0].y=yVF;

            xVF += xPxSpace;
        }
        yVF+=yPxSpace;
    }

    //GPULUT
    setLUT = activeLUT;
    setupLUTs();

    /*
         * Set to Paramters through GUI Later
         */
    history = 0.0f;

    /*
         * Shows XML
         */
    showsXMLFile = "shows.xml";
    showsXML.load(showsXMLFile);
    showsXML.setTo("SHOWSETTINGS//CONFIG[0]");
    showsCycle = showsXML.getChild("cycle").getIntValue();
    showsXML.setTo("SHOWSETTINGS//SHOWS");

    totalShows = showsXML.getNumChildren();
    currentShow = 0;
    playShow = false;
    lastSlideShow = -1;

    /*
         * Slideshow
         */
    slideshow = new ofxThreadedSlideshow();
    //Setup Slideshow
    imageDuration = 10;
    modelDuration = 60;
    //Setup Slideshow and start thread
    windowW = fbow;
    windowH = fboh;
    slideshow->mode = 1;
    slideshow->xml = "images/threadLoadExample/content.xml";
    slideshow->width = windowW;
    slideshow->height = windowH;
    slideshow->duration = imageDuration;
    slideshow->fade = true;
    slideshow->center = true;
    slideshow->scale = true;
    slideshow->folder = "images/threadLoadExample";
    slideshow->font.load("fonts/Roboto-Regular.ttf",18);
    slideshow->start();
    yPos =0.9f;
    scM = 0.2f;

    cout << "SEND DATA: " << sendData << endl;

    programLoaded = true;

    if(sendData && programLoaded){
        initiateDataComms();
    }
    slideImg = new ofImage();
    //Allocate Slide
    slideImg->allocate(slideshow->width,slideshow->height,OF_IMAGE_COLOR_ALPHA);

    slideModel = new ofxAssimpModelLoader();
    slideMov = new ofVideoPlayer();
    random = new PxRandom();
}


//--------------------------------------------------------------
void ofApp::update(){
    std::stringstream strm;
    strm << "UCLA Boyer5 | Visualizer | V1.3 |" << ofGetWindowWidth()<< "x" << ofGetWindowHeight() << " | fps: " << round(ofGetFrameRate());
    ofSetWindowTitle(strm.str());
    if(activeLUT != setLUT){
        setupLUTs();
    }

    //Slideshow
    if(!playShow && !debug){
        updateSlideshow();
    }

    //Update FBO And Save Pixels to PX
    fbo.begin();
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    if(showDebug){
        blur.setScale(debugBlur);
    }else{
        if(!playShow){
            blur.setScale(slideshow->getBlur());
        }else{
            blur.setScale(showBlur);
        }
    }
    blur.setRotation(ofRandom( -PI, PI));
    blur.begin();

    float alpha;
    if(showDebug){
        history = debugTrail;
        alpha = (1.0f - history) * 255.0f;
    }else{
        if(!playShow){
            //Clearing The buffer (depends on history value)
            history =  slideshow->getTrail();
            alpha = (1.0f - history) * 255.0f;
        }else{
            alpha = (1.0f - showTrail ) * 255.0f;
        }
    }

    if( contentType != "3dmodel"  || showDebug ){
        ofSetColor(0, alpha);
        ofDrawRectangle(0,0,fbow,fboh+4);
    }else{
        ofClear(0,alpha);
    }

    /*
         * Shows
         */
    if(showDebug){
        //Solid Color
        if(debugSolidColor){
            ofSetColor(solidColor);
            ofFill();
            ofDrawRectangle(0,0,fbow,fboh);
        }else if(toggleDebugRandom){
            ofSetColor(manualColor);
            ofFill();
            debugRandom->draw();
        }
    }else{
        if(playShow){
            drawShows();
        }else{
            drawSlideshow();
        }
    }

    blur.end();
    blur.draw();
    ofEnableBlendMode(OF_BLENDMODE_DISABLED);
    fbo.end();

    fbo.readToPixels(px);

    /*
     * Histogram Update
     */

    if((isNewFrame = px.isNewFrame(lastPx))){
        //Histogram Update
        // get separate red, green, blue channels
        r.setFromPixels(px.getChannel(0));
        g.setFromPixels(px.getChannel(1));
        b.setFromPixels(px.getChannel(2));
        rgb.setFromGrayscalePlanarImages(r,g,b);
        // convert rgb to hsv and grab each channel individually
        cvCvtColor(rgb.getCvImage(), hsv.getCvImage(), CV_BGR2HSV);

        v.setFromPixels(hsv.getPixels().getChannel(2));

        // get histograms
        histogramR = histogram.getHistogram(r, bins);
        histogramG = histogram.getHistogram(g, bins);
        histogramB = histogram.getHistogram(b, bins);
        histogramV = histogram.getHistogram(v, bins);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    if(doLUT){
        if(!showLut){
            fbo.draw(0,0, W,H+8);
        }
        if(cubeLUT){
            ofImage correctedImg;
            correctedImg.setFromPixels(px);
            lutFilter.begin();
            lutFilter.setUniformTexture("tex",correctedImg.getTexture(), 0);
            lutFilter.setUniformTexture("lutTexure", GL_TEXTURE_3D, int(texture3D), 1);
            lutFilter.setUniform1f("lutSize", LUTsize);
            lutFilter.setUniform2f("lutIntensity", ofVec2f(lutIntensity,1));
            fbo.begin();
            ofSetColor(255, 255);
            ofDrawRectangle(0,0,fbow,fboh+8);

            plane.draw();
            lutFilter.end();
            fbo.end();
            fbo.readToPixels(px);

            if(showLut){
                fbo.draw(0,0, W,H+8);
            }
        }else if(matLUT){
            for (int i=0; i<fbo.getWidth(); i++){
                for(int j=0; j<fbo.getHeight();j++){
                    ofColor inColor = px.getColor(i,j);
                    calColMat[0] = 1;
                    calColMat[1] = inColor.r;
                    calColMat[2] = inColor.g;
                    calColMat[3] = inColor.b;

                    /*Equation
                        1*a1 + r*a2 + g*a3 + b*a4 = R
                        1*b1 + r*b2 + g*b3 + b*b4 = G
                        1*c1 + r*c2 + g*c3 + b*c4 = B
                        */
                    adjColMat[0] = (calColMat[0] * lutMat[0][0]) + (calColMat[1] * lutMat[1][0]) + (calColMat[2] * lutMat[2][0]) + (calColMat[3] * lutMat[3][0]);
                    adjColMat[1] = (calColMat[0] * lutMat[0][1]) + (calColMat[1] * lutMat[1][1]) + (calColMat[2] * lutMat[2][1]) + (calColMat[3] * lutMat[3][1]);
                    adjColMat[2] = (calColMat[0] * lutMat[0][2]) + (calColMat[1] * lutMat[1][2]) + (calColMat[2] * lutMat[2][2]) + (calColMat[3] * lutMat[3][2]);

                    ofColor adjustedColor = ofColor(adjColMat[0],adjColMat[1],adjColMat[2],255);
                    px.setColor(i,j,adjustedColor);
                }
            }
            if(showLut){
                ofImage matImage;
                matImage.setFromPixels(px);
                matImage.update();
                matImage.draw(0,0,W,H+8);
            }
        }
    }else{
        fbo.draw(0,0, W,H+8);
    }

    if((isNewFrame = px.isNewFrame(lastPx))){
        lastPx.operator =(px);
    }

    if(sendData && isNewFrame){
        for(unsigned int i = 1; i < sizeof(structure)/sizeof(structure[0]); i++ ){
            if(dataHandler[i].isThreadRunning()){
                if(isNewFrame){
                    dataHandler[i].isNewFrame = true;
                    dataHandler[i].px.operator =( px );
                }
            }
        }
    }
    if(!playShow && slideshow->isThreadRunning()){
        slideshow->draw();
    }
}

bool ofApp::mcAvailable(string ipAddress){
    int ping_ret;
    string command = "ping -c 2 " + ipAddress;
    int status = system(command.c_str());
    if (-1 != status){
        ping_ret = WEXITSTATUS(status);
        if(ping_ret==0){
            return true;
        }else{
            return false;
        }
    }
    return false;
}

void ofApp::initiateDataComms(){
    /*
         * Setup Data Stream Threads
         */
    try{
        for(unsigned int i = 1; i < sizeof(structure)/sizeof(structure[0]); i++ ){

            mcIP = "10.16.34.1";
            char mcIPEnd[2];
            sprintf(mcIPEnd,"%02d",i);
            mcIP += mcIPEnd;
            if(dataHandler[i].isThreadRunning()){
                dataHandler[i].stop();
            }
            dataHandler[i].MC = i;
            dataHandler[i].ipAddr =mcIP;
            dataHandler[i].configPort = configPort;
            dataHandler[i].pxWidth = fbow;
            dataHandler[i].pxHeight = fboh;
            dataHandler[i].dataPort = txPort;
            dataHandler[i].bitDepth = bitDepth;
            dataHandler[i].powerLevel = (float)powerLevel / powerLevel.getMax();
            dataHandler[i].protocolMode = protocolMode;
            dataHandler[i].dataFMT = dataFMT;
            dataHandler[i].dataFMTSize = dataFMTSize;
            dataHandler[i].sendData = sendData;
            dataHandler[i].clipping = clipping;
            if(mcAvailable(mcIP)){
                dataHandler[i].start();
                cout << "Start Network Connection: " << dataHandler[i].ipAddr << endl;
                dataInitiated = true;
            }
        }
    }catch(exception &e) {
        cout << "EXCEPTION: " << e.what() << endl;
    }
}

//--------------------------------------------------------------
void ofApp::initiateShows(){
    if(totalShows > 0){
        clearSlides();
        stopShowsThreads();
        currentShowElement = "//SHOW[" + ofToString(currentShow) + "]";
        cout << "Show: " << currentShowElement << endl;
        showsXML.setTo(currentShowElement);
        showType = showsXML.getChild("type").getValue();
        if(showType == "random"){
            /*
             * Random Colors
             */
            //Setup Random and start thread
            random->width = fbow;
            random->height = fboh;
            random->mode = showsXML.getChild("mode").getIntValue();
            random->refreshRate = showsXML.getChild("refreshRate").getIntValue();
            random->lowColor = showsXML.getChild("lowColor").getFloatValue();
            random->highColor = showsXML.getChild("highColor").getFloatValue();
            random->start();

            showName = showsXML.getChild("name").getValue();
            showDuration = showsXML.getChild("duration").getFloatValue();
            showBlur = showsXML.getChild("blur").getFloatValue();
            showTrail = showsXML.getChild("trail").getFloatValue();
        }
        showInitiated = true;
        restartShowTimer();
        currentShow = (currentShow +1) % totalShows;
        playShow = true;
        threadCount = ofSystem("ps h -o nlwp " + ofToString(PID));
    }else{
        playShow = false;
    }
}

//------------------------------------------------------------
void ofApp::restartShowTimer(){
    time(&showCurrentTime);
    time(&showStartTime);
}

//--------------------------------------------------------------
void ofApp::drawShows(){
    if(totalShows > 0){
        if(showTimeDiff() >= showDuration){
            showInitiated = false;
            playShow = false;
            random->clearRandom = true;
            clearSlides();
            stopShowsThreads();
            slideshow->start();
            //slideshow->internetAccess();
            loadContent();

            lastSlideShow = slideshow->getNextCount();
        }else{
            time(&showCurrentTime);
            ofSetColor(manualColor);
            ofFill();
            if(showType == "random"){
                random->draw();
            }
        }
    }else{
        playShow = false;
        random->stop();
        delete random;
        random = new PxRandom();
    }
}

//--------------------------------------------------------------
void ofApp::updateSlideshow(){
    //Check Whether to Run Shows
    if( totalShows > 0){
        if(slideshow->getNextCount() != 0 &&
                slideshow->getNextCount() % showsCycle == 0 &&
                slideshow->getNextCount() != lastSlideShow){
            initiateShows();
        }else{
            //Load Next Slideshow
            if( slideshow->isThreadRunning() && slideshow->isFrameNew()  && slideshow->isInitiated()){
                clearSlides();
                slideshow->nextContent();
                if(slideshow->getNextCount() % showsCycle != 0){
                    loadContent();
                }
            }
        }
    }else{
        if( slideshow->isThreadRunning() && slideshow->isFrameNew()  && slideshow->isInitiated()){
            clearSlides();
            slideshow->nextContent();
            loadContent();
        }
    }
    if(slideshow->isThreadRunning() && slideshow->getContentType() == "video"){
        try{
            slideMov->update();
        }catch(exception &e) {
            ofLogError("threadedFunction()") << "Slideshow Image Load EXCEPTION: " << e.what();
        }
    }
    if(slideshow->isThreadRunning() && slideshow->getContentType() == "3dmodel"){
        try{
            slideModel->update();
        }catch(exception &e) {
            ofLogError("threadedFunction()") << "Slideshow Image Load EXCEPTION: " << e.what();
        }
    }
}

//--------------------------------------------------------------
void ofApp::drawSlideshow(){
    if(slideshow->isInitiated()){
        if(slideshow->fadeAlpha != 255){
            ofSetColor(manualColor, slideshow->fadeAlpha);
        }else{
            ofSetColor(manualColor);
        }
        ofFill();

        if(contentType == "image"){
            if(slideImg->isAllocated()){
                slideImg->draw(slideshow->getPos(), slideshow->scaledWidth, slideshow->scaledHeight);
            }else{
                clearSlides();
            }
        }else if(contentType == "video"){
            if(slideMov->isLoaded() && slideMov->isPlaying()){
                slideMov->draw(slideshow->getPos(), slideshow->scaledWidth, slideshow->scaledHeight);
            }else{
                clearSlides();
            }
        }else if(contentType == "3dmodel"){
            ofEnableDepthTest();
#ifndef TARGET_PROGRAMMABLE_GL
            glShadeModel(GL_SMOOTH); //some model / light stuff
#endif
            light.enable();
            light.lookAt(
                        ofVec3f(
                            slideModel->getPosition().x,
                            slideModel->getPosition().y,
                            slideModel->getPosition().z
                            )
                        );
            ofColor defaultColor(manualColor);
            ofColor lightColor(defaultColor);

            float alpha = slideshow->fadeAlpha;
            if(alpha != 255){
                lightColor= ofColor(
                            defaultColor.r*alpha,
                            defaultColor.g*alpha,
                            defaultColor.b *alpha
                            );
            }
            light.setDiffuseColor(lightColor);
            light.setAmbientColor(lightColor);
            light.setSpecularColor(lightColor);
            ofEnableSeparateSpecularLight();

            ofPushMatrix();
            ofTranslate(slideModel->getPosition().x, slideModel->getPosition().y, 0);
            slideModel->setRotation(0, rotateIter++, 0,1, 0);
            ofTranslate(-slideModel->getPosition().x, -slideModel->getPosition().y, 0);
            if(slideModel->hasMeshes()){
                if(slideshow->getMeshMode() == 0){
                    slideModel->draw(OF_MESH_POINTS);
                }else if(slideshow->getMeshMode() == 1){
                    slideModel->draw(OF_MESH_WIREFRAME);
                }else if(slideshow->getMeshMode() == 2){
                    slideModel->draw(OF_MESH_FILL);
                }
            }
            ofPopMatrix();
#ifndef TARGET_PROGRAMMABLE_GL
            glEnable(GL_NORMALIZE);
#endif
            ofDisableDepthTest();
            light.disable();
            ofDisableLighting();
            ofDisableSeparateSpecularLight();
        }
    }
    ofSetColor(manualColor);
}

//--------------------------------------------------------------
void ofApp::loadContent(){
    contentType = slideshow->getContentType();
    clearSlides();
    slideshow->waitForThread();
    //------------------------- Image
    if(contentType == "image"){

        if(slideshow->mode == 0){
            slideshow->duration = imageDuration;
        }else if(slideshow->mode ==1){
            slideshow->setXmlDuration();
        }

        int i = 0;
        int sleepyTime = 100;
        //LOAD CONTENT
        try{
            if(slideImg->load(slideshow->currentContent())){
                slideImg->update();
                while(slideImg->getWidth()<=0){
                    ofSleepMillis(sleepyTime);
                    slideshow->restartTimer();
                    if(i >= sleepyTime){
                        slideshow->nextContent();
                        loadContent();
                        return;
                    }
                    i++;
                }
            }else{
                slideshow->nextContent();
                loadContent();
                return;
            }
        }catch(exception &e) {
            ofLogError("threadedFunction()") << "Slideshow Image Load EXCEPTION: " << e.what();
        }

        //------------------------------Video
    }else if(contentType == "video"){
        //LOAD CONTENT
        try{
            slideMov->loadAsync(slideshow->currentContent());
            if(slideMov->isLoaded()){
                int i = 0;
                int sleepyTime = 150;
                while(slideMov->getCurrentFrame() < 0 ){
                    ofSleepMillis(sleepyTime);
                    slideshow->restartTimer();
                    if(i >= sleepyTime){
                        slideshow->restartTimer();
                        slideshow->nextContent();
                        loadContent();
                        return;
                    }
                    i++;
                }

                if(slideshow->mode == 0 ){
                    if(slideMov->getDuration() > 0){
                        slideshow->duration = slideMov->getDuration();
                    }else{
                        slideshow->duration = 60;
                    }
                }

                if(slideshow->mode == 1){
                    if(slideshow->getXmlDuration() == 0 &&
                            slideshow->getVideoMode() == "file"){
                        slideshow->duration = slideMov->getDuration();
                        slideshow->restartTimer();
                        slideshow->setPosSize(slideMov->getWidth(), slideMov->getHeight());

                    }else{
                        slideshow->setXmlDuration();
                        slideshow->restartTimer();
                    }
                }

                if(slideMov->getDuration() > 0){
                    slideshow->duration = slideMov->getDuration();
                }

                slideshow->setPosSize(slideMov->getWidth(), slideMov->getHeight());
                if(slideshow->getVideoMode() == "livestream"){
                    slideMov->setLoopState(OF_LOOP_NORMAL);
                }else{
                    slideMov->setLoopState(OF_LOOP_NONE);
                }
                slideMov->play();

                slideshow->restartTimer();
            }else{
                slideshow->nextContent();
                loadContent();
                return;
            }
        }catch(exception &e) {
            ofLogError("threadedFunction()") << "Slideshow Video Load EXCEPTION: " << e.what();
        }
        //-------------------------------3D Model
    }else if(contentType == "3dmodel"){
        rotateIter = 0.0f;
        slideModel->createEmptyModel();
        if(slideshow->mode == 0){
            slideshow->duration = modelDuration;
        }else if(slideshow->mode==1){
            slideshow->setXmlDuration();
        }

        int i = 0;
        int sleepyTime = 100;
        //Load Model
        try{
            if( slideModel->loadModel(slideshow->currentContent(), true)){
                while(!slideModel->hasMeshes()){
                    ofSleepMillis(sleepyTime);
                    slideshow->restartTimer();

                    if(i >= sleepyTime){
                        //slideshow->internetAccess();
                        slideshow->nextContent();
                        loadContent();
                        return;
                    }
                    i++;
                }

                //Scale Model
                slideModel->setLoopStateForAllAnimations(OF_LOOP_NORMAL);
                if(slideModel->getAnimationCount() > 0 ){
                    slideModel->playAllAnimations();
                }else{
                    slideModel->setPausedForAllAnimations(true);
                }
            }else{
                slideshow->nextContent();
                loadContent();
                return;
            }
        }catch(exception &e) {
            ofLogError("threadedFunction()") << "Slideshow Model Load EXCEPTION: " << e.what();
        }
    }else if(contentType == "unkown format"){
        slideshow->nextContent();
        loadContent();
        return;
    }

    threadCount = ofSystem("ps h -o nlwp " + ofToString(PID));
    CPUMEM= ofSystem("ps -p " + ofToString(PID) + " -o %cpu,%mem  | tail -n +2");
    if(!slideshow->isThreadRunning()){
        slideshow->start();
    }
    scalePosContent();
    slideshow->restartTimer();
    cout << "End Load Content: " << slideshow->currentContent() << " | Img- " << slideImg->isAllocated() <<" | 3D-" << slideModel->hasMeshes() << " | Video-" <<  slideMov->isLoaded() << endl;
}

//--------------------------------------------------------------
void ofApp::clearSlides(){
    if(slideImg->isAllocated()){
        slideImg->clear();
        delete slideImg;
        slideImg = new ofImage();
        slideImg->allocate(slideshow->width,slideshow->height,OF_IMAGE_COLOR_ALPHA);
        slideImg->clear();
    }
    if(slideModel->hasMeshes()){
        slideModel->resetAllAnimations();
        slideModel->stopAllAnimations();
        slideModel->clear();
        delete slideModel;
        slideModel = new ofxAssimpModelLoader();
        slideModel->clear();
    }

    if(slideMov->isPlaying()){
        slideMov->stop();
    }
    if(slideMov->isLoaded()){
        //slideMov->close();
        delete slideMov;
        slideMov = new ofVideoPlayer();
    }
}

//-------------------------------------------------------------
void ofApp::stopShowsThreads(){
    if(slideshow->isThreadRunning()){
        slideshow->waitForThread();
    }
    if(random->isThreadRunning()){
        random->cleanup();
        random->waitForThread();
        delete random;
        random = new PxRandom();
    }
    if(debugRandom->isThreadRunning()){
        debugRandom->cleanup();
        debugRandom->waitForThread();
        delete debugRandom;
        debugRandom = new PxRandom();
    }
}

//-------------------------------------------------------------
int ofApp::showTimeDiff(){
    return difftime(showCurrentTime,showStartTime);
}

//--------------------------------------------------------------
void ofApp::scalePosContent(){
    if(contentType == "image"){
        slideshow->setPosSize(slideImg->getWidth(), slideImg->getHeight());
    }else if(contentType == "video"){
        slideshow->setPosSize(slideMov->getWidth(), slideMov->getHeight());
    }else if(contentType == "3dmodel"){
        ofDisableArbTex();
        slideModel->calculateDimensions();
        slideModel->setScaleNormalization(true);
        ofVec3f modScale = slideModel->getScale().getLimited(scM);
        slideModel->setScale(modScale.x, modScale.y,modScale.z );
        slideModel->setPosition(fbow/2.0f, fboh  * yPos , 0.0f);
    }
}

//-------------------------------------------------------------
//GUI Loading Functions
//GUI

//--------------------------------------------------------------
void ofApp::drawGnav(ofEventArgs & args){
    ofSetColor( 0,128,255 );
    robotoSmallBold.drawString( "CPU | MEM: ", 20, ofGetWindowHeight()-40 );
    ofSetColor(180 );
    robotoSmallBold.drawString(CPUMEM,120,ofGetWindowHeight()-40 );
    ofSetColor( 0,128,255 );
    robotoSmallBold.drawString( "Threads: ", 20, ofGetWindowHeight()-20 );
    ofSetColor(180 );
    robotoSmallBold.drawString(threadCount,90,ofGetWindowHeight()-20);

    ofSetColor(255,0,0);
    r.draw(0, 0);
    ofSetColor(255,75,75);

    drawHistogram(histogramR);

    ofTranslate(fbow, 0);

    ofSetColor(0, 255, 0);
    g.draw(0, 0);
    ofSetColor(75, 255, 75);
    drawHistogram(histogramG);

    ofTranslate(fbow, 0);

    ofSetColor(0,0, 255);
    b.draw(0, 0);
    ofSetColor(75,75, 255);
    drawHistogram(histogramB);
    /*

    ofTranslate(-2*fbow, fboh);

    ofSetColor(255);
    h.draw(0, 0);
    drawHistogram(histogramH);

    ofTranslate(fbow, 0);

    ofSetColor(255);
    s.draw(0, 0);
    drawHistogram(histogramS);
    */
    ofTranslate(fbow, 0);

    ofSetColor(255);
    v.draw(0, 0);
    ofSetColor(128);
    drawHistogram(histogramV);

    ofTranslate(-3*fbow, 0);
    ofSetColor(128,200);
    robotoSmallBold.drawString( "Red ", 10,15 );
    robotoSmallBold.drawString( "Green", fbow + 10 , 15 );
    robotoSmallBold.drawString( "Blue ", (2*fbow) + 10 , 15 );
    robotoSmallBold.drawString( "Value ", (3*fbow) + 10 , 15 );

    //ofDrawBitmapString("red", 0, 15);
    //ofDrawBitmapString("green", fbow, 15);
    //ofDrawBitmapString("blue", 2*fbow, 15);
    //ofDrawBitmapString("hue", 0, 15+fboh);
    //ofDrawBitmapString("saturation", fbow, 15+fboh);
    //ofDrawBitmapString("value", 3*fbow, 15);
    ofSetColor(manualColor);
    ofTranslate(0,0);


}

//--------------------------------------------------------------
void ofApp::drawGui(ofEventArgs & args){
    std::stringstream strm;
    if(showColorMgmt || showNetworking || showDebug){
        strm << currentNav;
    }else{
        strm << "Control Window";
    }
    ofSetWindowTitle(strm.str());

    GlobalNav.draw();
    if(showColorMgmt){
        ColorMgmtGui.draw();
    }

    if(showNetworking){
        NetworkingGui.draw();
    }

    if(showDebug){
        DebugGui.draw();
    }
}

//--------------------------------------------------------------
void ofApp::drawGstat(ofEventArgs & args){
    time ( &rawtime );
    std::stringstream strm;
    char tmstr[50];
    sprintf(tmstr,  "%s", ctime (&rawtime) );
    strm << "Boyer 5 | Stats | ";// << tmstr ;
    ofSetWindowTitle(strm.str());
    //Shows
    ofSetColor( 0,128,255 );
    robotoBold.drawString( "Current Show: ", 10, 40 );
    ofSetColor(180 );
    string currentShowDetails = slideshow->getContentType() +
            " | " +
            ofToString(slideshow->duration - slideshow->getTimeRemaining()) +
            " seconds";
    if(!playShow){
        robotoNormal.drawString(slideshow->getCurrentContentName(), 230 , 40);
        ofSetColor( 0,128,255 );
        robotoBold.drawString( "Mode | Length: ", 10, 80 );
        ofSetColor(180 );
        robotoNormal.drawString(currentShowDetails, 240 , 80);
        ofSetColor( 0,128,255 );
        robotoBold.drawString( "Next Show: ", 10, 120 );
        ofSetColor(180 );
        robotoNormal.drawString(slideshow->getNextContentName(), 190 , 120);
        ofSetColor( 0,128,255 );
        robotoBold.drawString( "Mode: ", 10, 160 );
        ofSetColor(180 );
        robotoNormal.drawString(slideshow->getNextContentType(), 110 , 160);
    }else{
        robotoNormal.drawString(showName, 230 , 40);
        ofSetColor( 0,128,255 );
        robotoBold.drawString( "Mode | Length: ", 10, 80 );
        ofSetColor(180 );
        robotoNormal.drawString("Show | " + ofToString(showDuration - showTimeDiff()), 240 , 80);
        ofSetColor( 0,128,255 );
        robotoBold.drawString( "Next Show: ", 10, 120 );
        ofSetColor(180 );
        robotoNormal.drawString(slideshow->getCurrentContentName(), 190 , 120);
        ofSetColor( 0,128,255 );
        robotoBold.drawString( "Mode | Length: ", 10, 160 );
        ofSetColor(180 );
        robotoNormal.drawString(currentShowDetails, 240 , 160);
    }

    //LUT
    ofSetColor( 0,128,255 );
    robotoBold.drawString( "LUT: ", 10, 200 );
    ofSetColor(180 );

    robotoNormal.drawString(doLutStr, 90 , 200);
    ofSetColor( 0,128,255 );
    robotoBold.drawString( "Mode:  ", 140, 200 );
    ofSetColor(180 );

    robotoNormal.drawString(lutModeStr, 240 , 200);
    ofSetColor( 0,128,255 );
    robotoBold.drawString( "Display LUT: ", 340, 200 );
    ofSetColor(180 );
    robotoNormal.drawString(showLutStr, 530 , 200);

    ofSetColor( 0,128,255 );
    robotoBold.drawString( "LUT: ", 590, 200 );
    ofSetColor(180 );
    robotoNormal.drawString(currentLUT, 670 , 200);

    //line 5
    //Content Items
    int line5 = 240;
    ofSetColor( 0,128,255 );
    robotoBold.drawString( "Content Count: ", 10, line5 );
    ofSetColor(180 );
    robotoNormal.drawString(ofToString(slideshow->getTotalContentCount()),240,line5);
    //  << " | Elapsed: " << ofGetElapsedTimef()
    ofSetColor( 0,128,255 );
    robotoBold.drawString( "Show Count: ", 300, line5 );
    ofSetColor(180 );
    robotoNormal.drawString(ofToString(totalShows),495,line5);
    ofSetColor( 0,128,255 );
    robotoBold.drawString( "Elapsed Time: ", 535, line5 );
    ofSetColor(180 );
    robotoNormal.drawString(ofToString(ofGetElapsedTimef()),750,line5);


    //Line 6
    ofSetColor(32,0,0);
    ofFill();
    ofDrawRectangle(0,ofGetWindowHeight()-60,ofGetWindowWidth(),60);

    int BottomText = 285;
    //pixels
    ofSetColor( 0,128,255 );
    robotoBold.drawString("LEDs: ", 10,BottomText);
    ofSetColor(180 );
    robotoNormal.drawString(pxSize,95,BottomText);
    //FPS
    ofSetColor( 0,128,255 );
    sprintf(fps, "%0.1f", ofGetFrameRate());
    robotoBold.drawString( "FPS: ", 580, BottomText );
    ofSetColor(180 );
    robotoNormal.drawString(fps,655,BottomText);
    //Network
    ofSetColor( 0,128,255 );
    robotoBold.drawString( "Data Port: ", 740, BottomText );
    ofSetColor(180 );
    robotoNormal.drawString(networkInfo,890,BottomText);
    ofSetColor( 0,128,255 );
    robotoBold.drawString( "1st IP: ", 995, BottomText );
    ofSetColor(180 );
    robotoNormal.drawString(dataHandler[1].ipAddr,1100,BottomText);
}

//--------------------------------------------------------------
void ofApp::drawHistogram(vector<float> & h) {
    ofBeginShape();
    ofNoFill();
    ofSetLineWidth(3);
    for (int i=0; i<h.size(); i++) {
        float x = ofMap(i, 0.0f, h.size(), 0.0f, (float)fbow, true);
        float y = ofMap((float)h[i], 0.0f, 0.05f, (float)fboh, 0.0f, true);
        ofVertex(x, y);
    }
    ofEndShape();
}

//--------------------------------------------------------------
void ofApp::exit(){
    //colorMGT Gui Remove Listeners
    colorManagement.removeListener(this, &ofApp::ofxColorManPressed);
    networking.removeListener(this, &ofApp::networkingPressed);

    //Networking //Remove Listeners
    doLUT.removeListener(this, &ofApp::enableLutPressed);
    showLut.removeListener(this, &ofApp::showLutPressed);
    cubeLUT.removeListener(this, &ofApp::cubeLutPressed);
    matLUT.removeListener(this, &ofApp::matLutPressed);
    powerLevel.removeListener(this, &ofApp::powerLevelChanged);


    GlobalNav.saveToFile("settings.xml");
    ColorMgmtGui.saveToFile("settings.xml");
    NetworkingGui.saveToFile("settings.xml");
    DebugGui.saveToFile("settings.xml");
    closeThreads();

    ofLog(OF_LOG_NOTICE,"Clean Exit - Goodbye");
}

//--------------------------------------------------------------
//Reset Thread Configuration
void ofApp::resetThreads(){
    if(!dataInitiated){
        initiateDataComms();
    }
    for(unsigned int i = 1; i < sizeof(structure)/sizeof(structure[0]); i++ ){
        dataHandler[i].sendData = sendData;
        dataHandler[i].clipping = clipping;
        //Trigger Pi Reconfigure
        if(dataHandler[i].bitDepth != bitDepth){
            dataHandler[i].bitDepth = bitDepth;
            dataHandler[i].init = false;
        }
        if((float) powerLevel / powerLevel.getMax() != dataHandler[i].powerLevel){
            dataHandler[i].powerLevel = (float) powerLevel / powerLevel.getMax();
            dataHandler[i].isConnected = false;
            dataHandler[i].config = true;
        }
        if(dataHandler[i].dataFMT != dataFMT){
            dataHandler[i].dataFMT = dataFMT;
            dataHandler[i].init = false;
        }

        if(dataHandler[i].dataFMTSize != dataFMTSize){
            dataHandler[i].dataFMTSize = dataFMTSize;
            dataHandler[i].init = false;
        }

        if(protocolMode != dataHandler[i].protocolMode){
            dataHandler[i].protocolMode = protocolMode;
            dataHandler[i].init = false;
        }
    }
}

void ofApp::closeThreads(){
    for(unsigned int i = 1; i < sizeof(structure)/sizeof(structure[0]); i++ ){
        if(dataHandler[i].isThreadRunning()){
            dataHandler[i].waitForThread();
        }
    }
    // stop the thread
    if(slideshow->isThreadRunning()){
        slideshow->waitForThread();
    }
    if(random->isThreadRunning()){
        random->waitForThread();
        delete random;
        random = new PxRandom();
    }
    if(debugRandom->isThreadRunning()){
        debugRandom->waitForThread();
        delete debugRandom;
        debugRandom = new PxRandom();
    }
    ofLog(OF_LOG_NOTICE,"All Threads Stopped");
}

void ofApp::ofxColorManPressed(){
    showColorMgmt^=true;
    showNetworking = false;
    showDebug=false;

    if(!slideshow->isThreadRunning() && !playShow){
        debugRandom->init = false;
        closeThreads();
        slideshow->restartTimer();
        slideshow->start();
        loadContent();
    }
    if(debugRandom->isThreadRunning()){
        debugRandom->waitForThread();
        delete debugRandom;
        debugRandom = new PxRandom();
    }

    currentNav = ColorMgmtGui.getName();
}

void ofApp::networkingPressed(){
    showNetworking^=true;
    showColorMgmt = false;
    showDebug=false;

    if(!slideshow->isThreadRunning() && !playShow){
        debugRandom->init = false;
        closeThreads();
        slideshow->restartTimer();
        slideshow->start();
        loadContent();
    }
    if(debugRandom->isThreadRunning()){
        debugRandom->waitForThread();
        delete debugRandom;
        debugRandom = new PxRandom();
    }
    currentNav = NetworkingGui.getName();
}


void ofApp::debugPressed(){
    showNetworking=false;
    showColorMgmt = false;
    showDebug^=true;

    if(playShow){
        playShow = false;
    }

    if(showDebug){
        if(slideshow->isThreadRunning()){
            slideshow->waitForThread();
        }
        if(playShow){
            playShow = false;
            if(random->isThreadRunning()){
                random->waitForThread();
            }
        }
    }else{
        if(debugRandom->isThreadRunning()){
            debugRandom->waitForThread();
            delete debugRandom;
            debugRandom = new PxRandom();
        }
        slideshow->restartTimer();
        slideshow->start();
        loadContent();
    }
    currentNav = DebugGui.getName();
}

void ofApp::enableLutPressed(const void * sender, bool & pressed){
    if(doLUT){
        doLutStr = "on";
    }else{
        doLutStr = "off";
    }
}

void ofApp::showLutPressed(const void * sender, bool & pressed){
    if(showLut){
        showLutStr= "on";
    }else{
        showLutStr = "off";
    }
}

void ofApp::cubeLutPressed(const void * sender, bool & pressed){
    if(cubeLUT){
        matLUT = false;
        lutModeStr = "Cube";
        currentLUT = cubeStr;
    }
}

//--------------------------------------------------------------
//Matrix Based LUT Pressed
void ofApp::matLutPressed(const void * sender, bool & pressed){
    if(matLUT){
        cubeLUT = false;
        lutModeStr = "Matrix";
        currentLUT = "Experimental";
    }
}

//--------------------------------------------------------------
//Power Level Changed
void ofApp::powerLevelChanged(int & powerLevel){
    if(sendData && programLoaded){
        resetThreads();
    }
}

//--------------------------------------------------------------
//Clipping Changed
void ofApp::clippingChanged(int & clipping){
    if(sendData && programLoaded){
        resetThreads();
    }
}
//--------------------------------------------------------------
//UDP Pressed
void ofApp::udpPressed(const void * sender, bool & pressed){
    if(udp){
        tcp = false;
        protocolMode= 1;
        ofSetFrameRate( 30 );
    }
    if(sendData && programLoaded){
        resetThreads();
    }
}

//--------------------------------------------------------------
//TCP Pressed
void ofApp::tcpPressed(const void * sender, bool & pressed){
    if(tcp){
        udp = false;
        protocolMode= 0;
        ofSetFrameRate( 15 );
    }
    if(sendData && programLoaded){
        resetThreads();
    }
}

//--------------------------------------------------------------
//ALL HEX (Bytes) Pressed
void ofApp::allHexPressed(const void * sender, bool & pressed){
    if(allHex){
        dataFMT = 0;
        allHexA = false;
        mcAddrRGB = false;
        mcAddrRGBA = false;
        mcAddrHEX = false;
        mcAddrHEXA = false;
        if(eightbit){
            dataFMTSize = 5;//6;
        }else if(sixteenbit){
            dataFMTSize = 9;
        }
    }
    if(sendData && programLoaded){
        resetThreads();
    }
}

//--------------------------------------------------------------
//All HEX+Alpha Pressed
void ofApp::allHexAPressed(const void * sender, bool & pressed){
    if(allHexA){
        dataFMT = 1;
        allHex = false;
        mcAddrRGB = false;
        mcAddrRGBA = false;
        mcAddrHEX = false;
        mcAddrHEXA = false;
        if(eightbit){
            dataFMTSize = 7;
        }else if(sixteenbit){
            dataFMTSize = 11;
        }
    }
    if(sendData && programLoaded){
        resetThreads();
    }
}

//--------------------------------------------------------------
//MC,Addr, R,G,B Pressed
void ofApp::mcAddrRGBPressed(const void * sender, bool & pressed){
    if(mcAddrRGB){
        dataFMT = 2;
        allHex = false;
        allHexA = false;
        mcAddrRGBA = false;
        mcAddrHEX = false;
        mcAddrHEXA = false;
    }
    if(eightbit){
        dataFMTSize = 16;
    }else if(sixteenbit){
        dataFMTSize = 22;
    }
    if(sendData && programLoaded){
        resetThreads();
    }
}

//--------------------------------------------------------------
//MC, Addr, R,G,B,A Pressed
void  ofApp::mcAddrRGBAPressed(const void * sender, bool & pressed){
    if(mcAddrRGBA){
        dataFMT = 3;
        allHex = false;
        allHexA = false;
        mcAddrRGB = false;
        mcAddrHEX = false;
        mcAddrHEXA = false;
    }
    if(eightbit){
        dataFMTSize = 20;
    }else if(sixteenbit){
        dataFMTSize = 28;
    }
    if(sendData && programLoaded){
        resetThreads();
    }
}

//--------------------------------------------------------------
//MC,Addr,HEX Pressed
void  ofApp::mcAddrHEXPressed(const void * sender, bool & pressed){
    if(mcAddrHEX){
        dataFMT = 4;
        allHex = false;
        allHexA = false;
        mcAddrRGB = false;
        mcAddrRGBA = false;
        mcAddrHEXA = false;
    }
    if(eightbit){
        dataFMTSize = 11;
    }else if(sixteenbit){
        dataFMTSize = 17;
    }
    if(sendData && programLoaded){
        resetThreads();
    }
}

//--------------------------------------------------------------
//MC,Addr,HEX+Alpha Pressed
void  ofApp::mcAddrHEXAPressed(const void * sender, bool & pressed){
    if(mcAddrHEXA){
        dataFMT = 5;
        allHex = false;
        allHexA = false;
        mcAddrRGB = false;
        mcAddrRGBA = false;
        mcAddrHEX = false;
    }
    if(eightbit){
        dataFMTSize = 13;
    }else if(sixteenbit){
        dataFMTSize = 21;
    }
    if(sendData && programLoaded){
        resetThreads();
    }
}

//--------------------------------------------------------------
//8bit Pressed
void  ofApp::eightBitPressed(const void * sender, bool & pressed){
    if(eightbit){
        sixteenbit = false;
        bitDepth = 8;
    }
    if(sendData && programLoaded){
        resetThreads();
    }
}

//--------------------------------------------------------------
//16bit Pressed
void  ofApp::sixteenBitPressed(const void * sender, bool & pressed){
    if(sixteenbit){
        eightbit = false;
        bitDepth = 16;
    }
    if(sendData && programLoaded){
        resetThreads();
    }
}

//--------------------------------------------------------------
//sendData Pressed
void  ofApp::sendDataPressed(const void * sender, bool & pressed){
    if(sendData && programLoaded){
        resetThreads();
    }
}

//--------------------------------------------------------------
//Enable Random Debug Pressed
void ofApp::enableDebugRandomPressed(const void * sender, bool & pressed){
    if(toggleDebugRandom){
        //Setup Random and start thread
        debugRandom->width = fbow;
        debugRandom->height = fboh;
        debugRandom->mode = randomMode;
        debugRandom->refreshRate = randomRefreshRate;
        debugRandom->lowColor = randomLowColor;
        debugRandom->highColor = randomHighColor;
        debugRandom->start();
    }else{
        debugRandom->init = false;
        debugRandom->waitForThread();
        delete debugRandom;
        debugRandom = new PxRandom();
    }
    if(debugSolidColor){
        debugSolidColor = false;
    }
}

//--------------------------------------------------------------
//Random Mode Pressed
void  ofApp::updateRandomPressed(){
    debugRandom->mode = randomMode;
    debugRandom->refreshRate = randomRefreshRate;
    debugRandom->lowColor = randomLowColor;
    debugRandom->highColor = randomHighColor;
}


//--------------------------------------------------------------
//Debug Pressed
void ofApp::enableSolidDebugPressed(const void * sender, bool & pressed){
    if(debugRandom->isThreadRunning()){
        debugRandom->waitForThread();
        delete debugRandom;
        debugRandom = new PxRandom();
    }
    if(toggleDebugRandom){
        toggleDebugRandom = false;
    }
}

//--------------------------------------------------------------
//Define Luts Structures - Setup
void ofApp::setupLUTs(){
    //CubeLUT
    string LUTtype = "cube";
    string folder = "LUTs";
    dir.allowExt(LUTtype);
    dir.listDir(folder + "/");
    dir.sort();
    activeLUT.setMax(dir.size()-1);
    loadLUT();

    //MatrixLUT
    /*
         [[173.82384076650285, -157.5481382293615, -147.1330877568063],
         [0.5695641856053187, 0.35825908886207003, 0.34444718370119454],
         [-0.3550871528843065, 2.7939742344183736, 1.1414578390761465],
         [-0.48276323450098757, -0.4295950464434436, 1.2881288831631537]]
        */

    lutMat[0][0] = 173.82384076650285; //A1
    lutMat[0][1] = -157.5481382293615;  //B1
    lutMat[0][2] = -147.1330877568063; //C1

    lutMat[1][0] = 0.5695641856053187;//A2
    lutMat[1][1] = 0.35825908886207003;//B2
    lutMat[1][2] = 0.34444718370119454;//C2

    lutMat[2][0] = -0.3550871528843065;//A3
    lutMat[2][1] =  2.7939742344183736;//B3
    lutMat[2][2] = 1.1414578390761465;//C3

    lutMat[3][0] = -0.48276323450098757;//A4
    lutMat[3][1] = -0.4295950464434436;//B4
    lutMat[3][2] = 1.2881288831631537;//C4

}

//--------------------------------------------------------------
//Initialize LUT
void ofApp::loadLUT(){
    ofSleepMillis(500);
    //OpenGL Lut
    // Disable rectangle textures
    ofDisableArbTex();

    // Load the LUT
    vector<RGB> LUT;

    LUTpath = ofToDataPath(dir.getPath(activeLUT));
    ifstream LUTfile(LUTpath.c_str());

    while (!LUTfile.eof()) {
        string LUTline;
        getline(LUTfile, LUTline);

        if (LUTline.empty()) continue;

        RGB line;

        if (sscanf(LUTline.c_str(), "%f %f %f", &line.r, &line.g, &line.b) == 3) LUT.push_back(line);
    }

    //Figure out LUT Size
    if(LUT.size() == 262144){
        LUTsize = 64;
    }else if(LUT.size() == 32768){
        LUTsize = 32;
    }
    if (LUT.size() != unsigned((pow(LUTsize, 3.0f)))) ofLogError() << "LUT size is incorrect.";


    // Create a 3D texture
    // Reference from http://content.gpwiki.org/index.php/OpenGL:Tutorials:3D_Textures
    glEnable(GL_TEXTURE_3D);

    glGenTextures(1, &texture3D);
    glBindTexture(GL_TEXTURE_3D, texture3D);

    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);

    glTexImage3D(
                GL_TEXTURE_3D,
                0,
                GL_RGB,
                LUTsize,
                LUTsize,
                LUTsize,
                0,
                GL_RGB,
                GL_FLOAT,
                &LUT[0]);

    glBindTexture(GL_TEXTURE_3D, 0);
    glDisable(GL_TEXTURE_3D);

    plane.set(fbow,fboh,2,2);
    plane.setPosition(ofVec3f(fbow/2.0f,fboh/2.0f,0.0f));

    // Load the shader
    lutFilter.load("lut_filter");

    if(matLUT){
        currentLUT = "Experimental";
    }else{
        currentLUT = LUTpath.substr(10,LUTpath.length());
    }
    cubeStr = LUTpath.substr(10,LUTpath.length());

    setLUT = activeLUT;

    cout << "GL LUT Loaded -- " << "LUT Qty: " << dir.size()  << " | Current Selected LUT: " << currentLUT << endl;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 's'){
        GlobalNav.saveToFile("settings.xml");
        ColorMgmtGui.saveToFile("settings.xml");
        NetworkingGui.saveToFile("settings.xml");
        DebugGui.saveToFile("settings.xml");
    }
    if(key == 'l'){
        GlobalNav.loadFromFile("settings.xml");
        ColorMgmtGui.loadFromFile("settings.xml");
        NetworkingGui.loadFromFile("settings.xml");
        DebugGui.loadFromFile("settings.xml");
    }
    if(key == 'm'){
        random->mode = fmod(double(random->mode+1), double(3));
    }
    if(key == OF_KEY_RIGHT){
        if(slideshow->isInitiated()){
            slideshow->fadeAlpha = 255;
            slideshow->nextContent();
            if(totalShows > 0){
                if(slideshow->getNextCount() % showsCycle != 0){
                    loadContent();
                }
            }else{
                loadContent();
            }
        }
    }
    if(key == OF_KEY_LEFT){
        if(slideshow->isInitiated()){
            slideshow->fadeAlpha = 255;
            slideshow->previousContent();
            if(totalShows > 0){
                if(slideshow->getNextCount() % showsCycle != 0){
                    loadContent();
                }
            }else{
                loadContent();
            }
        }
    }
    //Pause Slideshow
    if(key == ' ' ){
        if(slideshow->isThreadRunning()){
            slideshow->waitForThread();
        }else{
            slideshow->start();
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    ofColor testC;
    testC = lastPx.getColor(x/4,y/4);

    cout << testC << endl;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    W = w;
    H = w*0.2808f;
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
