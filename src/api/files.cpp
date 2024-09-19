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

    auto file_name = ROOT_DIR + request.path().url();
    const QueryParams& params = request.query_params();

    auto lang_it = params.find("lang"); // map iterator
    if (lang_it != params.end()) {
        string lang = lang_it->second;
        size_t dot_pos = file_name.find_last_of('.');
        if (dot_pos != string::npos) {
            file_name.insert(dot_pos, "." + lang);
        }
        else {
            file_name += "." + lang;
        }
    }

    ifstream file(file_name);
    if (!file) {
        return { Status::NotFound_404, "File not found" };
    }

    stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    return { Status::OK_200, buffer.str() };
}

Response upload_file(const Request& request) {

    auto full_path = ROOT_DIR + request.path().url();

    ifstream existing_file(full_path);
    if (existing_file.good()) {
        existing_file.close();
        return { Status::Conflict_409, "File already exists." };
    }

    ofstream out_file(full_path, ios::binary);

    if (!out_file.is_open()) {
        return { Status::InternalServerError_500, "Failed to open file for writing." };
    }

    try {
        out_file.write(request.body().c_str(), request.content_length());
        out_file.close();
    } catch (const exception& e) {
        return { Status::InternalServerError_500, string("Failed to write to file: ") + e.what() };
    }

    return { Status::Created_201, "File uploaded successfully." };
}

Response update_file(const Request& request) {
    auto full_path = ROOT_DIR + request.path().url();

    ifstream in_file(full_path);
    if (!in_file.good()) {
        in_file.close();
        return { Status::NotFound_404, "File not found" };
    }
    in_file.close();

    ofstream out_file(full_path, ios::binary | ios::trunc);

    if (!out_file.is_open()) {
        return { Status::InternalServerError_500, "Failed to open file for writing." };
    }

    try {
        out_file.write(request.body().c_str(), request.content_length());
        out_file.close();
    } catch (const exception& e) {
        return { Status::InternalServerError_500, string("Failed to update file: ") + e.what() };
    }

    return { Status::OK_200, "File updated successfully." };
}


Response delete_file(const Request &request) {
   auto file_name = ROOT_DIR + request.path().url();

    if (remove(file_name.c_str()) == 0) {
        return { Status::NoContent_204 };
    } else {
        return { Status::NotFound_404, "File not found" };
    }
}
