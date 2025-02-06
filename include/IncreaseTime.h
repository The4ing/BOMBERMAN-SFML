#include "Present.h"

class IncreaseTime : public Present {
public:
    IncreaseTime();
    char getSymbol() const override;// Unique symbol
};
