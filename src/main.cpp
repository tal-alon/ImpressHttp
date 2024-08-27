#include <iostream>
#include <impress.h>

using namespace std;

int main() {
    cout << "Hello, World!" << endl;
    cout << IMPRESS_VERSION << endl;

    auto status = Status::OK_200;
    cout << "Method: " << status_to_string(status) << endl;

    auto logger = StreamLogger(cerr, DEBUG_LVL);
    logger.info("Hello, Logger!");

//    Server server("127.0.0.1", 8080, logger);
//    server.run();
    return 0;
}
