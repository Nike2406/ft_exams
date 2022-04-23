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

void	Warlock::learnSpell(ASpell *spell) {
	if (!spell)
		return;
	vector<ASpell*>::iterator ite = this->spells.end();
	for (vector<ASpell*>::iterator it = this->spells.begin(); it != ite; ++it)
		if (spell->getName() == (*it)->getName())
			return;
	this->spells.push_back(spell);
}

void	Warlock::forgetSpell(string const &name) {
	vector<ASpell*>::iterator ite = this->spells.end();
	for (vector<ASpell*>::iterator it = this->spells.begin(); it != ite; ++it) {
		if (name == (*it)->getName()) {
			delete (*it);
			it = spells.erase(it);
			return;
		}
	}
}

void	Warlock::launchSpell(string const &name, ATarget const &target) {
	ATarget const *tmp = 0;
	if (tmp == &target)
		return;
	vector<ASpell*>::iterator ite = this->spells.end();
	for (vector<ASpell*>::iterator it = this->spells.begin(); it != ite; ++it) {
		if (name == (*it)->getName()) {
			(*it)->launch(target);
			return;
		}
	}
}

