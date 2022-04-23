#include "ATarget.hpp"

ATarget::ATarget(string const &type)
	: _type(type) {}

ATarget::~ATarget() {}

ATarget::ATarget(ATarget const &copy)
	: _type(copy._type) {}

ATarget	const &ATarget::operator=(ATarget const &other) {
	this->_type = other._type;
	return (*this);
}

string	const &ATarget::getType() const {
	return this->_type;
}

void	ATarget::getHItBySpell(ASpell const &spell) const {
	cout << _type << " has been " << spell.getEffects() << "!\n";
}
