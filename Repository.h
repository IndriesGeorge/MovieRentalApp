#pragma once
#include "Movie.h"
#include "RepoException.h"
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;


class Repository
{
	vector<Movie> movies;
	string file_name;

	/*
		Private method: Loads from file all saved movies
	*/
	void load_from_file();

	/*
		Private method: Stores in file all movies from memory
	*/
	void write_to_file();

public:

	/*
		Repository Constructor
		Calls load_from_file() private method
	*/
	Repository(const string& fname) :file_name{ fname }
	{
		load_from_file();
	}

	// We use this to avoid copying the Repository 
	Repository(const Repository& ot) = delete;

	/*
		Adds a movie in memory
		Throws RepoException if there already exists another movie with the same id
		Parameter: movie - Movie 
	*/
	void repo_add_movie(const Movie& movie);

	/*
		Removes a movie from memory
		Throws RepoException if the movie doesn't exist
		Parameter: movie - Movie 
	*/
	void repo_delete_movie(const Movie& movie);

	/*
		Modifies a movies from memory
		Throws RepoException if the movie doesn't exist
		Parameter: new_movie - Movie 
		Return type: void
	*/
	void repo_update_movie(const Movie& new_movie);

	/*
		Returns a copy of a searched movie from memory
		Throws RepoException if the movie doesn't exist
		Parameter: movie - Movie
	*/
	Movie repo_find_movie(const Movie& movie);

	/*
		Returns through reference a list with all movies
	*/
	const vector<Movie>& repo_get_all_movies() const noexcept;
};

