Compile Script
g++ displayLeds.cpp -o test `pkg-config --cflags --libs opencv4` -I/usr/local/include/ws2811 -lws2811
