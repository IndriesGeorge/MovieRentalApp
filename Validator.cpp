#include "Validator.h"

string Exception::get_validation_messages()
{
	string message = "";

	for (const string& msg : messages)
		message += msg;

	return message;

}

void Validator::validate_movie(const Movie& movie)
{
	vector<string> errors;

	if (movie.get_id() < 0)
		errors.push_back("The id must be greater than 0!\n");

	if (movie.get_title() == "")
		errors.push_back("The title cannot be empty!\n");

	if (movie.get_genre() == "")
		errors.push_back("The genre cannot be empty!\n");

	if (movie.get_year() < 1895)
		errors.push_back("The year of apparition must be greater than 1895!\n");

	if (movie.get_protagonist() == "")
		errors.push_back("The main actors's name cannot be empty!\n");

	if (errors.size() > 0)
		throw Exception(errors);

}
