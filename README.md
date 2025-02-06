# Bomberman Game - Romi Sinizkey & Or-ram Atar

## Introduction
Bomberman Game is an engaging and strategic maze-based game developed in C++ using the SFML (Simple and Fast Multimedia Library) for graphics rendering. The player navigates through multiple levels filled with obstacles, enemies, and power-ups while aiming to reach the exit door. The game requires quick thinking and strategic placement of bombs to overcome challenges and advance.

## Game Overview
In this game, the player controls a Bomberman character, maneuvering through complex maze layouts while avoiding enemy guards, collecting items, and utilizing power-ups. Each level introduces new challenges that demand tactical movement and decision-making.

## Features
- **Intuitive Controls**: Navigate using keyboard arrow keys.
- **Dynamic Collision Detection**: Ensures realistic interactions between the player, obstacles, and enemies.
- **Diverse Game Objects**: Includes walls, rocks, doors, coins, power-ups, and guards.
- **Scoring System**: Tracks progress based on eliminated guards and collected items.
- **Immersive Audio**: Integrated sound effects and background music enhance gameplay.
- **User Interface**: Includes buttons for game control, help menu, and navigation.
- **AI-Driven Guards**: Intelligent enemy movement enhances the challenge.
- **Multiple Levels**: Progressive difficulty with new obstacles and power-ups.

## Game Elements
- **Bomberman**: The player-controlled character navigating the maze.
- **Guards**: Enemies that chase the player and reduce health upon contact.
- **Door**: The exit point to advance to the next level.
- **Coins**: Provide extra points to the player.
- **Presents (Power-ups)**: Random bonuses that enhance gameplay, including:
  - Freezing guards
  - Extra life
  - Extra time
  - Removing a random guard

## Code Structure

### Header Files
- **board.h**: Manages level loading and board structure.
- **bombs.h**: Defines the `Bombs` class, enabling destruction of obstacles and guards.
- **door.h**: Defines the `Door` class, handling level transitions.
- **freezingGuards.h**: Implements the `Freeze` class for temporary enemy freezing.
- **gameManager.h**: Controls the core game logic and state management.
- **gameObjects.h**: Base class for all in-game objects.
- **guard.h**: Implements the `Guard` class, governing enemy behavior.
- **smart_guard.h**: Implements a pathfinding AI that moves towards the player.
- **stupid_guard.h**: Implements random movement behavior for less predictable AI.
- **increasingLife.h**: Manages the `Medkit` class, which grants extra lives.
- **mainMenuDisplay.h**: Defines the `Menu` class for user interface interactions.
- **robot.h**: Implements the `Player` class, managing movement and actions.
- **removingGuard.h**: Defines the `RemovingGuard` class, allowing the elimination of guards.
- **ToolbarGame.h**: Displays game statistics at the top of the board.
- **resourcesManager.h**: Loads and manages game assets.
- **rock.h**: Defines the `Rock` class, acting as obstacles.
- **coin.h**: Defines the `Coin` class, providing points to the player.
- **wall.h**: Defines the `Wall` class, serving as immovable barriers.
- **Present.h**: Base class for power-up presents, managing shared functionality.

### Source Files
Each `.cpp` file implements the functionality defined in its corresponding header file, including object behavior, interactions, and rendering logic.

## Algorithms
- **Guard Movement Algorithm**:
  - Smart guards use AI pathfinding techniques to chase the player.
  - Stupid guards move randomly, adding unpredictability.
- **Collision Detection Algorithm**: Implements double dispatch to dynamically handle interactions between different objects.

## Object-Oriented Design
- **GameObjects (Base Class)**: Serves as the parent class for all game objects.
  - Inherited by: `Bombs`, `Door`, `Explosion`, `Freeze`, `Guard`, `Present`, `Player`, `RemovingGuard`, `Rock`, `Coin`, and `Wall`.
- **MovingObjects (Dynamic Objects)**: Handles dynamic game elements.
  - Includes: `Bombs`, `Guard`, `Player`.

## Adding New Levels
To introduce a new level, create a file named `Level[number].txt` with the following symbols:

```
/ - Bomberman (Player)
! - Guard (Enemy)
- - Water Gun (Removes a guard)
@ - Rock (Obstacle)
# - Wall (Barrier)
' ' - Present (Generates a random gift as mentioned above)
' ' - Coin (Provides extra points)
```

## Future Enhancements
- **Multiplayer Mode**: Implementing a two-player cooperative or competitive mode.
- **New Power-ups**: Adding new bonuses to diversify gameplay.
- **More Intelligent AI**: Enhancing enemy movement and strategy.
- **Graphical Improvements**: Improving animations and UI design.

## Credits
- **Developers**: Romi Sinizkey & Or-ram Atar
- **Sound Effects**: Sourced from YouTube & Pixabay
- **Inspiration**: Based on the classic **Bomberman** series

## License
This project is part of Hadassah Academic College coursework and is the intellectual property of **Romi Sinizkey & Or-ram Atar**. Redistribution or modification without permission is prohibited.

