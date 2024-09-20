#include <impress.h>
#include "./api/files.h"
#include "./config.h"
#include <iostream>
#include <sstream>

#define APP_ROUTE(server, methods, path) server.router().add_route(methods, path)

using namespace std;


Server* build_server() {
    auto logger = new StreamLogger(cout, INFO_LVL);
    logger->info("Building server...");

    auto app = new Server(IP, PORT, logger);
    APP_ROUTE((*app), {HTTP_GET}, "/ping")
    ([](const Request &req) -> Response {
        return {Status::OK_200, "pong"};
    });

    return app;
}


int main() {
    WSAInitializer wsa;
    cout << "Impress Version: " << IMPRESS_VERSION << endl;

    Server *app = build_server();
    include_files_routes(app->router());
    app->run();
}
