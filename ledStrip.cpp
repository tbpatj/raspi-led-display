
class LEDStrip {
private:
    int led_count;
    int led_pin;
    ws2811_channel_t* channel;
    ws2811_t ledstring;

public:
    LEDStrip(int pin, int count) : led_count(count), led_pin(pin) {
        ledstring = {};
        ledstring.freq = WS2811_TARGET_FREQ;
        ledstring.dmanum = 10; // Choose a DMA channel

        channel = &ledstring.channel[0];
        channel->gpionum = led_pin;
        channel->count = led_count;
        channel->invert = 0;
        channel->brightness = 255;
        channel->strip_type = WS2811_STRIP_GRB; // Set the correct color order for WS2812B
    }

    void setColor(int index, int r, int g, int b){
        channel->leds[index] = (r << 16) | (g << 8) | (b);
    }

    void render(){
        ws2811_render(&ledstring);
    }

    bool init() {
        if (ws2811_init(&ledstring)) {
            std::cerr << "ws2811_init failed" << std::endl;
            return false;
        }
        return true;
    }

    void turnOff(int ledCount){
        for(int i = 0; i <= ledCount; ++i){
            setColor(i,0,0,0);
        }
    }

    void mapLEDs(FrameObject fo,DisplayProperties display) {
        int start = display.clockwise ? display.ledLeftStart : display.ledLeftEnd;
        int pos =  display.clockwise ? display.maxY - 1 : 0;
        int dir = display.clockwise ? -1 : 1;
        cv::Vec3b c;
        for(int i = 0; i <= display.leftL; ++i){
            int y = pos + display.leftDx * dir * i;
            c = fo.getColorAt(0,std::max(pos + display.leftDx * dir * i,0));
            setColor(i + start,c[0],c[1],c[2]);
        }
        start = display.clockwise ? display.ledRightStart : display.ledRightEnd;
        pos =  display.clockwise ? 0 : display.maxY - 1;
        dir = display.clockwise ? 1 : -1;
        for(int i = 0; i <= display.rightL; ++i){
            c = fo.getColorAt(display.maxX - 1,std::max(pos + display.rightDx * dir * i,0));
            setColor(i + start,c[0],c[1],c[2]);
        }
        start = display.clockwise ? display.ledBottomStart :display.ledBottomEnd;
        pos =  display.clockwise ? display.maxX - 1 : 0;
        dir = display.clockwise ? -1 : 1;
        for(int i = 0; i <= display.bottomL; ++i){
            c = fo.getColorAt(std::max(pos + display.bottomDx * dir * i,0),display.maxY - 1);
            setColor(i + start,c[0],c[1],c[2]);
        }
        start = display.clockwise ? display.ledTopStart :display.ledTopEnd;
        pos =  display.clockwise ? 0 : display.maxX - 1;
        dir = display.clockwise ? 1 : -1;
        for(int i = 0; i <= display.topL; ++i){
            c = fo.getColorAt(std::max(pos + display.rightDx * dir * i,0),0);
            setColor(i + start,c[0],c[1],c[2]);
        }
        render();
    }

    // Add any other methods or functionality as needed
};