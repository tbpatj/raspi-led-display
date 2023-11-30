#include <opencv2/opencv.hpp>
#include <cmath>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <ws2811.h>
#include <thread>
#include <mutex>
#include "../cpp-httplib/httplib.h"
#include "../json/single_include/nlohmann/json.hpp"
using json = nlohmann::json;
#include "displayProperties.cpp"
#include "frameObject.cpp"
#include "ledStrip.cpp"
#include "fileManage.cpp"
#include "options.cpp"

using namespace std;
//compile script
//g++ displayLeds.cpp -o test `pkg-config --cflags --libs opencv4` -I/usr/local/include/ws2811 -lws2811

#define LED_PIN 18        // GPIO pin connected to the data input of the LED strip
MyOptions options;

#include "server.cpp"

int main(){
    // You can add more routes for different paths
    std::thread serverThread(runServer);
    options.save();
    while(true){
        if(options.getLEDStatus()){
            try{
                FrameObject fo(options.getResizeWidth());
                fo.downsampleFrame(fo.getTargetWidth(),fo.getTargetHeight());
                DisplayProperties display(fo.getFrame(),options.getLEDCount());
                display.printValues();
                display.initLEDPos(options.LED_POS[0],options.LED_POS[1],options.LED_POS[2],options.LED_POS[3]);

                LEDStrip led(LED_PIN,options.getLEDCount());
                if(!led.init()){
                    return -1;
                }

                while(options.getLEDStatus()){
                    fo.updateFrame();
                    fo.downsampleFrame(fo.getTargetWidth(),fo.getTargetHeight());
                    fo.blurFrame();
                    led.mapLEDs(fo,display);
                    
                    fo.show();
                    if(cv::waitKey(30) >= 0){
                        break;
                    }
                }
                led.turnOff();
            }catch(const cv::Exception& e){
                std::cerr << "Error creating video object: " << std::endl;
                options.setLEDStatus(false);
            }
        }
        if(cv::waitKey(30) >= 0){
			break;
	    }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    serverThread.join();
    
    std::cout << "end of script" << std::endl;
    return 0;
}

// int main(){

    

	
// }
