#include "SpellBook.hpp"

SpellBook::SpellBook() {}

SpellBook::~SpellBook() {
	vector<ASpell*>::iterator ite = this->spells.end();
	for(vector<ASpell*>::iterator it = this->spells.begin(); it != ite; ++it) {
		delete (*it);
	}
	this->spells.clear();
}

SpellBook::SpellBook(SpellBook const &copy) {}

SpellBook	const &SpellBook::operator=(SpellBook const &other) {
	return (*this);
}

void	SpellBook::learnSpell(ASpell *spell) {
	if (!spell)
		return;
	vector<ASpell*>::iterator ite = this->spells.end();
	for(vector<ASpell*>::iterator it = this->spells.begin(); it != ite; ++it) {
		if ((*it)->getName() == spell->getName())
			return;
	}
	this->spells.push_back(spell->clone());
}

void	SpellBook::forgetSpell(string const &name) {
	vector<ASpell*>::iterator ite = this->spells.end();
	for(vector<ASpell*>::iterator it = this->spells.begin(); it != ite; ++it) {
		if ((*it)->getName() == name) {
			delete (*it);
			it = this->spells.erase(it);
			return;
		}
	}
}

ASpell*	SpellBook::createSpell(string const &name) {
	vector<ASpell*>::iterator ite = this->spells.end();
	for(vector<ASpell*>::iterator it = this->spells.begin(); it != ite; ++it) {
		if ((*it)->getName() == name) {
			return (*it);
		}
	}
	return NULL;
}

