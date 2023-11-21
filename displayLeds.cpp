#include <opencv2/opencv.hpp>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <ws2811.h>
using namespace std;
//compile script
//g++ displayLeds.cpp -o test `pkg-config --cflags --libs opencv4` -I/usr/local/include/ws2811 -lws2811

#define LED_COUNT 47      // Number of LEDs in the strip
#define LED_PIN 18         // GPIO pin connected to the data input of the LED strip


int main(){

    //Initialize Webcam scripts
	cv::VideoCapture cap(0);
	
	if(!cap.isOpened()){
			std::cerr << "Error: couldn't open the webcam." << std::endl;
			return -1;
	}
	cv::Mat frame;
	int targetWidth = 100;
	
	//Initialize LED strip
	ws2811_t ledstring = {};
    ledstring.freq = WS2811_TARGET_FREQ;
    ledstring.dmanum = 10; // Choose a DMA channel

    ws2811_channel_t& channel = ledstring.channel[0];
    channel.gpionum = LED_PIN;
    channel.count = LED_COUNT;
    channel.invert = 0;
    channel.brightness = 255;
    channel.strip_type = WS2811_STRIP_GRB;  // Set the correct color order for WS2812B

    if (ws2811_init(&ledstring)) {
        std::cerr << "ws2811_init failed" << std::endl;
        return -1;
    }
    //Initialize Frame variables
    cap >> frame;
    
    int targetHeight = static_cast<int>((static_cast<double>(targetWidth) / frame.cols) * frame.rows);
    
     cv::Size downsampledSize(targetWidth,targetHeight);
            cv::Mat downsampledFrame;
            cv::resize(frame,downsampledFrame,downsampledSize);
    
    int maxX = downsampledFrame.cols;
    int maxY = downsampledFrame.rows + 10;
    double aspectRatio = static_cast<double>(maxX) / static_cast<double>(maxY);
    int xPixels = static_cast<int>(round(static_cast<double>(LED_COUNT) / aspectRatio));
    int yPixels = LED_COUNT - xPixels;
    int rowXPixels = xPixels / 2;
    int rowYPixels = yPixels / 2;
    int dx = maxX / (rowXPixels);
    int dy = maxY / (rowYPixels);
    
    std::cout << "image width: " << maxX << std::endl;
    std::cout << "image height: " << maxY << std::endl;
    std::cout << "aspect ratio: " << aspectRatio << "\n" << std::endl;
    
    std::cout << "xPixels: " << xPixels << std::endl;
    std::cout << "yPixels: " << yPixels << "\n" << std::endl;
    
    std::cout << "rowXPixels: " << rowXPixels << "\nrowYPixels: " << rowYPixels << "\n" << std::endl;
    
    std::cout << "dx: " << dx << std::endl;
    std::cout << "dy: " << dy << std::endl;
    
    void setStripColor(int i, int x, int y) {
     cv::Vec3b color = downsampledFrame.at<cv::Vec3b>(x,y);
      channel.leds[i] = (color[0] << 16) | (color[1] << 8) | (color[2]); // GRB color order: Green, Red, Blue
    };
	//Loop through the frames given to us and update the strip accordingly
	while(true){
		cap >> frame;
		if(frame.cols > 0 && frame.rows > 0){
            
            cv::resize(frame,downsampledFrame,downsampledSize);
            
            int blurSize = 5;
            cv:GaussianBlur(downsampledFrame,downsampledFrame,cv::Size(blurSize,blurSize),1);

          
             
            //assign the top of the led strip
            for (int i = 0; i < rowXPixels - 1; ++i) {
                setStripColor(i, maxX - dx * i,maxY);
            }
            
            channel.leds[0] = (255 << 16) | (0 << 8) | (0);
            for(int i = 0; i < rowYPixels - 1; ++i){
                setStripColor(i + rowXPixels - 1, 0,maxY - i * dy);
            }
            
            channel.leds[rowXPixels - 1] = (255 << 16) | (0 << 8) | (0);
            
            for(int i = 0; i < rowXPixels - 1; ++i){
                 setStripColor(i + rowXPixels - 1 + rowYPixels - 1,dx * i, 0);
            }
            
            channel.leds[rowXPixels - 1 + rowYPixels - 1] = (255 << 16) | (0 << 8) | (0);
            
            ws2811_render(&ledstring);
            
            cv::imshow("Webcam",downsampledFrame);
		}
		if(cv::waitKey(30) >= 0){
			break;
		}
		
	}
	return 0;
	
}
