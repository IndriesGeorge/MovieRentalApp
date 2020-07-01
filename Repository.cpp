#include "Repository.h"

void Repository::load_from_file()
{
	ifstream in(file_name);

	if (!in.is_open())
		throw RepoException("Unable to open the file: " + file_name);

	while (!in.eof())
	{
		Movie movie{ 0,"","",0,"" };
		in >> movie;
		if (in.eof())
			break;
		movies.push_back(movie);
	}

	in.close();

}

void Repository::write_to_file()
{
	ofstream out(file_name);

	if (!out.is_open())
		throw RepoException("Unable to open the file: " + file_name);

	for (const Movie& m : movies)
	{
		out << m;
	}

	out.close();

}

void Repository::repo_add_movie(const Movie& movie)
{
	auto found = std::find_if(movies.begin(), movies.end(), [movie](const Movie& m) {
		return m.get_id() == movie.get_id();
		});

	if (found != movies.end())
		throw RepoException("Existent movie!\n");

	movies.push_back(movie);

	write_to_file();

}

void Repository::repo_delete_movie(const Movie& movie)
{
	auto found = std::find_if(movies.begin(), movies.end(), [movie](const Movie& m) {
		return m.get_id() == movie.get_id();
		});

	if (found == movies.end())
		throw RepoException("Inexistent movie!\n");

	movies.erase(found);

	write_to_file();
}

void Repository::repo_update_movie(const Movie& new_movie)
{
	auto found = std::find_if(movies.begin(), movies.end(), [new_movie](const Movie& m) {
		return m.get_id() == new_movie.get_id();
		});

	if (found == movies.end())
		throw RepoException("Inexistent movie!\n");

	(*found).set_title(new_movie.get_title());
	(*found).set_genre(new_movie.get_genre());
	(*found).set_year(new_movie.get_year());
	(*found).set_protagonist(new_movie.get_protagonist());

	write_to_file();

}

Movie Repository::repo_find_movie(const Movie& movie)
{
	auto found = std::find_if(movies.begin(), movies.end(), [movie](const Movie& m) {
		return m.get_id() == movie.get_id();
		});

	if (found == movies.end())
		throw RepoException("Inexistent movie!\n");

	return *found;

}

const vector<Movie>& Repository::repo_get_all_movies() const noexcept
{
	return movies;
}
