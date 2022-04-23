#include "Polymorph.hpp"

ASpell	*Polymorph::clone() const {
	return (new Polymorph(*this));
}
