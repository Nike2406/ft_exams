#include "Fireball.hpp"

ASpell	*Fireball::clone() const {
	return (new Fireball(*this));
}
