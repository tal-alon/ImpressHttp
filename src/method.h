#ifndef IMPRESSHTTP_METHOD_H
#define IMPRESSHTTP_METHOD_H

#include <map>
#include <string>

namespace impress {

    enum class Method {
        GET,
        POST,
        PUT,
        DELETE,
        HEAD,
        OPTIONS,
        TRACE
    };

    const std::map<std::string, Method> HTTP_METHODS = {
            {"GET", Method::GET},
            {"POST", Method::POST},
            {"PUT", Method::PUT},
            {"DELETE", Method::DELETE},
            {"HEAD", Method::HEAD},
            {"OPTIONS", Method::OPTIONS},
            {"TRACE", Method::TRACE}};

    Method get_method(const std::string &method_str);
}// namespace impress

#endif//IMPRESSHTTP_METHOD_H
