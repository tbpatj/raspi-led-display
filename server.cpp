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

    srv.Get("/indices",[](const httplib::Request& req, httplib::Response& res) {
        std::ostringstream json_stream;
        json_stream << "{";
        json_stream << "\"right\": {\"s\": " << LED_POS[0][0] << ", \"e\": " << LED_POS[0][1] << "},";
        json_stream << "\"left\": {\"s\": " << LED_POS[1][0] << ", \"e\": " << LED_POS[1][1] << "},";
        json_stream << "\"top\": {\"s\": " << LED_POS[2][0] << ", \"e\": " << LED_POS[2][1] << "},";
        json_stream << "\"bottom\": {\"s\": " << LED_POS[3][0] << ", \"e\": " << LED_POS[3][1] << "}";
        json_stream << "}";
        res.set_content(json_stream, "application/json")
    });

    svr.set_mount_point("/static", "./build/static");

    // svr.Post("/indices",[](const httplib::Request& req, httplib::Response& res){
    //     std::cout << req << std::endl;
    //     // std::cout << res << std::endl;
    // });

    svr.listen("0.0.0.0", 3000);

}