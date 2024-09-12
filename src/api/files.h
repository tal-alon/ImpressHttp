#pragma once

#include <impress.h>

Response list_files(const Request &request);
Response get_file(const Request &request);
Response upload_file(const Request &request);
Response update_file(const Request &request);
Response delete_file(const Request &request);
