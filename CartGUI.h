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
#include <QtWidgets/qlistwidget.h>

#include "Movie.h"
#include "Repository.h"
#include "RepoException.h"
#include "MyTableModel.h"
#include "Service.h"
#include "ExportToFile.h"
#include "observer.h"
#include <string>

using std::string;

class CartGUI : public QWidget, public Observer
{
	Cart& cart;

	QListWidget* list = new QListWidget;
	QPushButton* addToCartButton = new QPushButton{ "&Add Movie" };
	QPushButton* clearCartButton = new QPushButton{ "&Clear Cart" };
	QPushButton* generateCartButton = new QPushButton{ "&Generate Cart" };
	QPushButton* exportButton = new QPushButton{ "&Export Cart" };
	QPushButton* reloadButton = new QPushButton{ "&Reload" };

	QLineEdit* idTxt = new QLineEdit;
	QLineEdit* numTxt = new QLineEdit;
	QLineEdit* fileTxt = new QLineEdit;

	void initGUIComponents();

	void initConnect();

	void reloadList(vector<Movie> movies);

public:

	CartGUI(Cart& c) :cart{ c } 
	{
		initGUIComponents();
		initConnect();
		reloadList(cart.get_all_from_cart());
	}

	void update() override
	{
		reloadList(cart.get_all_from_cart());
	}

	~CartGUI()
	{
		cart.remove_observer(this);
	}

};