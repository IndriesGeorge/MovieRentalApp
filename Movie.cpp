#include "Movie.h"

int Movie::get_id() const noexcept
{
	return id;
}

string Movie::get_title() const
{
	return title;
}

string Movie::get_genre() const
{
	return genre;
}

int Movie::get_year() const noexcept
{
	return year;
}

string Movie::get_protagonist() const
{
	return protagonist;
}

void Movie::set_title(string str)
{
	title = str;
}

void Movie::set_genre(string str)
{
	genre = str;
}

void Movie::set_year(int val)
{
	year = val;
}

void Movie::set_protagonist(string str)
{
	protagonist = str;
}

istream& operator>>(istream& in, Movie& movie)
{
	string line, part; 
	vector<string> parts; // We store in this vector all components of movie read from file
	parts.clear(); 
	std::getline(in, line); // Read the entire line
	std::stringstream ss(line); 

	while (std::getline(ss, part, ';')) // Split the line using ; separator 
	{
		parts.push_back(part); 
	}

	if (parts.size() != 5) // If the data are not complete
		return in;

	movie.id = std::stoi(parts.at(0));
	movie.title = parts.at(1);
	movie.genre = parts.at(2);
	movie.year = std::stoi(parts.at(3));
	movie.protagonist = parts.at(4);

	return in;

}

ostream& operator<<(ostream& out, const Movie& movie)
{
	out << movie.get_id() << ";";
	out << movie.get_title() << ";";
	out << movie.get_genre() << ";";
	out << movie.get_year() << ";";
	out << movie.get_protagonist() << "\n";

	return out;
}
