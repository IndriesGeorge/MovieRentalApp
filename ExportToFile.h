#pragma once

#include "Movie.h"
#include "RepoException.h"
#include <vector>
#include <string>
#include <fstream>

using std::vector;
using std::string;
using std::ofstream;

/*
	Writes in a file(file_name) the list of the movies
	Parameters: file_name - string, movies - vector<Movie>
	Throws RepoException if the file cannot be created
*/
void export_to_csv(const string& file_name, const vector<Movie>& movies);
