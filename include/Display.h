#pragma once
#include <SFML/Graphics.hpp>

// Base Class: Display
class Display {
public:
    virtual void show() = 0;       // Pure virtual for derived classes
    virtual int handleInput() = 0; // Pure virtual for input handling
    virtual ~Display() = default; // Virtual destructor for cleanup
};
