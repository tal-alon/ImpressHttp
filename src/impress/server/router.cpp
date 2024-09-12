#include "router.h"

#include <iostream>
#include <regex>
#include <utility>

using namespace std;

void Router::add_route(const std::set<Method>& methods, const string &url, RouteHandler handler) {
    try {
        regex path_regex(url);
    } catch (exception &e) {
        cerr << "Invalid regex: " << url << endl;
        cerr << e.what() << endl;
        throw e;
    }
    m_routes[make_tuple(methods, url)] = handler;
}

Router::RouteAdder Router::add_route(std::set<Method> methods, const string &url) {
    return Router::RouteAdder(*this, std::move(methods), url);
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
        set<Method> route_methods;
        string route_path;
        tie(route_methods, route_path) = route.first;
        if (route_methods.find(request.method()) == route_methods.end()) {
            continue;// method does not match
        }
        regex path_regex(route_path);
        if (!regex_match(request.path().url(), path_regex)) {
            continue;// path does not match
        }

        return route.second;
    }
    return nullptr;
}

Router::RouteAdder::RouteAdder(Router &router, std::set<Method> methods, std::string url)
    : m_router(router), m_methods(std::move(methods)), m_url(std::move(url)) {}

void Router::RouteAdder::register_handler(RouteHandler handler) {
    m_router.add_route(m_methods, m_url, handler);
}
void Router::RouteAdder::operator()(RouteHandler handler) {
    register_handler(handler);
}
