#include "files.h"

#include "../config.h"
#include <windows.h>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;

void list_files_rec(const string& dir, vector<string>& file_names) {
    string search_path = dir + "\\*";
    WIN32_FIND_DATA find_file_data;
    HANDLE h_find = FindFirstFile(search_path.c_str(), &find_file_data);

    if (h_find == INVALID_HANDLE_VALUE) {
        cerr << "Directory not found: " << dir << endl;
        return;
    }
    do {
        const string file_or_dir_name = find_file_data.cFileName;
        // Skip "." and ".."
        if (file_or_dir_name == "." || file_or_dir_name == "..") {
            continue;
        }
        string full_path = dir + "/" + file_or_dir_name;
        if (find_file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            // It's a directory, recurse into it
            list_files_rec(full_path, file_names);
        } else {
            // It's a regular file, add to the list
            file_names.push_back(full_path);
        }
    } while (FindNextFile(h_find, &find_file_data) != 0);

    FindClose(h_find);
}

vector<string> list_files(const string& dir) {
    vector<string> file_names;
    list_files_rec(dir, file_names);
    return file_names;
}


Response list_files(const Request &request) {
    auto files = list_files(ROOT_DIR);
    stringstream ss("");
    for (auto &file : files) {
        ss << file << endl;
    }

    return { Status::OK_200, ss.str() };
}

Response get_file(const Request &request) {
    // TODO handle headers such as language, etc.
    auto file_name = ROOT_DIR + request.path().url();

    ifstream file(file_name);
    if (!file) {
        return { Status::NotFound_404, "File not found" };
    }

    stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    return { Status::OK_200, buffer.str() };
}

Response upload_file(const Request &request) {
    return { Status::OK_200, "upload file" };
}

Response update_file(const Request &request) {
    return { Status::OK_200, "update file" };
}

Response delete_file(const Request &request) {
   auto file_name = ROOT_DIR + request.path().url();

    if (remove(file_name.c_str()) == 0) {
        return { Status::NoContent_204 };
    } else {
        return { Status::NotFound_404, "File not found" };
    }
}
