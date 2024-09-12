#include "files.h"

Response list_files(const Request &request) {
    return { Status::OK_200, "list files" };
}

Response get_file(const Request &request) {
    return { Status::OK_200, "get file" };
}

Response upload_file(const Request &request) {
    return { Status::OK_200, "upload file" };
}

Response update_file(const Request &request) {
    return { Status::OK_200, "update file" };
}

Response delete_file(const Request &request) {
    return { Status::OK_200, "delete file" };
}
