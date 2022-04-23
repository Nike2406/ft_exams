#include "BrickWall.hpp"

ATarget	*BrickWall::clone() const {
	return (new BrickWall(*this));
}
