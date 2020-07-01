#pragma once

#include <qwidget.h>
#include <QtWidgets/qlayout.h>
#include <QtWidgets/qtableview.h>
#include <QtWidgets/qlistview.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qmessagebox.h>
#include <QtWidgets/qcheckbox>
#include <QtWidgets/qcombobox>
#include <QtWidgets/qspinbox.h>
#include <QtWidgets/qlabel.h>

#include "Movie.h"
#include "Repository.h"
#include "RepoException.h"
#include "Validator.h"
#include "MyTableModel.h"
#include "Service.h"
#include "Cart.h"
#include "CartGUI.h"
#include <string>

using std::string;

class GUI : public QWidget
{

	// GUI class contains a reference to Service
	Service& serv;

	QPushButton* addButton = new QPushButton{ "&Add" };
	QPushButton* deleteButton = new QPushButton{ "&Delete" };
	QPushButton* updateButton = new QPushButton{ "&Update" };
	QPushButton* UndoButton = new QPushButton{ "&Undo" };
	QPushButton* ReloadButton = new QPushButton{ "&Reload" };

	QPushButton* openCartButton = new QPushButton{ "&Open Cart" };
	
	QPushButton* sortByTitle = new QPushButton{ "&Sort by title" };
	QPushButton* filterByProtagonist = new QPushButton{ "&Filter by protagonist" };

	QLineEdit* idTxt = new QLineEdit;
	QLineEdit* titleTxt = new QLineEdit;
	QLineEdit* genreTxt = new QLineEdit;
	QLineEdit* yearTxt = new QLineEdit;
	QLineEdit* protagonistTxt = new QLineEdit;

	QSpinBox* yearSpin = new QSpinBox;
	QComboBox* genreCombo = new QComboBox;
	QStringList genresList{ "Action","Adventure","Comedy","Drama","Historical","Mystery","Romance","Science-Fiction","Thriller","Western" };
	QLabel* yearLbl = new QLabel{ "&Year: " };

	QWidget* checkBoxesWidget = new QWidget;
	QVBoxLayout* checkBoxesLy = new QVBoxLayout;
	QPushButton* filterByGenreButton = new QPushButton{ "&Filter by genre" };

	MyTableModel* model = new MyTableModel{ serv.service_get_all_movies() };
	QTableView* table = new QTableView;

	// Creates the layouts and adds widgets on them
	void initGUIComponents();

	// Connects Signals and Slots
	void initConnect();

	// Reloads the table with all movies from application
	void reloadTable(vector<Movie> movies);

	// Generates check boxes with all genres from application
	void generateCheckBoxes(vector<Movie> movies);

public:

	/*
		GUI Constructor
		Parameter: Reference to Service
	*/
	GUI(Service& serv) :serv{ serv } 
	{
		table->setModel(model);
		initGUIComponents();
		initConnect();
		reloadTable(serv.service_get_all_movies());
		generateCheckBoxes(serv.service_get_all_movies());
	}

};

