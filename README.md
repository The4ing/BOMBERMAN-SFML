# Bomberman Game - Romi Sinizkey & Or-ram Atar

## Introduction
Bomberman Game is an exciting maze-based strategy game where the player navigates through various levels, overcoming obstacles and avoiding guards while aiming to reach the exit door. The game is developed in C++ using the SFML (Simple and Fast Multimedia Library) for graphics rendering.

## Game Overview
In this game, the player controls a Bomberman character who must strategically traverse complex maze layouts, evade enemy guards, and utilize power-ups to enhance gameplay. Each level presents increasing challenges, requiring quick thinking and tactical movement.

## Features
- **Intuitive Controls**: Navigate the Bomberman using keyboard arrow keys.
- **Dynamic Collision Detection**: Ensures realistic interactions between the player, obstacles, and enemies.
- **Diverse Game Objects**: Includes walls, rocks, doors, medkits, power-ups, and guards.
- **Scoring System**: Tracks progress based on eliminated guards and collected items.
- **Immersive Audio**: Integrated sound effects and background music.
- **User Interface**: Includes buttons for game control, help menu, and navigation.

## Game Elements
- **Bomberman**: The player-controlled character navigating the maze.
- **Guards**: Enemies that chase the player and reduce health upon contact.
- **Door**: The exit point to advance to the next level.
- **Present**: Give the player a gift - freezes the Guards/extra life/extra time/ remove random guard.

## Code Structure

### Header Files
- **board.h**: Handles level loading and board management.
- **bombs.h**: Defines the `Bombs` class, allowing the player to destroy obstacles and guards.
- **const.h**: Stores game constants.
- **door.h**: Defines the `Door` class, managing level transitions.
- **explosion.h**: Implements the `Explosion` class for bomb detonations.
- **freezingGuards.h**: Defines the `Freeze` class for temporary enemy freezing.
- **gameController.h**: Controls the core game logic and flow.
- **gameObjects.h**: Serves as the base class for all in-game objects.
- **guard.h**: Implements the `Guard` class, governing enemy behavior.
- **increasingLife.h**: Manages the `Medkit` class, which provides extra lives.
- **menu.h**: Defines the `Menu` class for user interface interactions.
- **player.h**: Implements the `Player` class, managing character movement and actions.
- **removingGuard.h**: Defines the `RemovingGuard` class, responsible for eliminating guards.
- **resourcesManager.h**: Loads and manages game resources.
- **rock.h**: Represents the `Rock` class, acting as obstacles.
- **scoreBoard.h**: Tracks player score, level progress, and remaining time.
- **staticObjects.h**: Defines static objects that do not move.
- **updateableObjects.h**: Serves as the base class for dynamic objects.
- **wall.h**: Represents the `Wall` class, defining immovable barriers.

### Source Files
Each `.cpp` file implements the corresponding header functionality, defining object behaviors, interactions, and rendering logic.

## Algorithms
- **Guard Movement Algorithm**: Guards use a simple AI pathfinding technique to chase the player, prioritizing movement along the shortest axis.
- **Collision Detection Algorithm**: Implements double dispatch to handle interactions between different objects dynamically.

## Object-Oriented Design
- **GameObjects (Base Class)**: Serves as the parent for all game objects.
  - Inherited by: `Bombs`, `Door`, `Explosion`, `Freeze`, `Guard`, `IncreasingLife`, `Medkit`, `Player`, `RemovingGuard`, `Rock`, and `Wall`.
- **UpdateableObjects (Dynamic Objects)**: Handles moving game elements.
  - Includes: `Bombs`, `Guard`, `Player`, `Explosion`.
- **StaticObjects (Fixed Objects)**: Represents objects that remain stationary.
  - Includes: `Door`, `Freeze`, `IncreasingLife`, `Medkit`, `RemovingGuard`, `Rock`, `Wall`.

## Adding New Levels
To introduce a new level, create a file named `Level[number].txt` with the following symbols:

```
/ - Bomberman (Player)
! - Guard (Enemy)
- - Water Gun (Removes a guard)
@ - Rock (Obstacle)
# - Wall (Barrier)
' ' - Present (generate random gift as mentioned)
' ' - Coins that give the player points 
```

## Credits
- Developed by **Romi Sinizkey & Or-ram Atar**.
- Sound effects sourced from **YouTube & Pixabay**.
- Special thanks to **Michal Merkin & Yehezkel Bernat** for guidance and feedback.
- Inspired by the classic **Bomberman** series.

## License
This project is part of Hadassah Academic College coursework and is the intellectual property of **Noam Mazouz & Ofek Cohen**.

