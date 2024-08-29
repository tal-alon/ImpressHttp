#include <impress.h>
#include <iostream>
#include <sstream>

#define APP_ROUTE(server, method, path, handler) server.router().add_route(method, path, handler)

using namespace std;

const string EXAMPLE_REQUEST = "GET /index.html?param1=1&param2=2 HTTP/1.1\r\n"
                               "Host: localhost:8080\r\n"
                               "User-Agent: curl/7.68.0\r\n"
                               "Accept: */*\r\n\r\n";

Response hello_world(const Request &req) {
    stringstream ss("");

    ss << "Hello, World!" << endl;
    ss << "got header: " << endl;
    for (auto &header : req.headers().map()) {
        ss <<  "\t" << header.first << ": " << header.second << endl;
    }
    ss << "got params: " << endl;
    for (auto &param : req.query_params()) {
        ss << "\t" << param.first << ": " << param.second << endl;
    }

    return {Status::OK_200, ss.str()};
}


Server build_server() {
    auto logger = StreamLogger(cout, DEBUG_LVL);

    Server app("127.0.0.1", 8080, logger);
    APP_ROUTE(app, HTTP_GET, ".+", hello_world);

    return app;
}


int main() {
    cout << "Hello, World!" << endl;
    cout << IMPRESS_VERSION << endl;

    Server app = build_server();
//    server.run();

    Request request = Request::from_string(EXAMPLE_REQUEST);
    cout << request.to_string() << endl;

    Response response = app.router().handle_request(request);
    cout << response.to_string() << endl;

    return 0;

}
