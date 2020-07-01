#pragma once
#include "Movie.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

class Exception
{

	vector<string> messages;

public:

	/*
		Exception Constructor
		Parameter: errors - vector<string>
	*/
	Exception(const vector<string>& errors) :messages{ errors } {}

	/*
		Returns a string containing all validation errors 
	*/
	string get_validation_messages();

};


class Validator
{
	
public:

	/*
		Validate a movie: Check if all attributes of a movie respect some conditions
		Parameter: movie - Movie
	*/
	void validate_movie(const Movie& movie);

};

