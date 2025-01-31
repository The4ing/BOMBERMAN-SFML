#include "Present.h"

class RemovedGuard : public Present {
public:
    RemovedGuard(); // Pass by reference


    char getSymbol() const override; // Unique symbol

};
