#include "Exceptions.hpp"

using namespace std;

Exception::Exception(string _description) : description(_description) {};

NotFound::NotFound() : Exception("Not Found") {}

BadRequest::BadRequest() : Exception("Bad Request") {}

PermissionDenied::PermissionDenied() : Exception("Permission Denied") {}
