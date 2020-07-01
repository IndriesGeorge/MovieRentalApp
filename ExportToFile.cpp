#include "ExportToFile.h"

void export_to_csv(const string& file_name, const vector<Movie>& movies)
{
	ofstream out(file_name, std::ios::trunc);

	if (!out.is_open())
		throw RepoException("Unable to open the file: " + file_name);

	for (const auto& m : movies)
	{
		out << m.get_id() << ";";
		out << m.get_title() << ";";
		out << m.get_genre() << ";";
		out << m.get_year() << ";";
		out << m.get_protagonist() << "\n";
	}

	out.close();

}
