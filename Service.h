#pragma once
#include "Movie.h"
#include "RepoException.h"
#include "Repository.h"
#include "Validator.h"
#include "undo.h"
#include "Cart.h"
#include "ExportToFile.h"
#include <string>
#include <vector>
#include <algorithm>
#include <memory>

using std::string;
using std::vector;
using std::unique_ptr;


class Service
{
	// Service contain a reference to Repository
	Repository& rep;

	// Service contain a referene to Validator
	Validator& val;

	/*
		We use smart pointers in order to avoid memory leaks(safe-exception code)
		We use a vector of actions and when we do undo the last action will be undone and deleted from this vector.
	*/
	vector<unique_ptr<UndoAction>> undoActions;

	Cart cart{ rep };

public:

	/*
		Service Constructor
		Parameters: Reference to Repository, Reference to Validator
	*/
	Service(Repository& rep, Validator& val) :rep{ rep }, val{ val }{}

	// We use this to avoid copying objects of Service type 
	Service(const Service& ot) = delete;

	/*
		Adds a movie in application
		Parameters: id - int, title - string, genre - string, year - int, protagonist - string
	*/
	void service_add_movie(int id, const string& title, const string& genre, int year, const string& protagonist);

	/*
		Removes a movie from application
		Parameter: id - int
	*/
	void service_delete_movie(int id);

	/*
		Modifies a movie from application
		Parameters: id - int, title - string, genre - string, year - int, protagonist - string
	*/
	void service_update_movie(int id, const string& title, const string& genre, int year, const string& protagonist);

	/*
		Returns a copy of a movie from application with a specified id
		Parameter: id - int
	*/
	Movie service_find_movie(int id);

	/*
		Returns a list with all movies from application
	*/
	const vector<Movie>& service_get_all_movies() const noexcept;

	/*
		Do undo for the last action
	*/
	void undo();

	/*
		Returns a vector containing all movies sorted ascending by title
		Parameter: title - string
	*/
	vector<Movie> sort_by_title();

	/*
		Returns a vector containing all movies having a specific protagonist
		Parameter: protagonist - string
	*/
	vector<Movie> filter_by_protagonist(const string& protagonist);

	vector<string> get_all_genres();

	// Cart

	/*
		Adds a movie into the cart
		Parameter: id - int
	*/
	const vector<Movie>& service_add_in_cart(int id);

	/*
		Removes all movies from cart
		Parameter: id - int
	*/
	const vector<Movie>& service_clear_cart();

	/*
		Add number_of_movies movies into the cart
		Parameter: number_of_movies - int
	*/
	const vector<Movie>& service_add_random_in_cart(int number_of_movies);

	/*
		Returns a list with all movies from cart
		Parameter: number_of_movies - int
	*/
	const vector<Movie>& service_get_all_from_cart() const;

	/*
		Exports all movies from cart in a CSV file
	*/
	void export_cart_to_csv(const string& file_name);

	/*
		Returns a reference of the Cart
	*/
	Cart& get_cart();

};

