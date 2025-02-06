#include "Present.h"

class FreezeGuard : public Present {
public:
	FreezeGuard(); 
	char getSymbol() const override; 
};
