#include <iostream>
#include <impress.h>

using namespace std;

const string EXAMPLE_REQUEST = "GET /index.html?param1=1&param2=2 HTTP/1.1\r\n"
                               "Host: localhost:8080\r\n"
                               "User-Agent: curl/7.68.0\r\n"
                               "Accept: */*\r\n\r\n";

Response hello_world(const Request &request);

int main() {
    cout << "Hello, World!" << endl;
    cout << IMPRESS_VERSION << endl;

    auto logger = StreamLogger(cout, DEBUG_LVL);
    logger.info("Hello, Logger!");

//    Server server("127.0.0.1", 8080, logger);
//    server.run();

    auto request = Request::from_string(EXAMPLE_REQUEST);

    cout << request.to_string() << endl;

    Router router;
    router.add_route(Method::GET, "/*", hello_world);

    auto response = router.handle_request(request);
    cout << response.to_string() << endl;

    return 0;
}

Response hello_world(const Request &request) {
    return {Status::OK_200, "Hello, World!"};
}
