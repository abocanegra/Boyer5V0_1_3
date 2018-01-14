#pragma once
#include "ofThread.h"
#include "ofMain.h"
#include "ofxNetwork.h"

/// This is a simple example of a ThreadedObject created by extending ofThread.
/// It contains data (count) that will be accessed from within and outside the
/// thread and demonstrates several of the data protection mechanisms (aka
/// mutexes).
class DataHandler: public ofThread
{
public:
    /// Create a ThreadedObject and initialize the member
    /// variable in an initialization list.
    DataHandler()
    {
        MC = 1;
        ipAddr = "";
        dataPort = 10001;
        configPort = 10002;
        protocolMode = 1;//0 = TCP, 1 = UDP
        bitDepth = 8; //8 or 16
        dataFMTSize = 5;
        dataFMT = 0; // 0-> 5
        init = false;
        powerLevel = 1;
        sendData = false;
        pxWidth = 324;
        pxHeight = 91;
        delimiter = "\n";
        serverAddr = "10.16.34.38";
        config = true;
    }

    /// Start the thread.
    void start()
    {

        startThread();
    }

    /// Signal the thread to stop.  After calling this method,
    /// isThreadRunning() will return false and the while loop will stop
    /// next time it has the chance to.
    void stop()
    {
        stopThread();
    }



    /// Our implementation of threadedFunction.
    void threadedFunction()
    {
        while(isThreadRunning())
        {
            // Attempt to lock the mutex.  If blocking is turned on,
            if(lock())
            {
                if(!this->init || !this->isConnected){
                    this->setup();
                }
                if(this->isConnected){
                    if(this->isNewFrame){
                        this->formatData();
                    }
                }
                // Unlock the mutex.  This is only
                // called if lock() returned true above.
                unlock();

                // Sleep
                if(this->isConnected){
                    if(this->protocolMode == 1){
                        //sleep(1);
                        this->yield();
                    }
                }else{
                    sleep(60*1000);
                }
            }
            else
            {
                // If we reach this else statement, it means that we could not
                // lock our mutex, and so we do not need to call unlock().
                // Calling unlock without locking will lead to problems.
                ofLogWarning("threadedFunction()") << "Unable to lock mutex.";
            }
        }
    }



    /// This drawing function cannot be called from the thread itself because
    /// it includes OpenGL calls (ofDrawBitmapString).
    void draw()
    {

        if(lock())
        {
            // The mutex is now locked and the "count"
            // variable is protected.  Time to read it.
            // Unlock the mutex.  This is only
            // called if lock() returned true above.
            unlock();
        }
        else
        {
            // If we reach this else statement, it means that we could not
            // lock our mutex, and so we do not need to call unlock().
            // Calling unlock without locking will lead to problems.
            ofLogWarning("threadedFunction()") << "Unable to lock mutex.";
        }

    }

    bool setup(){
        if(this->ipAddr != ""){
            this->isConnected = ping();
        }else{
            this->isConnected = false;
        }

        if(this->isConnected){
            cout << "Setup |  PI: "<< this->MC
                 << ", Protocol: " << this->protocolMode
                 << " | IP: " << this->ipAddr
                 << ":" << this->dataPort
                 << ", Data Format/Chunk: " << this->dataFMT << "/"<< this->dataFMTSize
                 << ", bitDepth: " << this->bitDepth
                 << ", powerLevel: " << this->powerLevel
                 << ", Send Data: " << this->sendData
                 << " END Setup "
                 << endl;
            //Network Setup
            //UDP Data
            if(this->bitDepth == 8){
                this->px.allocate(this->pxWidth,this->pxHeight,GL_RGBA);
            }else if (this->bitDepth == 16){
                this->px.allocate(this->pxWidth,this->pxHeight, GL_RGB16);
            }
            if(this->config){
                this->sendConfiguration();
            }
            UDPData.Create();
            UDPData.Connect(this->ipAddr.c_str(),this->dataPort);
            UDPData.SetNonBlocking(true);
            //TCP Config
            TCPConfig.setup(this->ipAddr,this->configPort);
            TCPConfig.setMessageDelimiter(this->delimiter);

            this->init = true;
            return true;
        }else{
            return false;
        }
    }

