#pragma once
#include <string>


typedef std::string Method;

#define HTTP_GET Method {"GET"}
#define HTTP_POST Method {"POST"}
#define HTTP_PUT Method {"PUT"}
#define HTTP_DELETE Method {"DELETE"}
#define HTTP_PATCH Method {"PATCH"}
#define HTTP_OPTIONS Method {"OPTIONS"}
#define HTTP_HEAD Method {"HEAD"}
#define HTTP_TRACE Method {"TRACE"}
