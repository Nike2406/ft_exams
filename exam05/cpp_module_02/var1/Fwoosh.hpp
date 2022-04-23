#include "ASpell.hpp"

class Fwoosh: public ASpell
{
public:
	Fwoosh();
	virtual ~Fwoosh();

	virtual ASpell	*clone() const;
};

