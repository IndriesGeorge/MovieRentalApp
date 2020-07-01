#include "Service.h"

void Service::service_add_movie(int id, const string& title, const string& genre, int year, const string& protagonist)
{
	Movie movie{ id, title, genre, year, protagonist };
	val.validate_movie(movie);
	rep.repo_add_movie(movie);
	undoActions.push_back(std::make_unique<UndoAdd>(rep, movie));
}

void Service::service_delete_movie(int id)
{
	Movie movie{ id,"","",0,"" };
	Movie m{ id,"","",0,"" };
	try{ m = rep.repo_find_movie(movie); }
	catch (...) {};
	rep.repo_delete_movie(movie);
	undoActions.push_back(std::make_unique<UndoDelete>(rep, m));
}

void Service::service_update_movie(int id, const string& title, const string& genre, int year, const string& protagonist)
{
	Movie new_movie{ id, title, genre, year, protagonist };
	val.validate_movie(new_movie);
	Movie m{ id,"","",0,"" };
	try { m = rep.repo_find_movie(new_movie); }
	catch (...) {};
	rep.repo_update_movie(new_movie);
	undoActions.push_back(std::make_unique<UndoUpdate>(rep, m));
}

Movie Service::service_find_movie(int id)
{
	Movie movie{ id,"","",0,"" };
	return rep.repo_find_movie(movie);
}

const vector<Movie>& Service::service_get_all_movies() const noexcept
{
	return rep.repo_get_all_movies();
}

void Service::undo()
{
	if (undoActions.empty())
		throw RepoException("No more undo actions!\n");

	undoActions.back()->doUndo();
	undoActions.pop_back();
}

vector<Movie> Service::sort_by_title()
{
	auto all = rep.repo_get_all_movies();

	std::sort(all.begin(), all.end(), [](const Movie& m1, const Movie& m2) {
		return m1.get_title() < m2.get_title();
		});

	return all;
}

vector<Movie> Service::filter_by_protagonist(const string& protagonist)
{
	auto all = rep.repo_get_all_movies();
	vector<Movie> filtered_by_protagonist;

	std::copy_if(all.begin(), all.end(), std::back_inserter(filtered_by_protagonist), [protagonist](const Movie& movie) {
		//return movie.get_protagonist() == protagonist;
		return (movie.get_protagonist().find(protagonist) != std::string::npos);
		});

	return filtered_by_protagonist;
}

vector<string> Service::get_all_genres()
{
	vector<string> all_genres;
	auto all = rep.repo_get_all_movies();

	for (const auto& m : all)
	{
		int ok = 1;
		for (const auto g : all_genres)
		{
			if (m.get_genre() == g)
			{
				ok = 0;
				break;
			}
		}
		
		if (ok)
		{
			all_genres.push_back(m.get_genre());
		}
	}

	return all_genres;
}

const vector<Movie>& Service::service_add_in_cart(int id)
{
	Movie m{ id,"","",0,"" };
	Movie movie = rep.repo_find_movie(m);
	cart.add_in_cart(movie);
	return cart.get_all_from_cart();
}

const vector<Movie>& Service::service_clear_cart()
{
	cart.clear_cart();
	return cart.get_all_from_cart();
}

const vector<Movie>& Service::service_add_random_in_cart(int number_of_movies)
{
	cart.generate_cart(number_of_movies);
	return cart.get_all_from_cart();
}

const vector<Movie>& Service::service_get_all_from_cart() const
{
	return cart.get_all_from_cart();
}

void Service::export_cart_to_csv(const string& file_name)
{
	export_to_csv(file_name, cart.get_all_from_cart());
}

Cart& Service::get_cart()
{
	return cart;
}
