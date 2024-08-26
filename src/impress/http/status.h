#pragma once
#include <string>
#include <map>

namespace impress {
    enum class Status {
        OK_200 = 200,
        Created_201 = 201,
        Accepted_202 = 202,
        NoContent_204 = 204,
        BadRequest_400 = 400,
        Unauthorized_401 = 401,
        Forbidden_403 = 403,
        NotFound_404 = 404,
        MethodNotAllowed_405 = 405,
        RequestTimeout_408 = 408,
        Conflict_409 = 409,
        UnprocessableEntity_422 = 422,
        InternalServerError_500 = 500,
        NotImplemented_501 = 501,
    };

    const std::map<Status, std::string> STATUS_MAP = {
        {Status::OK_200, "200 OK"},
        {Status::Created_201, "201 Created"},
        {Status::Accepted_202, "202 Accepted"},
        {Status::NoContent_204, "204 No Content"},
        {Status::BadRequest_400, "400 Bad Request"},
        {Status::Unauthorized_401, "401 Unauthorized"},
        {Status::Forbidden_403, "403 Forbidden"},
        {Status::NotFound_404, "404 Not Found"},
        {Status::MethodNotAllowed_405, "405 Method Not Allowed"},
        {Status::RequestTimeout_408, "408 Request Timeout"},
        {Status::Conflict_409, "409 Conflict"},
        {Status::UnprocessableEntity_422, "422 Unprocessable Entity"},
        {Status::InternalServerError_500, "500 Internal Server Error"},
        {Status::NotImplemented_501, "501 Not Implemented"},
    };

    const std::string &status_to_string(Status status);
}
