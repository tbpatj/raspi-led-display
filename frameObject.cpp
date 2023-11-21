class FrameObject {
    private:
        cv::VideoCapture cap;
        cv::Mat frame;
        int targetWidth;
        int targetHeight;
    public:
       void updateTargets(){
        targetHeight = static_cast<int>((static_cast<double>(targetWidth) / frame.cols) * frame.rows);
       }
       void setFrame( cv::Mat nFrame){
        frame = nFrame;
       }
       cv::Mat getFrame(){
        return frame;
       }
       void updateFrame(){
        cap >> frame;
       }
       void show(){
        cv::imshow("Webcam",frame);
       }
       void downsampleFrame(){
            cv::Size downsampledSize(targetWidth,targetHeight);
            cv::Mat downsampledFrame;
            cv::resize(frame,downsampledFrame,downsampledSize);
            frame = downsampledFrame;
       }
       FrameObject(int inWidth){
            cap(0);
            //resize the image to the new target width and height
            if(!cap.isOpened()){
                std::cerr << "Error: couldn't open the webcam." << std::endl;
                return -1;
	        }
            updateFrame();
            targetWidth = inWidth;
            updateTargets();
       }
};