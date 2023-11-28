#include <opencv2/opencv.hpp>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <ws2811.h>
#include <thread>
#include <mutex>
#include "displayProperties.cpp"
#include "frameObject.cpp"
#include "ledStrip.cpp"
#include "server.cpp"
#include "../cpp-httplib/httplib.h"
using namespace std;
//compile script
//g++ displayLeds.cpp -o test `pkg-config --cflags --libs opencv4` -I/usr/local/include/ws2811 -lws2811

#define LED_COUNT 47      // Number of LEDs in the strip
#define LED_PIN 18         // GPIO pin connected to the data input of the LED strip
int LED_POS[4][2] = {{38,47},{15,23},{24,37},{0,14}};

int main(){
    
    // You can add more routes for different paths
    std::thread serverThread(runServer);
    FrameObject fo(100);
    //make sure to downsample the frame so we are able to blur faster and not working with massive image
    fo.downsampleFrame();
    DisplayProperties display(fo.getFrame(),LED_COUNT);
    display.printValues();
    display.initLEDPos(LED_POS[0],LED_POS[1],LED_POS[2],LED_POS[3]);

    LEDStrip led(LED_PIN,LED_COUNT);
    if(!led.init()){
        return -1;
    }

    led.setColor(display.rowXPixels,255,0,0);
    led.setColor(5,0,255,0);
    led.setColor(10,0,0,255);
    led.render();
    while(true){
        fo.updateFrame();
        fo.downsampleFrame();
        fo.blurFrame();
        led.mapLEDs(fo,display);
        
        // fo.show();
        if(cv::waitKey(30) >= 0){
			break;
	    }
    }

    serverThread.join();
    
    std::cout << "end of script" << std::endl;
    return 0;
}

// int main(){

    

	
// }
