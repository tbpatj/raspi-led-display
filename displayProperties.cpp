class DisplayProperties {
    public:
        int maxX;
        int maxY;
        double aspectRatio;
        int xPixels;
        int yPixels;
        int rowXPixels;
        int rowYPixels;
        int dx;
        int dy;
        int ledRightStart;
        int ledRightEnd;
        int ledLeftStart;
        int ledLeftEnd;
        int ledTopStart;
        int ledTopEnd;
        int ledBottomStart;
        int ledBottomEnd;
        int rightL;
        int leftL;
        int topL;
        int bottomL;
        DisplayProperties(cv::Mat frame, int LED_COUNT){
            maxX = frame.cols;
            maxY = frame.rows + 10;
            aspectRatio = static_cast<double>(maxX) / static_cast<double>(maxY);
            xPixels = static_cast<int>(round(static_cast<double>(LED_COUNT) / aspectRatio));
            yPixels = LED_COUNT - xPixels;
            rowXPixels = xPixels / 2;
            rowYPixels = yPixels / 2;
            dx = maxX / (rowXPixels);
            dy = maxY / (rowYPixels);
        }
        void printValues(){
             std::cout << "image width: " << maxX << std::endl;
            std::cout << "image height: " << maxY << std::endl;
            std::cout << "aspect ratio: " << aspectRatio << "\n" << std::endl;
            
            std::cout << "xPixels: " << xPixels << std::endl;
            std::cout << "yPixels: " << yPixels << "\n" << std::endl;
            
            std::cout << "rowXPixels: " << rowXPixels << "\nrowYPixels: " << rowYPixels << "\n" << std::endl;
            
            std::cout << "dx: " << dx << std::endl;
            std::cout << "dy: " << dy << std::endl;
        }
        void initLEDPos (int right[2], int left[2],int top[2], int bottom[2]){
            ledRightStart = right[0];
            ledRightEnd = right[1];
            rightL = ledRightEnd - ledRightStart;

            ledLeftStart = left[0];
            ledLeftEnd = left[1];
            leftL = ledLeftEnd - ledLeftStart;

            ledTopStart = top[0];
            ledTopEnd = top[1];
            topL = ledTopEnd - ledTopStart;

            ledBottomStart = bottom[0];
            ledBottomEnd = bottom[1];
            bottomL = ledBottomEnd - ledBottomStart;

        }
};