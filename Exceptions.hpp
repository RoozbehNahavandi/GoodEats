#ifndef _EXCEPTIONS_HPP_
#define _EXCEPTIONS_HPP_

#include <string>

class Exception {
public:
	Exception(std::string _description) : description(_description) {};
	std::string Description() { return description; };
protected:
	std::string description;
};

class NotFound : public Exception {
public:
	NotFound() : Exception("Not Found") {};
};

class PermissionDenied : public Exception {
public:
	PermissionDenied() : Exception("Permission Denied") {};
};

class BadRequest : public Exception {
public:
	BadRequest() : Exception("Bad Request") {};
};


#endif