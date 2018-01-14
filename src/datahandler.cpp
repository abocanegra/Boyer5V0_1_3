#include "datahandler.h"

class DataHandler::DataHandler()
{
    class MyThread : public ofThread {


        // the thread function
        void MyThread::threadedFunction() {

            // start

            while(isThreadRunning()) {

                cam.update();
                if(cam.isFrameNew()) {

                    // lock access to the resource
                    lock();

                    // load the image
                    image.setFromPixels(cam.getPixels());
                    // done with the resource
                    unlock();
                }
            }

            // done
        }

        ofVideoGrabber cam; // the cam
        ofImage image;      // the shared resource
    };
