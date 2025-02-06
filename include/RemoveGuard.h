#include "Present.h"

class RemovedGuard : public Present {
public:
    RemovedGuard(); 
    char getSymbol() const override; 
};
