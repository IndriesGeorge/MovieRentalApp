#include "Tests.h"
#include "Movie.h"
#include "Validator.h"
#include "RepoException.h"
#include "Repository.h"
#include "Service.h"
#include "Cart.h"
#include <assert.h>
#include <string>
#include <vector>
#include <fstream>

using std::string;
using std::vector;
using std::ofstream;

void test_create()
{
	Movie m{ 1,"tt","gn",2015,"pp" };
	assert(m.get_id() == 1);
	assert(m.get_title() == "tt");
	assert(m.get_genre() == "gn");
	assert(m.get_year() == 2015);
	assert(m.get_protagonist() == "pp");
}

void test_validate()
{
	Movie m1{ -1,"tt","",2015,"pp" };
	Validator val;

	try
	{
		val.validate_movie(m1);
		assert(false);
	}
	catch (Exception ex)
	{
		assert(true);
		assert(ex.get_validation_messages() == "The id must be greater than 0!\nThe genre cannot be empty!\n");
	}

	Movie m2{ 1,"","gn",1780,"pp" };

	try
	{
		val.validate_movie(m2);
		assert(false);
	}
	catch (Exception ex)
	{
		assert(true);
		assert(ex.get_validation_messages() == "The title cannot be empty!\nThe year of apparition must be greater than 1895!\n");
	}

	Movie m3{ 1,"tt","gn",2015,"" };

	try
	{
		val.validate_movie(m3);
		assert(false);
	}
	catch (Exception ex)
	{
		assert(true);
		assert(ex.get_validation_messages() == "The main actors's name cannot be empty!\n");
	}

}

void test_domain()
{
	test_create();
	test_validate();
}

void test_repo_add()
{
	ofstream out("testfile.txt");
	out.close();
	Repository rep{ "testfile.txt" };
	Movie m{ 1,"tt","gn",2015,"pp" };
	rep.repo_add_movie(m);
	auto all = rep.repo_get_all_movies();
	assert(all.size() == 1);
	try
	{
		rep.repo_add_movie(m);
		assert(false);
	}
	catch (RepoException ex)
	{
		assert(true);
		assert(ex.get_exception_message() == "Existent movie!\n");
	}
}

void test_repo_delete()
{
	ofstream out("testfile.txt");
	out.close();
	Repository rep{ "testfile.txt" };
	Movie m1{ 1,"tt","gn",2015,"pp" };
	Movie m2{ 2,"ta","gv",2011,"pk" };
	rep.repo_add_movie(m1);
	rep.repo_add_movie(m2);
	rep.repo_delete_movie(m1);
	auto all = rep.repo_get_all_movies();
	assert(all.size() == 1);

	try
	{
		rep.repo_delete_movie(m1);
		assert(false);
	}
	catch (RepoException ex)
	{
		assert(true);
		assert(ex.get_exception_message() == "Inexistent movie!\n");
	}
}

void test_repo_update()
{
	ofstream out("testfile.txt");
	out.close();
	Repository rep{ "testfile.txt" };
	Movie m1{ 1,"tt","gn",2015,"pp" };
	Movie m2{ 1,"ta","gv",2011,"pk" };
	rep.repo_add_movie(m1);
	rep.repo_update_movie(m2);
	auto all = rep.repo_get_all_movies();
	auto movie = all.at(0);
	assert(movie.get_id() == 1);
	assert(movie.get_title() == "ta");
	assert(movie.get_genre() == "gv");
	assert(movie.get_year() == 2011);
	assert(movie.get_protagonist() == "pk");

	Movie m3{ 3,"tb","gu",2017,"pr" };
	try
	{
		rep.repo_update_movie(m3);
		assert(false);
	}
	catch (RepoException ex)
	{
		assert(true);
		assert(ex.get_exception_message() == "Inexistent movie!\n");
	}
	
}

void test_repo_find()
{
	ofstream out("testfile.txt");
	out.close();
	Repository rep{ "testfile.txt" };
	Movie m1{ 1,"tt","gn",2015,"pp" };
	rep.repo_add_movie(m1);
	auto movie = rep.repo_find_movie(m1);
	assert(movie.get_id() == 1);
	assert(m1.get_title() == "tt");
	assert(m1.get_genre() == "gn");
	assert(m1.get_year() == 2015);
	assert(m1.get_protagonist() == "pp");
	
	Movie m2{ 2,"ta","gb",2019,"pc" };

	try
	{
		auto mv = rep.repo_find_movie(m2);
		assert(false);
	}
	catch (RepoException ex)
	{
		assert(true);
		assert(ex.get_exception_message() == "Inexistent movie!\n");
	}
	
}

void test_service_add()
{
	ofstream out("testfile.txt");
	out.close();
	Repository rep{ "testfile.txt" };
	Validator val;
	Service serv{ rep,val };
	serv.service_add_movie(1, "ta", "gb", 2014, "pc");
	auto all = serv.service_get_all_movies();
	assert(all.size() == 1);
}

void test_service_delete()
{
	ofstream out("testfile.txt");
	out.close();
	Repository rep{ "testfile.txt" };
	Validator val;
	Service serv{ rep,val };
	serv.service_add_movie(1, "ta", "gb", 2014, "pc");
	serv.service_add_movie(2, "tb", "gc", 2014, "pd");
	auto all = serv.service_get_all_movies();
	assert(all.size() == 2);
	serv.service_delete_movie(1);
	all = serv.service_get_all_movies();
	assert(all.size() == 1);
}

