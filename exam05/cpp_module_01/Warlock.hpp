#pragma once

#include "ASpell.hpp"
#include <vector>

class Warlock
{
private:
	string					_name;
	string					_title;

	std::vector<ASpell*>	spells;
public:
	Warlock(string const &name, string const &title);
	~Warlock();
	Warlock(Warlock const &copy);
	Warlock	const& operator=(Warlock const &);

	string	const &getName() const;
	string	const &getTitle() const;

	void	setTitle(string const &newTitle);

	void	introduce() const;

	void	learnSpell(ASpell *spell);
	void	forgetSpell(string const &spell);
	void	launchSpell(string const &spell, ATarget const &target);
};

