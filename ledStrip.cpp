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

    void setColor(int index, byte r, byte g, byte b){
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

    // Add any other methods or functionality as needed
};