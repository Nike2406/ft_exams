#pragma once

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

class Warlock
{
private:
	string	_name;
	string	_title;
public:
	Warlock(string const &name, string const &title);
	~Warlock();
	Warlock(Warlock const &copy);
	Warlock	const& operator=(Warlock const &);

	string	const &getName() const;
	string	const &getTitle() const;

	void	setTitle(string const &newTitle);

	void	introduce() const;
};

