#include "ATarget.hpp"
#include "ASpell.hpp"

ATarget::ATarget(string const &type)
	: _type(type) {}

ATarget::~ATarget() {}

ATarget::ATarget(ATarget const &copy) { *this = copy;}

ATarget const &ATarget::operator=(ATarget const &other) {
	this->_type = other._type;
	return *this;
}

string	const &ATarget::getType() const { return this->_type; }

void	ATarget::getHitBySpell(ASpell const &spell) const {
	cout << this->getType() << " has been " << spell.getEffects() << "!" << endl;
}
