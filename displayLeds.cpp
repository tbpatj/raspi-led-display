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
int LED_POS[4][2] = {{38,46},{15,23},{24,37},{0,14}};

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
    led.setColor(5,0,255,0);
    led.setColor(10,0,0,255);
    led.render();
    while(true){
        fo.updateFrame();
        fo.downsampleFrame();
        int start = display.clockwise ? display.ledLeftStart : display.ledLeftEnd;
        int pos =  display.clockwise ? display.maxY : 0;
        int dir = display.clockwise ? -1 : 1;
        cv::Vec3b c;
        c = fo.getColorAt(0,pos + display.leftDx * dir * 0);
        std::cout << "start: " << start << " pos: " << pos << " dir: " << dir << " clockwise: " << display.clockwise << std::endl;
        std::cout << "r: " << c[0] << " g: " << c[1] << " b: " << c[2] << std::endl;
        for(int i = 0; i <= display.leftL; ++i){
            c = fo.getColorAt(0,pos + display.leftDx * dir * i);
            led.setColor(i + start,c[0],c[1],c[2]);
        }
        start = display.clockwise ? display.ledRightStart : display.ledRightEnd;
        pos =  display.clockwise ? 0 : display.maxY;
        dir = display.clockwise ? 1 : -1;
        for(int i = 0; i <= display.rightL; ++i){
            c = fo.getColorAt(display.maxX,pos + display.rightDx * dir * i);
            led.setColor(i + start,c[0],c[1],c[2]);
        }
        start = display.clockwise ? display.ledBottomStart :display.ledBottomEnd;
        pos =  display.clockwise ? display.maxX : 0;
        dir = display.clockwise ? -1 : 1;
        for(int i = 0; i <= display.bottomL; ++i){
            c = fo.getColorAt(pos + display.bottomDx * dir * i,display.maxY);
            led.setColor(i + start,c[0],c[1],c[2]);
        }
        start = display.clockwise ? display.ledTopStart :display.ledTopEnd;
        pos =  display.clockwise ? 0 : display.maxX;
        dir = display.clockwise ? 1 : -1;
        for(int i = 0; i <= display.topL; ++i){
            c = fo.getColorAt(pos + display.rightDx * dir * i,0);
            led.setColor(i + start,c[0],c[1],c[2]);
        }
        led.render();
        fo.show();
        sleep(1);
        if(cv::waitKey(30) >= 0){
			break;
	    }
    }
    
	return 0;

	
}
