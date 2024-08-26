#include "status.h"

using namespace std;
using namespace impress;

const string &impress::status_to_string(Status status) {
    return STATUS_MAP.at(status); // TODO check if key exists
}
