#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <thread>
#include <vector>

#include "../lib/imgui/imgui-SFML.h"
#include "../lib/imgui/imgui.h"

const int WIDTH = 1280, HEIGHT = 920;

struct Cell {
  int x;
  int y;
  sf::RectangleShape shape;
  bool alive;
};

using cell_vec = std::vector<std::vector<Cell>>;

class Life {
 private:
  cell_vec cells;
  int scale, rows, cols;

  int countNeighbors(Cell c) {
    int total = 0;
    for (auto i = c.y - 1; i <= c.y + 1; i++) {
      int di = (i + rows) % rows;
      for (auto j = c.x - 1; j <= c.x + 1; j++) {
        int dj = (j + cols) % cols;
        if (i == c.y && j == c.x) continue;

        if (cells[di][dj].alive) total += 1;
      }
    }

    return total;
  }

  cell_vec buildGen() {
    double r;
    cell_vec generation;
    // Setup cells
    for (auto i = 0; i < rows; ++i) {
      generation.push_back(std::vector<Cell>());
      for (auto j = 0; j < cols; ++j) {
        r = ((double)std::rand() / (double)RAND_MAX);
        Cell c{
          x : j,
          y : i,
          shape : sf::RectangleShape(sf::Vector2f((float)scale, (float)scale)),
          alive : (r < 0.65) ? true : false
        };
        c.shape.setFillColor(sf::Color::Yellow);
        c.shape.setPosition(sf::Vector2f(j * scale, i * scale));
        generation[i].push_back(c);
      }
    }

    return generation;
  }

  void evaluateSlice(int begin, int end, cell_vec& slice, cell_vec& result) {
    std::cout << "Thread at: " << begin << " - :)\n";
    for (auto i = begin; i < end; i++) {
      result[i] = std::vector<Cell>();
      for (auto cell : slice[i]) {
        auto neighbors = countNeighbors(cell);
        Cell c = {
          x : cell.x,
          y : cell.y,
          shape : cell.shape,
          alive : cell.alive
        };

        if (neighbors == 3 && !cell.alive) {
          c.alive = true;
        } else if (neighbors < 2) {
          c.alive = false;
        } else if (neighbors > 3) {
          c.alive = false;
        }

        result[c.y].push_back(c);
      }
    }
  }

 public:
  Life(const int& w, const int& h, const int& s) {
    scale = s;
    rows = h / scale;
    cols = w / scale;
    cells = buildGen();
  }

  void evaluateGen() {
    cell_vec nextGen;
    nextGen.resize(rows);

    int half = (int)rows / 2;
    std::thread worker1(&Life::evaluateSlice, this, 0, half, std::ref(cells), std::ref(nextGen));
    std::thread worker2(&Life::evaluateSlice, this, half, rows, std::ref(cells), std::ref(nextGen));

    worker1.join();
    worker2.join();

    cells = nextGen;
  }

  void reset() {
    cells = buildGen();
  }

  void draw(sf::RenderWindow& win) {
    for (auto row : cells) {
      for (auto cell : row) {
        if (cell.alive) win.draw(cell.shape);
      }
    }
  }
};

void handleEvents(sf::RenderWindow& win) {
  sf::Event e;
  while (win.pollEvent(e)) {
    ImGui::SFML::ProcessEvent(win, e);
    switch (e.type) {
      case sf::Event::Closed:
        win.close();
        break;
      default:
        break;
    }
  }
}

bool menuWindow(bool& pause, Life& game) {
  ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize;
  bool open = false;
  ImGui::Begin("Menu", &open, flags);
  ImGui::Text("Controls:");
  std::string btnText = (!pause) ? "Pause" : "Play";
  if (ImGui::Button(btnText.c_str())) pause = !pause;
  if (ImGui::Button("Reset Board")) game.reset();
  ImGui::End();

  return pause;
}

int main() {
  sf::RenderWindow win(sf::VideoMode(WIDTH, HEIGHT), "Game Of Life");
  ImGui::SFML::Init(win);

  std::srand(std::time(0));
  Life game(WIDTH, HEIGHT, 3);

  std::cout << "Starting application..." << std::endl;
  sf::Clock deltaClock;
  bool pause = false;

  while (win.isOpen()) {
    handleEvents(win);
    ImGui::SFML::Update(win, deltaClock.restart());
    win.clear();
    game.draw(win);
    if (!pause) game.evaluateGen();

    menuWindow(pause, game);
    ImGui::SFML::Render(win);
    win.display();
  }

  ImGui::SFML::Shutdown();
  return 0;
}