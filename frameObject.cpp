class FrameObject {
    private:
        cv::VideoCapture cap;
        cv::Mat frame;
        int targetWidth;
        int targetHeight;
        int blurSize=23;
    public:
       void updateTargets(){
        targetHeight = static_cast<int>((static_cast<double>(targetWidth) / frame.cols) * frame.rows);
       }
       void setTargetWidth(int nWidth){
        targetWidth = nWidth;
       }
       int getTargetWidth(){
          return targetWidth;
       }
       int getTargetHeight(){
          return targetHeight;
       }
       void setFrame( cv::Mat nFrame){
        frame = nFrame;
       }
       cv::Mat getFrame(){
        return frame;
       }
       cv::Vec3b getColorAt(int x, int y){
            cv::Vec3b color = frame.at<cv::Vec3b>(cv::Point(x,y));
            cv::Vec3b c(color[2],color[1],color[0]);
            return c;
       }
       void updateFrame(){
        cap >> frame;
       }
       void show(){
        cv::imshow("Webcam",frame);
       }
       void downsampleFrame(int width, int height){
            cv::Size downsampledSize(width,height);
            cv::Mat downsampledFrame;
            cv::resize(frame,downsampledFrame,downsampledSize);
            frame = downsampledFrame;
       }
       void updateInputResToTarget(){
          cap.set(cv::CAP_PROP_FRAME_WIDTH, targetWidth);
          cap.set(cv::CAP_PROP_FRAME_HEIGHT, targetHeight);
       }
       void blurFrame(){
        cv:GaussianBlur(frame,frame,cv::Size(blurSize,blurSize),1);
       }
       FrameObject(int inWidth) : cap(-1){
            
            //resize the image to the new target width and height
            if(!cap.isOpened()){
                std::cerr << "Error: couldn't open the webcam." << std::endl;
	        }
            std::cout << "initalized cap object??" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            cap.set(cv::CAP_PROP_FPS, 30);
            updateFrame();
            std::this_thread::sleep_for(std::chrono::seconds(1));
            updateFrame();
            setTargetWidth(inWidth);
            updateTargets();
            updateInputResToTarget();
            
           
       }
};