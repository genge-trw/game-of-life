# Conway's Game of Life

This is an implementation of Conway's Game of Life, a zero-player game, built with C++ and SDL2.

## What is Conway's Game of Life?

Conway's Game of Life is a cellular automaton devised by the British mathematician John Horton Conway in 1970. It is a zero-player game, meaning that its evolution is determined by its initial state, requiring no further input. One interacts with the Game of Life by creating an initial configuration and observing how it evolves.

## Features

*   **Simulation:** Implements the core rules of Conway's Game of Life.
*   **Graphical Display:** Renders the game grid and cell states using SDL2.
*   **User Interaction:**
    *   Toggle cell states with mouse clicks.
    *   Control simulation flow (start/pause, reset, step-by-step) with keyboard inputs.
*   **Random Initialization:** Start with a random pattern.

## Technologies Used

*   **C++17:** For the game logic and application structure.
*   **SDL2:** For graphics rendering, window management, and event handling.

## Build Instructions

To build this project, you need a C++ compiler (like g++) and SDL2 development libraries installed on your system. The `Makefile` is configured for a Linux/Termux environment where SDL2 headers are typically found in `/data/data/com.termux/files/usr/include/SDL2` and libraries are linked with `-lSDL2`.

1.  Navigate to the project root directory:

    ```bash
    cd /data/data/com.termux/files/home/Desktop/Projects/Tutorials/07
    ```

2.  Run `make` to compile the project:

    ```bash
    make
    ```

    This will create an executable named `game_of_life` in the project root.

## How to Run

After successful compilation, you can run the application from the project root directory:

```bash
./game_of_life
```

## Controls

*   **Spacebar:** Toggles the simulation between running and paused states.
*   **R:** Resets the entire grid, making all cells dead.
*   **N:** Advances the simulation by one step (only works when the simulation is paused).
*   **I:** Initializes the grid with a new random pattern.
*   **Left Mouse Click:** Toggles the state (alive/dead) of the cell at the clicked position.
