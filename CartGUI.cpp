#include "CartGUI.h"

void CartGUI::initGUIComponents()
{
	QHBoxLayout* mainLy = new QHBoxLayout{};
	setLayout(mainLy);

	mainLy->addWidget(list);

	QVBoxLayout* rightLy = new QVBoxLayout;

	QFormLayout* formsLy = new QFormLayout;
	formsLy->addRow("Movie ID: ", idTxt);
	formsLy->addRow("Number of movies: ", numTxt);
	formsLy->addRow("File Name: ", fileTxt);
	rightLy->addLayout(formsLy);

	QHBoxLayout* buttonsLy1 = new QHBoxLayout;
	buttonsLy1->addWidget(addToCartButton);
	buttonsLy1->addWidget(clearCartButton);
	buttonsLy1->addWidget(generateCartButton);
	rightLy->addLayout(buttonsLy1);

	QHBoxLayout* buttonsLy2 = new QHBoxLayout;
	buttonsLy2->addWidget(reloadButton);
	buttonsLy2->addWidget(exportButton);
	rightLy->addLayout(buttonsLy2);

	mainLy->addLayout(rightLy);

}

void CartGUI::initConnect()
{

	cart.add_observer(this);

	QObject::connect(reloadButton, &QPushButton::clicked, [&]() {

		reloadList(cart.get_all_from_cart());

		});

	QObject::connect(generateCartButton, &QPushButton::clicked, [&]() {

		auto number_of_movies = numTxt->text().toInt();
		cart.generate_cart(number_of_movies);
		reloadList(cart.get_all_from_cart());

		});

	QObject::connect(addToCartButton, &QPushButton::clicked, [&]() {

		auto id = idTxt->text().toInt();
		Movie m{ id,"","",0,"" };
		
		try
		{
			auto movie = cart.get_repo().repo_find_movie(m);
			cart.add_in_cart(movie);
		}
		catch (RepoException ex)
		{
			string message = ex.get_exception_message();
			QString warning_message = QString::fromStdString(message);
			QMessageBox::warning(nullptr, "Warning!", warning_message);
		}

		reloadList(cart.get_all_from_cart());

		});

	QObject::connect(clearCartButton, &QPushButton::clicked, [&]() {

		cart.clear_cart();
		reloadList(cart.get_all_from_cart());

		});

	QObject::connect(exportButton, &QPushButton::clicked, [&]() {

		auto file_name = fileTxt->text().toStdString();

		try
		{
			export_to_csv(file_name, cart.get_all_from_cart());
		}
		catch (RepoException ex)
		{
			string message = ex.get_exception_message();
			QString warning_message = QString::fromStdString(message);
			QMessageBox::warning(nullptr, "Warning!", warning_message);
		}

		});

}

void CartGUI::reloadList(vector<Movie> movies)
{
	list->clear();

	for (const auto& m : movies)
	{
		auto title = QString::fromStdString(m.get_title());
		auto genre = QString::fromStdString(m.get_genre());
		auto year = QString::number(m.get_year());
		auto protagonist = QString::fromStdString(m.get_protagonist());
		QString data = title + " " + genre + " " + year + " " + protagonist;
		QListWidgetItem* item = new QListWidgetItem(data);
		item->setData(Qt::UserRole, m.get_id());
		list->addItem(item);
	}

}
