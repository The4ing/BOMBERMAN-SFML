#pragma once

#include "Display.h"

// Derived Class: SettingsDisplay
class SettingsDisplay : public Display {
public:
    SettingsDisplay(sf::RenderWindow* window);
    void show() override;          // Render the settings screen
    void handleInput() override;   // Handle input in the settings

private:
    sf::RenderWindow* m_window;

};

