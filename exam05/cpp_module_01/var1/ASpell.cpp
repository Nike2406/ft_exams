#include "ASpell.hpp"

ASpell::ASpell(string const &name, string const &effects)
	: _name(name), _effects(effects) {}

ASpell::~ASpell() {}

ASpell::ASpell(ASpell const &copy)
	: _name(copy._name), _effects(copy._effects){}

ASpell	const &ASpell::operator=(ASpell const &other) {
	this->_name = other._name;
	this->_effects = other._effects;
	return (*this);
}

string	const &ASpell::getName() const {
	return this->_name;
}

string	const &ASpell::getEffects() const {
	return this->_effects;
}

void	ASpell::launch(ATarget const &target) const {
	target.getHItBySpell(*this);
}
