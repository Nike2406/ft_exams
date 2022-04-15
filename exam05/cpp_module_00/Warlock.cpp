#include "Warlock.hpp"


Warlock::Warlock(string const &name, string const &title)
	: _name(name), _title(title)
{
	cout << this->getName() << ": This looks like another boring day." << endl;
}

Warlock::~Warlock()
{
	cout << this->getName() << ": My job here is done!" << endl;
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
	cout << this->getName() << ": I am " << this->getName() << ", "
	 << this->getTitle() << "!"<< endl;
}