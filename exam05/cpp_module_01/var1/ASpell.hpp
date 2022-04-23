#pragma	once

#include <iostream>
#include <string>
#include "ATarget.hpp"

using std::cout;
using std::endl;
using std::string;

class ATarget;

class ASpell
{
protected:
	string	_name;
	string	_effects;
public:
	ASpell(string const &name, string const &effects);
	virtual ~ASpell();
	ASpell(ASpell const &copy);
	ASpell	const &operator=(ASpell const &other);

	string	const &getName() const;
	string	const &getEffects() const;

	virtual ASpell	*clone() const = 0;

	void	launch(ATarget const &target) const;
};

