#include "TargetGenerator.hpp"

TargetGenerator::TargetGenerator() {}

TargetGenerator::~TargetGenerator() {
	vector<ATarget*>::iterator ite = this->targets.end();
	for (vector<ATarget*>::iterator it = this->targets.begin(); it != ite; ++it) {
		delete (*it);
	}
	this->targets.clear();
}

void	TargetGenerator::learnTargetType(ATarget *target) {
	if (!target)
		return;
	vector<ATarget*>::iterator ite = this->targets.end();
	for (vector<ATarget*>::iterator it = this->targets.begin(); it != ite; ++it)
		if (target->getType() == (*it)->getType())
			return;
	this->targets.push_back(target->clone());
}

void	TargetGenerator::forgetTargetType(string const &type) {
	vector<ATarget*>::iterator ite = this->targets.end();
	for (vector<ATarget*>::iterator it = this->targets.begin(); it != ite; ++it) {
		if (type == (*it)->getType()) {
			delete (*it);
			it = targets.erase(it);
			return;
		}
	}
}

ATarget	*TargetGenerator::createTarget(string const &type) {
	vector<ATarget*>::iterator ite = this->targets.end();
	for (vector<ATarget*>::iterator it = this->targets.begin(); it != ite; ++it) {
		if (type == (*it)->getType()) {
			return (*it);
		}
	}
	return NULL;
}

