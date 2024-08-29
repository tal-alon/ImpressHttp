#include "router.h"

#include <regex>
#include <iostream>

using namespace std;

void Router::add_route(Method method, const string &url, RouteHandler handler) {
    try {
        regex path_regex(url);
    } catch (exception &e) {
        cerr << "Invalid regex: " << url << endl;
        cerr << e.what() << endl;
        throw e;
    }
    m_routes[make_tuple(method, url)] = handler;
}

Response Router::handle_request(const Request &request) {
    RouteHandler handler = get_handler(request);
    if (handler == nullptr) {
        return {request.version(), Status::NotFound_404, Headers(), ""};
    }
    return handler(request);
}

RouteHandler Router::get_handler(const Request &request) {
    // loop through all routes and check if the method match and the path is a regex match to the route
    for (auto &route : m_routes) {
        Method route_method;
        string route_path;
        tie(route_method, route_path) = route.first;
        if (route_method != request.method()) {
            continue;
        }
        try {
            regex path_regex(route_path);
            if (!regex_match(request.path().url(), path_regex)) {
                continue;
            }
        } catch (exception &e) {
            // if the regex is invalid, skip this route
            continue;
        }
        return route.second;
    }
    return nullptr;
}
