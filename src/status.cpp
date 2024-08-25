#include "status.h"

using namespace std;
using namespace impress;

const string &status_to_string(impress::Status status) {
    return STATUS_MAP.at(status); // TODO check if key exists
}
