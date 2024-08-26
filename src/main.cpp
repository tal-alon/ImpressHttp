#include <iostream>
#include <impress.h>

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::cout << IMPRESS_VERSION << std::endl;

    impress::Status status = impress::Status::OK_200;
    std::cout << "Method: " << impress::status_to_string(status) << std::endl;

    auto logger = impress::StreamLogger(std::cerr);
    logger.info("Hello, Logger!");
    return 0;
}
