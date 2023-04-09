# Game of Life

Implementation of the famous celullar automata *Game of Life* in C++ using [SFML](https://www.sfml-dev.org/index.php) and [Dear ImGUI](https://github.com/ocornut/imgui).

Conway's Game of Life is a Celullar Automata in a 2D grid that have simple rules:

- Each cell is either alive or dead
- Any living cell with more than 3 neighbors dies of super population
- Any dead cell with exactly 3 neighbors becomes alive
- Any cell  with less than 2 neighbors dies of isolation
- Any living cell with 2 or 3 neighbors carry on to the next generation

## Dependencies

- [CMake](https://cmake.org/)
- [SFML](https://www.sfml-dev.org/index.php)
- [Dear ImGUI](https://github.com/ocornut/imgui)
- [ImGUI-SFML](https://github.com/SFML/imgui-sfml)

## Quickstart

```Bash
mkdir build
cd build
cmake .. && make
./gameoflife
```

## Next Steps

- [x] Add Dear ImGUI for interactivity (Pause execution, reset board, etc)
- [ ] Add concurrency for better performance
- [ ] Record generations in a GIF File
- [ ] Run program using opengl
- [ ] Use a shader to calculate generations
- [ ] Add camera and procedural world