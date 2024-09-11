#include "status.h"

using namespace std;

const string &status_to_string(Status status) {
    return STATUS_MAP.at(status);// TODO check if key exists
}
