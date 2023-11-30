class DisplayProperties {
    public:
        int maxX;
        int maxY;
       
        //Mapping properties
        int ledRightStart;
        int ledRightEnd;
        int rightL;
        int rightDx;

        int ledLeftStart;
        int ledLeftEnd;
        int leftL;
        int leftDx;

        int ledTopStart;
        int ledTopEnd;
        int topL;
        int topDx;

        int ledBottomStart;
        int ledBottomEnd;
        int bottomL;
        int bottomDx;

        bool clockwise;
        
        DisplayProperties(cv::Mat frame, int LED_COUNT){
            maxX = frame.cols;
            maxY = frame.rows;
           
        }
        void printValues(){
             std::cout << "image width: " << maxX << std::endl;
            std::cout << "image height: " << maxY << std::endl;
        }
        void initLEDPos (int right[2], int left[2],int top[2], int bottom[2]){
            ledRightStart = right[0];
            ledRightEnd = right[1];
            rightL = abs(ledRightEnd - ledRightStart);
            rightDx = maxY / rightL;

            ledLeftStart = left[0];
            ledLeftEnd = left[1];
            leftL = abs(ledLeftEnd - ledLeftStart);
            leftDx = maxY / leftL;

            ledTopStart = top[0];
            ledTopEnd = top[1];
            topL = abs(ledTopEnd - ledTopStart);
            topDx = maxX / topL;

            ledBottomStart = bottom[0];
            ledBottomEnd = bottom[1];
            bottomL = abs(ledBottomEnd - ledBottomStart);
            bottomDx = maxX / bottomL;

            if(ledTopEnd < ledRightStart){
                clockwise = true;
            } else {
                clockwise = false;
            }

        }
};