void test_service_update()
{
	ofstream out("testfile.txt");
	out.close();
	Repository rep{ "testfile.txt" };
	Validator val;
	Service serv{ rep,val };
	serv.service_add_movie(1, "ta", "gb", 2014, "pc");
	serv.service_update_movie(1, "tx", "gy", 2019, "pz");
	auto all = serv.service_get_all_movies();
	auto movie = all.at(0);
	assert(movie.get_id() == 1);
	assert(movie.get_title() == "tx");
	assert(movie.get_genre() == "gy");
	assert(movie.get_year() == 2019);
	assert(movie.get_protagonist() == "pz");
}

void test_service_find()
{
	ofstream out("testfile.txt");
	out.close();
	Repository rep{ "testfile.txt" };
	Validator val;
	Service serv{ rep,val };
	serv.service_add_movie(1, "ta", "gb", 2014, "pc");
	auto movie = serv.service_find_movie(1);
	assert(movie.get_id() == 1);
}

void test_undo()
{
	ofstream out("testfile.txt");
	out.close();
	Repository rep{ "testfile.txt" };
	Validator val;
	Service serv{ rep,val };
	serv.service_add_movie(1, "ta", "gb", 2014, "pc");
	auto movie = serv.service_find_movie(1);
	assert(movie.get_id() == 1);
	serv.undo();
	try
	{
		movie = serv.service_find_movie(1);
		assert(false);
	}
	catch (RepoException ex)
	{
		assert(true);
		assert(ex.get_exception_message() == "Inexistent movie!\n");
	}

	serv.service_add_movie(2, "th", "gj", 2011, "pk");
	serv.service_delete_movie(2);
	serv.undo();

	try
	{
		movie = serv.service_find_movie(2);
		assert(true);
	}
	catch (RepoException ex)
	{
		assert(false);
	}
	
}

void test_cart()
{
	ofstream out("testfile.txt");
	out.close();
	Repository rep{ "testfile.txt" };
	Cart cart{ rep };
	Movie m1{ 1,"ta","gb",2016,"pc" };
	Movie m2{ 2,"tb","gc",2018,"pd" };
	Movie m3{ 3,"tc","gd",2020,"pe" };
	cart.add_in_cart(m1);
	auto all = cart.get_all_from_cart();
	assert(all.size() == 1);
	cart.clear_cart();
	all = cart.get_all_from_cart();
	assert(all.size() == 0);
	vector<Movie> movies;
	rep.repo_add_movie(m1);
	rep.repo_add_movie(m2);
	rep.repo_add_movie(m3);
	cart.generate_cart(2);
	all = cart.get_all_from_cart();
	assert(all.size() == 2);
}

void test_service_cart()
{
	ofstream out("testfile.txt");
	out.close();
	Repository rep{ "testfile.txt" };
	Validator val;
	Service serv{ rep,val };
	serv.service_add_movie(1, "ta", "gb", 2016, "pc");
	serv.service_add_movie(2, "tb", "gc", 2018, "pd");
	serv.service_add_movie(3, "tc", "gd", 2020, "pe");
	serv.service_add_in_cart(1);
	auto all_cart = serv.service_get_all_from_cart();
	assert(all_cart.size() == 1);
	serv.service_clear_cart();
	all_cart = serv.service_get_all_from_cart();
	assert(all_cart.size() == 0);
	serv.service_add_random_in_cart(2);
	all_cart = serv.service_get_all_from_cart();
	assert(all_cart.size() == 2);

	serv.export_cart_to_csv("testcsv.csv");
	ifstream in("testcsv.csv");
	assert(in.is_open());
	int count_lines = 0;
	while (!in.eof())
	{
		string line;
		in >> line;
		count_lines++;
	}
	in.close();
	assert(count_lines == 2+1);
}

void test_filter_by_protagonist()
{
	ofstream out("testfile.txt");
	out.close();
	Repository rep{ "testfile.txt" };
	Validator val;
	Service serv{ rep,val };
	serv.service_add_movie(1, "ta", "gb", 2016, "pc");
	serv.service_add_movie(2, "tb", "gc", 2018, "pd");
	serv.service_add_movie(3, "tc", "gd", 2020, "pe");
	auto all = serv.filter_by_protagonist("p");
	assert(all.size() == 3);
}

void test_sort_by_title()
{
	ofstream out("testfile.txt");
	out.close();
	Repository rep{ "testfile.txt" };
	Validator val;
	Service serv{ rep,val };
	serv.service_add_movie(1, "tc", "gb", 2016, "pc");
	serv.service_add_movie(2, "tb", "gc", 2018, "pd");
	serv.service_add_movie(3, "ta", "gd", 2020, "pe");
	auto all = serv.sort_by_title();
	assert(all.at(0).get_id() == 3);
	assert(all.at(1).get_id() == 2);
	assert(all.at(2).get_id() == 1);
}

void test_get_all_genres()
{
	ofstream out("testfile.txt");
	out.close();
	Repository rep{ "testfile.txt" };
	Validator val;
	Service serv{ rep,val };
	serv.service_add_movie(1, "tc", "gb", 2016, "pc");
	serv.service_add_movie(2, "tb", "gc", 2018, "pd");
	serv.service_add_movie(3, "ta", "gb", 2020, "pe");
	serv.service_add_movie(4, "tf", "gt", 2019, "pg");
	auto all_genres = serv.get_all_genres();
	assert(all_genres.size() == 3);
}

void test_repository()
{
	test_repo_add();
	test_repo_delete();
	test_repo_update();
	test_repo_find();
}

void test_service()
{
	test_service_add();
	test_service_delete();
	test_service_update();
	test_service_find();
	test_undo();
	test_service_cart();
	test_sort_by_title();
	test_filter_by_protagonist();
	test_get_all_genres();
}

void test_all()
{
	test_domain();
	test_repository();
	test_service();
	test_cart();
}