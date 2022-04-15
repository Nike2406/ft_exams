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

void	Warlock::learnSpell(ASpell *spell) {
	if (spell) {
			cout << "Spell " << spell << " learned \n";
		std::vector<ASpell*>::iterator ite = this->spells.end();
		for (std::vector<ASpell*>::iterator it = this->spells.begin(); it != ite; ++it) {
			if ((*it)->getName() == spell->getName())
				return;
			this->spells.push_back(spell->clone());
			cout << "Spell " << spell << " learned \n";
		}
	}
}

void	Warlock::forgetSpell(string const &spell) {
	std::vector<ASpell*>::iterator ite = this->spells.end();
	for (std::vector<ASpell*>::iterator it = this->spells.begin();
	it != ite;
	++it) {
		if ((*it)->getName() == spell) {
			delete *it;
			it = this->spells.erase(it);
		}
	}
}

void	Warlock::launchSpell(string const &spell, ATarget const &target) {
	cout << "try to get " << spell <<endl;
	std::vector<ASpell*>::iterator ite = this->spells.end();
	for (std::vector<ASpell*>::iterator it = this->spells.begin();	it != ite; ++it) {
		cout << "Got " << spell <<endl;
		if ((*it)->getName() == spell) {
			(*it)->launch(target);
			return;
		}
	}
}
