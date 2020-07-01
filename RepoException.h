#pragma once

#include <string>

using std::string;


class RepoException
{
	string message;

public:

	RepoException(const string& msg) :message{ msg } {}

	string get_exception_message();

};

