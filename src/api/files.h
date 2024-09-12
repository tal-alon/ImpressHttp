#pragma once

#include <impress.h>

Response get_file(Request &request);
Response upload_file(Request &request);
Response update_file(Request &request);
Response delete_file(Request &request);
Response list_files(Request &request);
