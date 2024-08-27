#include "method.h"

using namespace std;
using namespace impress;

optional<Method> impress::get_method(const string &method_str) {
    if (HTTP_METHODS.contains(method_str)) {
        return HTTP_METHODS.at(method_str);
    }
    return nullopt;
}
