#pragma once
#include "ofThread.h"
#include "ofMain.h"
#include <time.h>
#include "ofxPixelsExtended.h"

//Requires ofxPixelsExtendeds
/*
* Creates either random colored pixels, full screen random colors, or rainbow like hue transition strips.
* Creative Commons Attribution-ShareAlike 4.0 International License
* Originally developed by Aaron Bocanegra @ Nontrivial Studio
* 2016
*/
class PxRandom: public ofThread{
public:
    PxRandom()
    {
        width = 324;
        height = 91;
        mode = 0;//random pixels-0,random full color -1, rainbow - 2
        init = false;
        refreshRate = 100;
        lowColor = 0.0f;
        highColor = 255.0f;
        clearRandom = false;
    }

    /// Start the thread.
    void start()
    {
        // Mutex blocking is set to true by default
        // It is rare that one would want to use startThread(false).
        startThread();
        if(this->mode == 3){
            ofEnableBlendMode(ofBlendMode(blendSet[(int)ofRandom(0,4)]));
        }else{
            ofEnableBlendMode(OF_BLENDMODE_ALPHA);
        }
    }

    /// Signal the thread to stop.  After calling this method,
    /// isThreadRunning() will return false and the while loop will stop
    /// next time it has the chance to.
    void stop()
    {
        stopThread();
        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    }

    void setup(){
        ofEnableSmoothing();
        this->rand.allocate(this->width, this->height, OF_PIXELS_RGBA);
        this->randImg.setUseTexture(false);
        this->randImg.allocate(this->width, this->height, OF_IMAGE_COLOR_ALPHA);
        this->init = true;
        this->restartTimer();
        cout << "SETUP Random" << endl;
    }


    /// Our implementation of threadedFunction.
    void threadedFunction()
    {
        while(isThreadRunning())
        {
            // Attempt to lock the mutex.  If blocking is turned on,
            if(lock())
            {
                if(!this->init){
                    setup();
                }
                this->currentTime = ofGetElapsedTimeMillis();
                unlock();
                yield();
            }
            else
            {
                // ofLogWarning("threadedFunction()") << "PXRandom: Unable to lock mutex.";
            }
        }
    }

    void updatePx(){
        //Random Each Pixel
        this->startTime= ofGetElapsedTimeMillis();
        if(this->mode == 0){
            for (int i=0; i<this->rand.getTotalBytes(); i++){
                ofColor randColor(
                            ofRandom( lowColor, highColor),
                            ofRandom( lowColor, highColor ),
                            ofRandom( lowColor, highColor ),
                            255.0f
                            );
                //randColor.setHueAngle(fmod(double(ofGetSystemTimeMicros()),double(360)));
                this->rand.setColor(i,randColor);
            }
            //Random Full Screen
        }else if(this->mode == 1){
            ofColor randColor(
                        ofRandom( lowColor, highColor ),
                        ofRandom( lowColor, highColor ),
                        ofRandom( lowColor, highColor ),
                        255.0f);
            this->rand.setColor(randColor);
            //Random Strips
        }else if(this->mode == 2){
            for (int i=0; i<this->width; i+=3){
                for(int j = 0; j< this->height; j++){
                    ofColor randColor(255, 0, 0,255);
                    randColor.setHueAngle(fmod(double(ofGetSystemTimeMicros()),double(360)));
                    this->rand.setColor(i,j,randColor);
                    this->rand.setColor(i+1,j,randColor);
                    this->rand.setColor(i+2,j,randColor);
                }
            }
        }
    }

    /// This drawing function cannot be called from the thread itself because
    /// it includes OpenGL calls (ofDrawBitmapString).
    void draw()
    {
        if(lock()){
            if(this->timeDiff() >= this->refreshRate && this->mode == 3){
                this->randomCircles();
            }
            if(this->timeDiff() >= this->refreshRate && this->mode !=3 ){
                updatePx();
            }
            unlock();
        }else{
            //ofLogWarning("threadedFunction()") << "PXRandom: Unable to lock mutex. ";
        }
        this->randImg.setUseTexture(true);

        if(this->mode != 3){
            if(this->rand.isNewFrame()){
                this->randImg.setFromPixels(this->rand);
                this->randImg.update();
            }//else{
               // throw Poco::ApplicationException("Exception: Frame not Updated!");
            //}
            if(this->randImg.isAllocated()){
                this->randImg.draw(0,0);
            }
            this->randImg.setUseTexture(false);
        }
    }

    void cleanup(){
        try{
            this->randImg.clear();
            if(this->randImg.isAllocated()){
                this->randImg.setFromPixels(this->rand);
                this->clearRandom = false;
            }
            this->clearRandom = false;
            this->restartTimer();
        }catch(exception &e) {
            ofLogError("threadedFunction()") << "Slideshow Cleanup EXCEPTION: " << e.what();
        }
    }

    void randomCircles(){
        ofSetCircleResolution(64);
        this->startTime= ofGetElapsedTimeMillis();
        int circleQty = ofRandom(this->width/30, this->width/5);
        for(int i = 0; i< circleQty; i++){
            ofSetColor(
                        ofColor(
                            ofRandom( lowColor, highColor),
                            ofRandom( lowColor, highColor ),
                            ofRandom( lowColor, highColor ),
                            ofRandom( lowColor,highColor)
                            )
                        );
            ofFill();
            ofDrawCircle(ofPoint(ofRandom(0,this->width),ofRandom(0,this->height),0),ofRandom(2,this->width/PI));
            ofEnableBlendMode(OF_BLENDMODE_ALPHA);
        }
    }

    ofImage getImg(){
        return this->randImg;
    }

    ofxPixelsExtended rand;
    ofxPixelsExtended lastPx;
    int width;
    int height;
    bool init;
    ofImage randImg;
    int mode;
    int refreshRate;
    float lowColor;
    float highColor;
    bool clearRandom;
    int blendSet[5] = {1,2,4,5,6};
protected:
    uint64_t startTime;
    uint64_t currentTime;
    //Return Time Left
    uint64_t timeDiff(){
        return (this->currentTime - this->startTime);
    }
    void restartTimer(){
        this->startTime = ofGetElapsedTimeMillis();
        this->currentTime = ofGetElapsedTimeMillis();
    }
};
