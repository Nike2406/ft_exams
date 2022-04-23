#include "SpellBook.hpp"

SpellBook::SpellBook() {}

SpellBook::~SpellBook() {
	vector<ASpell*>::iterator ite = this->spells.end();
	for (vector<ASpell*>::iterator it = this->spells.begin(); it != ite; ++it) {
		delete (*it);
	}
	this->spells.clear();
}

void	SpellBook::learnSpell(ASpell *spell) {
	if (!spell)
		return;
	vector<ASpell*>::iterator ite = this->spells.end();
	for (vector<ASpell*>::iterator it = this->spells.begin(); it != ite; ++it)
		if (spell->getName() == (*it)->getName())
			return;
	this->spells.push_back(spell->clone());
}

void	SpellBook::forgetSpell(string const &spellName) {
	vector<ASpell*>::iterator ite = this->spells.end();
	for (vector<ASpell*>::iterator it = this->spells.begin(); it != ite; ++it) {
		if (spellName == (*it)->getName()) {
			delete (*it);
			it = spells.erase(it);
			return;
		}
	}
}

ASpell	*SpellBook::createSpell(string const &spellName) {
	vector<ASpell*>::iterator ite = this->spells.end();
	for (vector<ASpell*>::iterator it = this->spells.begin(); it != ite; ++it) {
		if (spellName == (*it)->getName()) {
			return (*it);
		}
	}
	return NULL;
}

