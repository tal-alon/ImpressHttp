#include "method.h"

using namespace std;
using namespace impress;

optional<Method> impress::get_method(const string &method_str) {
    return HTTP_METHODS.at(method_str); // TODO check if method_str exists in HTTP_METHODS
}