    bool ping(){
        string pingStr = (string)"ping -c 1 -t 1 " + this->ipAddr  + " > /dev/null";
        bool bServerConnected;
        int flag = system( pingStr.c_str());

        if(flag == 0){
            bServerConnected = true;
            cout << "Connected: " << this->ipAddr << endl;
        }else{
            bServerConnected = false;
            //   cout<<ofGetTimestampString()<<endl;
            // cout<<"cloud not connect to timing server at IP "<< this->ipAddr <<endl;
        }
        return bServerConnected;
    }

    void formatData(){
        uint64_t buffNum;
        uint msgSizeBytes = 910 * dataFMTSize +1 ;
        char chrMessage[msgSizeBytes];
        //Microcontroller
        txMessage = "";
        //Hex only
        buffNum = 0;

        if(this->dataFMT > 1){
            char mcNum[3];
            sprintf(mcNum, "%d:", this->MC);
            txMessage += mcNum;
        }
        bool zeroCoord = false;
        //Address
        for(unsigned int j = 0; j < sizeof(structure[this->MC])/sizeof(structure[this->MC][0]); j++ ){//sizeof(structure[i])/sizeof(structure[i][0])
            //Set Format Size in relation to bitdepth and data format
            char tcpData[dataFMTSize];

            //Skip Empty Positions
            if(this->dataFMT > 1){
                if(structure[this->MC][j][0] == 0 && structure[this->MC][j][1] == 0 && zeroCoord == false){
                    zeroCoord = true;
                }else if(structure[this->MC][j][0] == 0 && structure[this->MC][j][1] == 0 && zeroCoord){
                    continue;
                }
            }
            if(this->bitDepth == 8){
                //Setup Color Information
                ofColor cT;
                cT = this->px.getColor(
                            structure[this->MC][j][0],
                        structure[this->MC][j][1]
                        );
                //Correct for Clipping
                if(this->clipping>0){
                    structure[this->MC][j][2] = int(round(ofMap(cT.r,0,255,clipping,255)));  //red
                    structure[this->MC][j][3] = int(round(ofMap(cT.g,0,255,clipping,255))); //green
                    structure[this->MC][j][4] = int(round(ofMap(cT.b,0,255,clipping,255))); //blue
                    structure[this->MC][j][5] = cT.a; //alpha
                }else{
                    structure[this->MC][j][2] =cT.r;   //red
                    structure[this->MC][j][3] = cT.g; //green
                    structure[this->MC][j][4] = cT.b; //blue
                    structure[this->MC][j][5] = cT.a; //alpha
                }
                //Prepare Data
                if(this->dataFMT == 0){
                    //Hex (5 Bytes)
                    chrMessage[buffNum] = ((j >> 8) & 0xff);
                    buffNum++;
                    chrMessage[buffNum] = (j & 0xff);
                    buffNum++;
                    chrMessage[buffNum] = (structure[this->MC][j][2] & 0xff);
                    buffNum++;
                    chrMessage[buffNum] = (structure[this->MC][j][3] & 0xff);
                    buffNum++;
                    chrMessage[buffNum] = (structure[this->MC][j][4] & 0xff);
                    buffNum++;
                }else if(this->dataFMT == 1){
                    //HEX+Alpha (6 Bytes)
                    chrMessage[buffNum] = ((j >> 8) & 0xff);
                    buffNum++;
                    chrMessage[buffNum] = (j & 0xff);
                    buffNum++;
                    chrMessage[buffNum] = (structure[this->MC][j][2] & 0xff);
                    buffNum++;
                    chrMessage[buffNum] = (structure[this->MC][j][3] & 0xff);
                    buffNum++;
                    chrMessage[buffNum] = (structure[this->MC][j][4] & 0xff);
                    buffNum++;
                    chrMessage[buffNum] = (structure[this->MC][j][5] & 0xff);
                    buffNum++;
                }if(this->dataFMT == 2){
                    //Message Format: Address,R,G,B;
                    sprintf(tcpData, "%d,%d,%d,%d;",
                            j,
                            structure[this->MC][j][2],
                            structure[this->MC][j][3],
                            structure[this->MC][j][4]
                            );
                    txMessage += tcpData;
                }else if(this->dataFMT == 3){
                    //Message Format: Address,R,G,B,A;
                    sprintf(tcpData, "%d,%d,%d,%d,%d;",
                            j,
                            structure[this->MC][j][2],
                            structure[this->MC][j][3],
                            structure[this->MC][j][4],
                            structure[this->MC][j][5]
                            );
                    txMessage += tcpData;
                }else if(this->dataFMT == 4){
                    //Message Format: Address,HEX;
                    sprintf(tcpData, "%d,%02X%02X%02X;",
                            j,
                            structure[this->MC][j][2],
                            structure[this->MC][j][3],
                            structure[this->MC][j][4]
                            );
                    txMessage += tcpData;
                }else if(this->dataFMT == 5){
                    //Message Format: Address,HEXA;
                    sprintf(tcpData, "%d,%02X%02X%02X%02X;",
                            j,
                            structure[this->MC][j][2],
                            structure[this->MC][j][3],
                            structure[this->MC][j][4],
                            structure[this->MC][j][5]
                            );
                    txMessage += tcpData;
                }
            }else if (this->bitDepth == 16){

            }
        }
        if(this->dataFMT > 1){
            txMessage += ":";
        }
        if(this->dataFMT<=1){
            sendDataBytes(chrMessage, sizeof(chrMessage));
        }else{
            sendDataProtocol(txMessage);
        }
    }

