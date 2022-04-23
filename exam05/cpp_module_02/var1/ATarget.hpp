#pragma	once

#include <iostream>
#include <string>
#include "ASpell.hpp"

using std::cout;
using std::endl;
using std::string;

class ASpell;

class ATarget
{
protected:
	string	_type;
public:
	ATarget(string const &type);
	virtual ~ATarget();
	ATarget(ATarget const &copy);
	ATarget	const &operator=(ATarget const &other);

	string	const &getType() const;

	virtual ATarget	*clone() const = 0;

	void	getHItBySpell(ASpell const &spell) const;
};

