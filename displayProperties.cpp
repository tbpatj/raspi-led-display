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
}