    //Send Byte Data
    void sendConfiguration(){
        /*
         * Network_Protocol(0-tcp/1-udp),
         * Source(ip),
         * Bit_Depth(8/16),
         * Data_Format (0-6 or whatever),
         * Power(float)
         */
        string configure;
        //configure = ofToString(this->protocolMode) + ",";
        //configure += ofToString(this->serverAddr) + "," ;
        //configure += ofToString(this->bitDepth) + ",";
        //configure += ofToString(this->dataFMT) + "," ;
        configure = ofToString(this->powerLevel);
        this->TCPConfig.setup(this->ipAddr,this->configPort);
        this->TCPConfig.sendRaw(configure);
        cout << "CONFIGURE: " << configure << endl;
        this->TCPConfig.close();
        this->config = false;
        sleep(4);
        /*
            while (true){
                string rxMsg;
                rxMsg = this->TCPConfig.receiveRaw();
                if(rxMsg.length() > 0){
                    cout << "RECEIVED: " << rxMsg << endl;
                    this->init = true;
                    this->sendData = true;
                    break;
                }
            }
            */
    }

    //--------------------------------------------------------------
    //Send Byte Data
    void sendDataBytes(char message[], int size){
        if(this->sendData && this->init){
            if(this->protocolMode == 0){
                if(!this->TCPData.isConnected()){
                    this->TCPData.setup(this->ipAddr,this->dataPort);
                    this->TCPData.sendRawBytes(message, size);
                    this->TCPData.close();
                }
            }else if(this->protocolMode == 1){
                this->UDPData.Send(message, size);
            }
        }
    }

    //--------------------------------------------------------------
    //Send String Data
    void sendDataProtocol( string message ){
        if(this->sendData && this->init){
            if(this->protocolMode == 1){
                this->UDPData.Send(message.c_str(), message.length());
            }else if(this->protocolMode == 0){
                if(!this->TCPData.isConnected()){
                    this->TCPData.setup(this->ipAddr,this->dataPort);
                    this->TCPData.sendRaw(message);
                    //cout << message.substr( 0,12 ) << " | " << message.substr(message.length()-12)<< endl;
                    this->TCPData.close();
                }else{
                    this->TCPData.close();
                }
            }
        }
    }

    int MC;
    string ipAddr;
    int dataPort;
    int configPort;
    int bitDepth;
    float powerLevel;
    int dataFMTSize;
    int dataFMT;
    int protocolMode;
    ofPixels px;
    bool sendData;
    bool isConnected;
    bool init;
    int pxWidth;
    int pxHeight;
    unsigned int structure[34][910][6];
    string delimiter;
    string serverAddr;
    int clipping;
    bool isNewFrame;
    bool config;
protected:
    // A flag to check and see if we should throw a test exception.
    Poco::AtomicCounter shouldThrowTestException;

    // This is a simple variable that we aim to always access from both the
    // main thread AND this threaded object.  Therefore, we need to protect it
    // with the mutex.  In the case of simple numerical variables, some
    // garuntee thread safety for small integral types, but for the sake of
    // illustration, we use an int.  This int could represent ANY complex data
    // type that needs to be protected.
    //
    // Note, if we simply want to count in a thread-safe manner without worrying
    // about mutexes, we might use Poco::AtomicCounter instead.
    ofxUDPManager UDPData;
    ofxTCPClient  TCPConfig;
    ofxTCPClient  TCPData;
    string txMessage;
};
