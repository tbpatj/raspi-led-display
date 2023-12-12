

void runServer(){
    httplib::Server svr;

    svr.Get("/", [](const httplib::Request& req, httplib::Response& res) {
       std::string filepath = "./build/index.html";

         std::ifstream file(filepath, std::ios::in | std::ios::binary);
        if (file.is_open()) {
            // Read the content of the HTML file
            std::string file_content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

            // Serve the HTML content
            res.set_content(file_content.c_str(), "text/html");
        } else {
            // Return a 404 response if the file doesn't exist
            res.status = 404;
            res.set_content("Not Found", "text/plain");
        }
        std::cout << "hit" << std::endl;
    });

    svr.Get("/indices",[](const httplib::Request& req, httplib::Response& res) {
        std::ostringstream json_stream;
        json_stream << "{";
        json_stream << "\"right\": {\"s\": " << options.LED_POS[0][0] << ", \"e\": " << options.LED_POS[0][1] << "},";
        json_stream << "\"left\": {\"s\": " << options.LED_POS[1][0] << ", \"e\": " << options.LED_POS[1][1] << "},";
        json_stream << "\"top\": {\"s\": " << options.LED_POS[2][0] << ", \"e\": " << options.LED_POS[2][1] << "},";
        json_stream << "\"bottom\": {\"s\": " << options.LED_POS[3][0] << ", \"e\": " << options.LED_POS[3][1] << "}";
        json_stream << "}";
        std::string json_str = json_stream.str();
        res.set_content(json_str, "application/json");
    });

    svr.set_mount_point("/static", "./build/static");

    svr.Post("/indices", [](const httplib::Request& req, httplib::Response& res) {
         try {
            json requestJson = json::parse(req.body);
            options.setLEDPosFromJson(requestJson);
            options.save();
            res.set_content("success","text/plain");
         }catch(const json::exception& e){
             std::cerr << "Error parsing JSON: " << e.what() << std::endl;
            res.status = 400;  // Bad Request
            res.set_content("Error parsing JSON", "text/plain");
         }
    });

    svr.Post("/status",[](const httplib::Request& req, httplib::Response& res) {
        try {
            json requestJson = json::parse(req.body);
            options.setLEDStatus(requestJson["status"]);
            options.save();
            res.set_content("success","text/plain");
         }catch(const json::exception& e){
             std::cerr << "Error parsing JSON: " << e.what() << std::endl;
            res.status = 400;  // Bad Request
            res.set_content("Error parsing JSON", "text/plain");
         }
    });
 
    svr.Get("/status",[](const httplib::Request& req, httplib::Response& res) {
        std::ostringstream json_stream;
        json_stream << "{" << "\"status\": " << options.getLEDStatus() << "}";
        std::string json_str = json_stream.str();
        res.set_content(json_str, "application/json");
    });

    svr.Post("/blurSize",[](const httplib::Request& req, httplib::Response& res) {
        try {
            json requestJson = json::parse(req.body);
            options.setBlurSize(requestJson["blurSize"]);
            options.save();
            res.set_content("success","text/plain");
         }catch(const json::exception& e){
             std::cerr << "Error parsing JSON: " << e.what() << std::endl;
            res.status = 400;  // Bad Request
            res.set_content("Error parsing JSON", "text/plain");
         }
    });

    svr.Get("/blurSize", [](const httplib::Request& req, httplib::Response& res) {
    try {
        int blurSize = options.getBlurSize();
        json responseJson = { {"blurSize", blurSize} };
        res.set_content(responseJson.dump(), "application/json");
    } catch(const std::exception& e){
        std::cerr << "Error getting blurSize: " << e.what() << std::endl;
        res.status = 500;  // Internal Server Error
        res.set_content("Error getting blurSize", "text/plain");
    }

    svr.Post("/powerOff", [](const httplib::Request& req, httplib::Response& res) {
        try {
            json requestJson = json::parse(req.body);
            options.setPowerOn(requestJson["powerOff"]);
            res.set_content("success", "text/plain");
        } catch (const json::exception& e) {
            std::cerr << "Error parsing JSON: " << e.what() << std::endl;
            res.status = 400;  // Bad Request
            res.set_content("Error parsing JSON", "text/plain");
        }
    });



});

    svr.listen("0.0.0.0", 3000);

}