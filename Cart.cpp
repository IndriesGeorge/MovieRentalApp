#include "Cart.h"

void Cart::add_in_cart(const Movie& movie)
{
	inCart.push_back(movie);
	// We use notify() to notify that something has been changhed
	notify();
}

void Cart::clear_cart()
{
	inCart.clear();
	notify();
}

void Cart::generate_cart(size_t number_of_movies)
{
	auto all = rep.repo_get_all_movies();

	// Shuffles the movies from all
	std::shuffle(all.begin(), all.end(), std::default_random_engine(std::random_device{}())); 
	while (inCart.size() < number_of_movies && all.size() > 0)
	{
		inCart.push_back(all.back());
		all.pop_back();
	}
	 
	notify();
}

const vector<Movie>& Cart::get_all_from_cart() const
{
	return inCart;
}

Repository& Cart::get_repo()
{
	return rep;
}
