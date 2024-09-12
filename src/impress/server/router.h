#pragma once

#include "../http/request.h"
#include "../http/response.h"
#include <map>
#include <set>
#include <string>
#include <tuple>


typedef Response (*RouteHandler)(const Request &request);
typedef std::tuple<std::set<Method>, std::string> RouteKey;
typedef std::map<RouteKey, RouteHandler> RouteMap;


class Router {
    RouteMap m_routes;

public:
    class RouteAdder {
        Router &m_router;
        std::set<Method> m_methods;
        std::string m_url;

    public:
        explicit RouteAdder(Router &router, std::set<Method> methods, std::string url);
        void register_handler(RouteHandler handler);
        void operator()(RouteHandler handler);
    };

    void add_route(const std::set<Method>& methods, const std::string &url, RouteHandler handler);
    Router::RouteAdder add_route(std::set<Method> methods, const std::string &url);
    Response handle_request(const Request &request);

private:
    RouteHandler get_handler(const Request &request);
};
