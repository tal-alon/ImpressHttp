#include <iostream>
#include <impress.h>

using namespace std;

const string EXAMPLE_REQUEST = "GET / HTTP/1.1\r\n"
                               "Host: localhost:8080\r\n"
                               "User-Agent: curl/7.68.0\r\n"
                               "Accept: */*\r\n\r\n";

int main() {
    cout << "Hello, World!" << endl;
    cout << IMPRESS_VERSION << endl;

    auto status = Status::OK_200;
    cout << "Method: " << status_to_string(status) << endl;

    auto logger = StreamLogger(cout, DEBUG_LVL);
    logger.info("Hello, Logger!");

//    Server server("127.0.0.1", 8080, logger);
//    server.run();

    auto request = Request::from_string(EXAMPLE_REQUEST);

    cout << request.to_string() << endl;

    return 0;
}
