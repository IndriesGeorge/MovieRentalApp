#pragma once

#include <vector>
#include <algorithm>

using std::vector;

/*
	Abstract Class Observer
	update() - pure virtual method, need to be implemented by observers
*/
class Observer
{
public:
	virtual void update() = 0;
};


/*
	Observable(Subject) - class that notify changes in it's state
	We need to derive from this class if we want to provide notifications
*/
class Observable
{
	vector<Observer*> observers;

public:

	void add_observer(Observer* obs)
	{
		observers.push_back(obs);
	}

	void remove_observer(Observer* obs)
	{
		observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
	}

	void notify()
	{
		for (auto obs : observers)
			obs->update();
	}

};