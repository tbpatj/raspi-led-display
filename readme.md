## Libraries

OpenCV4
https://github.com/opencv/opencv
I installed the library using the following command
`sudo apt-get update \n sudo apt-get install libopencv-dev`

LED Controller Library
https://github.com/jgarff/rpi_ws281x.git

JSON Library
https://github.com/nlohmann/json

HTTP Server Library
https://github.com/yhirose/cpp-httplib

## Compile Script

OpenCV4 installed on my machine kinda strangely, so I had to specify the path to the repository.
g++ displayLeds.cpp -o test `pkg-config --cflags --libs opencv4` -I/usr/local/include/ws2811 -lws2811

## Instructions to make the project start on device startup

On raspberry Pi we can utlize the already installed software.
Open up a terminal and type in the command
`sudo crontab -e`
If you haven't run this command before you will see a bunch of selections. I just selected the one that claims "easiest"
It will then open up a text editor with text to explain some things, if you scroll to the bottom you can write some scripts to get your file running.

Make sure the command moves the current directory into the directory that contains the project like `cd /asdf/asdf/asdf` and no shortcuts. Has to be the full path no ~/ or ./
