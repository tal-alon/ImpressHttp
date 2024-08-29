#pragma once

#include <tuple>
#include <string>
#include <map>
#include <set>
#include "../http/request.h"
#include "../http/response.h"


typedef Response (*RouteHandler)(const Request &request);
typedef std::tuple<std::set<Method>, std::string> RouteKey;
typedef std::map<RouteKey, RouteHandler> RouteMap;


class Router {
    RouteMap m_routes;

public:
    void add_route(std::set<Method> methods, const std::string &url, RouteHandler handler);
    Response handle_request(const Request &request);

private:
    RouteHandler get_handler(const Request &request);
};
