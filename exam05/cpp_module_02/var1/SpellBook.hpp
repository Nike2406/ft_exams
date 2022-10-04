#pragma	once

#include <vector>
#include "ASpell.hpp"

using std::vector;

class SpellBook
{
private:
	vector<ASpell*>	spells;

	SpellBook(SpellBook const &copy);
	SpellBook	const &operator=(SpellBook const &other);
public:
	SpellBook();
	~SpellBook();

	void	learnSpell(ASpell *spell);
	void	forgetSpell(string const &name);
	ASpell*	createSpell(string const &name);
};