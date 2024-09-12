#include <impress.h>
#include "./api/files.h"
#include <iostream>
#include <sstream>

#define APP_ROUTE(server, methods, path) server.router().add_route(methods, path)

using namespace std;

const string EXAMPLE_REQUEST = "GET /index.html?param1=1&param2=2 HTTP/1.1\r\n"
                               "Host: localhost:8080\r\n"
                               "User-Agent: curl/7.68.0\r\n"
                               "Accept: */*\r\n\r\n";

Response hello_world(const Request &req) {
    stringstream ss("");

    ss << "Hello, World!" << endl;
    ss << "got header: " << endl;
    for (auto &header : req.headers()) {
        ss << "\t" << header.first << ": " << header.second << endl;
    }
    ss << "got params: " << endl;
    for (auto &param : req.query_params()) {
        ss << "\t" << param.first << ": " << param.second << endl;
    }

    return {Status::OK_200, ss.str()};
}


Server* build_server() {
    auto logger = new StreamLogger(cout, DEBUG_LVL);
    logger->info("Building server...");

    auto app = new Server("127.0.0.1", 8000, logger);
    APP_ROUTE((*app), {HTTP_GET}, "/hello")(hello_world);

    return app;
}

void include_files_api(Server &server) {
    APP_ROUTE(server, {HTTP_GET}, "^/$")(list_files);
    APP_ROUTE(server, {HTTP_GET}, "^/.+$")(get_file);
    APP_ROUTE(server, {HTTP_POST}, "^/.+$")(upload_file);
    APP_ROUTE(server, {HTTP_PUT}, "^/.+$")(update_file);
    APP_ROUTE(server, {HTTP_DELETE}, "^/.+$")(delete_file);
}


int main() {
    WSAInitializer wsa;
    cout << "Impress Version: " << IMPRESS_VERSION << endl;

    Server *app = build_server();

    APP_ROUTE((*app), {HTTP_GET}, "/")
    ([](const Request &req) -> Response {
        return {Status::OK_200, "Hello, World!"};
    });

    include_files_api(*app);
    app->run();
}
