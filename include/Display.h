#pragma once
#include <SFML/Graphics.hpp>
const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;
// Base Class: Display
class Display {
public:
    virtual void show() = 0;       // Pure virtual for derived classes
    virtual void handleInput() = 0; // Pure virtual for input handling
    virtual ~Display() = default; // Virtual destructor for cleanup
};
