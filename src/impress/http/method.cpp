#include "method.h"

using namespace std;

Method get_method(const string &method_str) {
    return HTTP_METHODS.at(method_str);
}
