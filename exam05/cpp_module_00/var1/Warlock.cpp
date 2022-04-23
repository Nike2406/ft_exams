#include "Warlock.hpp"

Warlock::Warlock(string const &name, string const &title)
	: _name(name), _title(title) {
		cout << _name << ": This looks like another boring day.\n";
	}

Warlock::~Warlock() {
		cout << _name << ": My job here is done!\n";
}

Warlock::Warlock(Warlock const &copy)
	: _name(copy._name), _title(copy._title) {}

Warlock	const &Warlock::operator=(Warlock const &other) {
	this->_name = other._name;
	this->_title = other._title;
	return (*this);
}

string	const &Warlock::getName() const {
	return this->_name;
}

string	const &Warlock::getTitle() const {
	return this->_title;
}

void	Warlock::setTitle(string const &newTitle) {
	this->_title = newTitle;
}

void	Warlock::introduce() const {
	cout << _name << ": I am " << _name << ", " << _title << "!\n";
}

