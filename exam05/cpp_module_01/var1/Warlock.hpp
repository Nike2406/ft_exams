#pragma	once

#include <iostream>
#include <string>
#include <vector>
#include "ASpell.hpp"
#include "ATarget.hpp"

using std::cout;
using std::endl;
using std::string;
using std::vector;

class Warlock
{
private:
	string	_name;
	string	_title;
	vector<ASpell*>	spells;

	Warlock();
	Warlock(Warlock const &copy);
	Warlock	const &operator=(Warlock const &other);
public:
	Warlock(string const &name, string const &title);
	~Warlock();

	string	const &getName() const;
	string	const &getTitle() const;

	void	setTitle(string const &newTitle);

	void	introduce() const;

	void	learnSpell(ASpell *spell);
	void	forgetSpell(string const &name);
	void	launchSpell(string const &name, ATarget const &target);
};