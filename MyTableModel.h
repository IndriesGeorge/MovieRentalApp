#pragma once
#include <QAbstractTableModel>
#include "Movie.h"
#include <vector>

using std::vector;

class MyTableModel : public QAbstractTableModel
{
	vector<Movie> movies;

public:

	/*
		MyTableModel Constructor
		Parameter: movies - vector<Movie>
	*/
	MyTableModel(const vector<Movie>& movies) : movies{ movies } {}


	int rowCount(const QModelIndex& parent = QModelIndex()) const override
	{
		return movies.size();
	}

	int columnCount(const QModelIndex& parent = QModelIndex()) const override
	{
		return 5;
	}

	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override
	{
		if (role == Qt::DisplayRole)
		{
			if (orientation == Qt::Horizontal)
			{
				if (section == 0)
					return QString("ID");
				else if (section == 1)
					return QString("Title");
				else if (section == 2)
					return QString("Genre");
				else if (section == 3)
					return QString("Release year");
				else if (section == 4)
					return QString("Main actor");
			}
			
			if (orientation == Qt::Vertical)
			{
				int count=0, nr = movies.size();

				while (count < nr)
				{
					if (section == count)
						return QString::number(count + 1);

					count++;
				}

			}

		}

		return QVariant{};

	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override
	{
		if (role == Qt::DisplayRole)
		{
			auto movie = movies[index.row()];

			if (index.column() == 0)
				return QString::number(movie.get_id());
			else if (index.column() == 1)
				return QString::fromStdString(movie.get_title());
			else if (index.column() == 2)
				return QString::fromStdString(movie.get_genre());
			else if (index.column() == 3)
				return QString::number(movie.get_year());
			else if (index.column() == 4)
				return QString::fromStdString(movie.get_protagonist());
		}

		if (role == Qt::UserRole)
		{
			auto movie = movies[index.row()];
			return movie.get_id();
		}

		return QVariant{};

	}

	void setMovies(vector<Movie> movies)
	{
		this->movies = movies;
		auto leftTop = createIndex(0, 0);
		auto bottomRight = createIndex(rowCount(), columnCount());
		emit dataChanged(leftTop, bottomRight);
	}

	void refresh()
	{
		emit layoutChanged();
	}

};

