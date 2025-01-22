#pragma once
class GameObject {
public:
    virtual char getSymbol() const = 0; // Abstract method for getting symbol representation
    virtual ~GameObject() = default;    // Virtual destructor


};

