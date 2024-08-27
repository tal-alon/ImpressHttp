#include "method.h"

using namespace std;

Method str_to_method(const std::string &method_str) {
    return HTTP_METHODS.at(method_str);
}

std::string method_to_string(Method method) {
    for (auto &pair : HTTP_METHODS) {
        if (pair.second == method) {
            return pair.first;
        }
    }
    return "";
}
