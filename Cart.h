#pragma once
#include "Movie.h"
#include "Repository.h"
#include "observer.h"
#include <vector>
#include <string>
#include <algorithm>
#include <random>

using std::vector;
using std::string;

class Cart : public Observable
{
	Repository& rep;

	vector<Movie> inCart;

public:

	Cart(Repository& rep) :rep{ rep } {};

	/*
		Adds a movie into the cart
		Parameter: movie - Movie type
		Return type: void
	*/
	void add_in_cart(const Movie& movie);

	/*
		Deletes all movies from cart
		Return type: void
	*/
	void clear_cart();

	void generate_cart(size_t number_of_movies);

	/*
		Returns a list with all movies from cart
		Return type: vector<Movie>
	*/
	const vector<Movie>& get_all_from_cart() const;

	Repository& get_repo();

};

