#pragma	once

#include <iostream>
#include <string>
#include <vector>
#include "ATarget.hpp"

using std::cout;
using std::endl;
using std::string;
using std::vector;

class TargetGenerator
{
private:
	string	_name;
	string	_title;

	vector<ATarget*>	targets;

	TargetGenerator(TargetGenerator const &copy);
	TargetGenerator	const &operator=(TargetGenerator const &other);
public:
	TargetGenerator();
	~TargetGenerator();

	void	learnTargetType(ATarget *target);
	void	forgetTargetType(string const &type);
	ATarget	*createTarget(string const &type);
};