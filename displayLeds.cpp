#include <opencv2/opencv.hpp>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <ws2811.h>
#include "displayProperties.cpp"
#include "frameObject.cpp"
#include "ledStrip.cpp"
using namespace std;
//compile script
//g++ displayLeds.cpp -o test `pkg-config --cflags --libs opencv4` -I/usr/local/include/ws2811 -lws2811

#define LED_COUNT 47      // Number of LEDs in the strip
#define LED_PIN 18         // GPIO pin connected to the data input of the LED strip
#define LED_POS {{0,14},{15,23},{24,37},{38,46}}

int main(){
    FrameObject fo(100);
    fo.downsampleFrame();
    DisplayProperties display(fo.getFrame(),LED_COUNT);
    display.printValues();
    display.initLEDPos(LED_POS[0],LED_POS[1],LED_POS[2],LED_POS[3]);

    LEDStrip led(LED_PIN,LED_COUNT);
    if(!led.init()){
        return -1;
    }

    led.setColor(display.rowXPixels,255,0,0);
    led.setColor(20,0,255,0);
    led.setColor(30,0,0,255);
    led.render();
    while(true){
        fo.updateFrame();
        fo.downsampleFrame();
        for(int i = display.ledLeftStart; i <= display.leftL; ++i){
            led.setColor(i,0,255,0);
        }
        for(int i = display.ledRightStart; i <= display.rightL; ++i){
            led.setColor(i,0,255,0);
        }
        for(int i = display.ledBottomStart; i <= display.bottomL; ++i){
            led.setColor(i,255,0,0);
        }
        for(int i = display.ledTopStart; i <= display.topL; ++i){
            led.setColor(i,255,0,0);
        }
        if(cv::waitKey(30) >= 0){
			break;
	    }
    }
    
	return 0;

	
}
