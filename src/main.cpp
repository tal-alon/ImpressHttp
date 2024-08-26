#include <iostream>
#include <impress.h>

using namespace std;
using namespace impress;

int main() {
    cout << "Hello, World!" << endl;
    cout << IMPRESS_VERSION << endl;

    auto status = Status::OK_200;
    cout << "Method: " << status_to_string(status) << endl;

    auto logger = StreamLogger(cerr, LogLevel::DEBUG);
    logger.info("Hello, Logger!");
    return 0;
}
