void runServer(){
    httplib::Server svr;

    svr.Get("/", [](const httplib::Request& req, httplib::Response& res) {
       std::string filepath = "./build/index.html";

        // Check if the file exists
        if (std::ifstream(filepath)) {
            // Serve the HTML file
            httplib::FileReader fr(filepath.c_str());

            // Serve the HTML content
            res.set_content(fr.data(), fr.length(), "text/html");
        } else {
            // Return a 404 response if the file doesn't exist
            res.status = 404;
            res.set_content("Not Found", "text/plain");
        }
        std::cout << "hit" << std::endl;
    });

    svr.set_mount_point("/static", "./build/static");

    // svr.Post("/indices",[](const httplib::Request& req, httplib::Response& res){
    //     std::cout << req << std::endl;
    //     // std::cout << res << std::endl;
    // });

    svr.listen("0.0.0.0", 3000);

}