#pragma	once

#include <iostream>
#include <string>
#include <vector>
#include "ASpell.hpp"

using std::cout;
using std::endl;
using std::string;
using std::vector;

class SpellBook
{
private:
	string	_name;
	string	_title;

	vector<ASpell*>	spells;

	SpellBook(SpellBook const &copy);
	SpellBook	const &operator=(SpellBook const &other);
public:
	SpellBook();
	~SpellBook();

	void	learnSpell(ASpell *spell);
	void	forgetSpell(string const &spellName);
	ASpell	*createSpell(string const &spellName);
};