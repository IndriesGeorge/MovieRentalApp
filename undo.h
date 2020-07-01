#include "Movie.h"
#include "Repository.h"

// Abstract Class
class UndoAction
{
public:
	// pure virtual method 
	virtual void doUndo() = 0;
	// We need virtual destructor to make sure that destructor is called properly from other derived classes 
	virtual ~UndoAction() = default;
};

/*
	When we do undo to add, we want to delete the last added movie(the opposite action)
*/
class UndoAdd : public UndoAction
{
	Repository& rep;
	Movie added_movie;
	
public:

	UndoAdd(Repository& rep, const Movie& m) :rep{ rep }, added_movie{ m }{}

	void doUndo() override
	{
		rep.repo_delete_movie(added_movie);
	}

};

/*
	When we do undo to delete, we want to add the last deleted movie
*/
class UndoDelete : public UndoAction
{
	Repository& rep;
	Movie deleted_movie;

public:

	UndoDelete(Repository& rep, const Movie& m) :rep{ rep }, deleted_movie{ m }{}

	void doUndo() override
	{
		rep.repo_add_movie(deleted_movie);
	}

};

/*
	When we do undo to update, we want to update again a movie with the old one
*/
class UndoUpdate : public UndoAction
{
	Repository& rep;
	Movie updated_movie;

public:

	UndoUpdate(Repository& rep, const Movie& m) :rep{ rep }, updated_movie{ m }{}

	void doUndo() override
	{
		rep.repo_update_movie(updated_movie);
	}

};