class MyOptions {
    private:
        bool LED_STATUS = true;
        int BLUR_SIZE = 23;
        int LED_COUNT = 47;
        int RESIZE_WIDTH = 100;
        FileManage fm;
        
    public:
        int LED_POS[4][2] = {{38,47},{15,23},{24,37},{0,14}};
        
        void save(){
            json optionsJson;
            optionsJson["indices"]["right"]["s"] = LED_POS[0][0];
            optionsJson["indices"]["right"]["e"] = LED_POS[0][1];
            optionsJson["indices"]["left"]["s"] = LED_POS[1][0];
            optionsJson["indices"]["left"]["e"] = LED_POS[1][1];
            optionsJson["indices"]["top"]["s"] = LED_POS[2][0];
            optionsJson["indices"]["top"]["e"] = LED_POS[2][1];
            optionsJson["indices"]["bottom"]["s"] = LED_POS[3][0];
            optionsJson["indices"]["bottom"]["e"] = LED_POS[3][1];
            optionsJson["blurSize"] = BLUR_SIZE;
            optionsJson["ledCount"] = LED_COUNT;
            optionsJson["resizeWidth"] = RESIZE_WIDTH;

            std::string jsonString = optionsJson.dump();
            fm.write(jsonString);
        }
        void setLEDPosFromJson(json inJson){
            LED_POS[0][0]=inJson["indices"]["right"]["s"];
            LED_POS[0][1]=inJson["indices"]["right"]["e"];
            LED_POS[1][0]=inJson["indices"]["left"]["s"];
            LED_POS[1][1]=inJson["indices"]["left"]["e"];
            LED_POS[2][0]=inJson["indices"]["top"]["s"];
            LED_POS[2][1]=inJson["indices"]["top"]["e"];
            LED_POS[3][0]=inJson["indices"]["bottom"]["s"];
            LED_POS[3][1]=inJson["indices"]["bottom"]["e"];
        }
        void setLEDPosByValues(int rightS,int rightE, int leftS, int leftE, int topS, int topE, int bottomS, int bottomE){
            LED_POS[0][0]=rightS;
            LED_POS[0][1]=rightE;
            LED_POS[1][0]=leftS;
            LED_POS[1][1]=leftE;
            LED_POS[2][0]=topS;
            LED_POS[2][1]=topE;
            LED_POS[3][0]=bottomS;
            LED_POS[3][1]=bottomE;
        }
        bool getLEDStatus(){
            return LED_STATUS;
        }
        void setLEDStatus(bool ledStatus){
            LED_STATUS = ledStatus;
        }
        int getBlurSize(){
            return BLUR_SIZE;
        }
        void setBlurSize(int blurSize){
            BLUR_SIZE = blurSize;
        }
        int getLEDCount(){
            return LED_COUNT;
        }
        void setLEDCount(int ledCount){
            LED_COUNT = ledCount;
        }
        int getResizeWidth(){
            return RESIZE_WIDTH;
        }
        void setResizeWidth(int resizeWidth){
            RESIZE_WIDTH = resizeWidth;
        }
        MyOptions() : fm("options.json"){
            std::string json_str = fm.read();
            if(json_str != ""){
                try{
                    json optionsJson = json::parse(json_str);
                    LED_POS[0][0]=optionsJson["indices"]["right"]["s"];
                    LED_POS[0][1]=optionsJson["indices"]["right"]["e"];
                    LED_POS[1][0]=optionsJson["indices"]["left"]["s"];
                    LED_POS[1][1]=optionsJson["indices"]["left"]["e"];
                    LED_POS[2][0]=optionsJson["indices"]["top"]["s"];
                    LED_POS[2][1]=optionsJson["indices"]["top"]["e"];
                    LED_POS[3][0]=optionsJson["indices"]["bottom"]["s"];
                    LED_POS[3][1]=optionsJson["indices"]["bottom"]["e"];
                    BLUR_SIZE=optionsJson["blurSize"];
                    LED_COUNT=optionsJson["ledCount"];
                    RESIZE_WIDTH=optionsJson["resizeWidth"];
                }catch(const json::exception& e){
                    std::cerr << "Error parsing JSON: " << e.what() << std::endl;
                }
            }
        }
};