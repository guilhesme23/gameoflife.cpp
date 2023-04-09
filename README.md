# Game of Life

Implementation of the famous celullar automata *Game of Life* in C++ using SFML and Dear ImGUI.

Conway's Game of Life is a Celullar Automata in a 2D grid that have simple rules:

- Each cell is either alive or dead
- Any living cell with more than 3 neighbors dies of super population
- Any dead cell with exactly 3 neighbors becomes alive
- Any cell  with less than 2 neighbors dies of isolation
- Any living cell with 2 or 3 neighbors carry on to the next generation

## Dependencies

- CMake
- SFML

## Quickstart

```Bash
mkdir build
cd build
cmake .. && make
./gameoflife
```