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
#include "displayProperties.cpp"
#include "frameObject.cpp"
#include "ledStrip.cpp"
#include "fileManage.cpp"
#include "options.cpp"

using namespace std;
using json = nlohmann::json;
//compile script
//g++ displayLeds.cpp -o test `pkg-config --cflags --libs opencv4` -I/usr/local/include/ws2811 -lws2811

#define LED_PIN 18        // GPIO pin connected to the data input of the LED strip
Options options();

#include "server.cpp"

int main(){
    
    // You can add more routes for different paths
    std::thread serverThread(runServer);
    while(true){
        if(LED_STATUS){
            FrameObject fo(options.getResizeWidth());
            DisplayProperties display(fo.getFrame(),options.getLEDCount);
            display.printValues();
            int[4][2] ledPos = options.getLEDPos();
            display.initLEDPos(ledPos[0],ledPos[1],ledPos[2],ledPos[3]);

            LEDStrip led(LED_PIN,options.getLEDCount);
            if(!led.init()){
                return -1;
            }

            while(LED_STATUS){
                fo.updateFrame();
                fo.blurFrame();
                led.mapLEDs(fo,display);
                
                fo.show();
                if(cv::waitKey(30) >= 0){
                    break;
                }
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
