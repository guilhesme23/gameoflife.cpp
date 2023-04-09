#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

const int WIDTH = 800, HEIGHT = 600;

void handleEvents(sf::RenderWindow& win) {
  sf::Event e;
  while(win.pollEvent(e)) {
    switch(e.type) {
      case sf::Event::Closed:
        win.close();
        break;
      default:
        break;
    }
  }
} 

struct Cell {
  int x;
  int y;
  sf::RectangleShape shape;
  bool alive;
};

class Life {
  private:
    std::vector<std::vector<Cell>> cells;
    int scale, rows, cols;
  public:
    Life(const int& w, const int& h, const int& s) {
      scale = s;
      rows = h / scale;
      cols = w / scale;

      // Setup cells
      for (auto i = 0; i < rows; ++i) {
        cells.push_back(std::vector<Cell>());
        for (auto j = 0; j < cols; ++j) {
          Cell c {
            x: j,
            y: i,
            shape: sf::RectangleShape(sf::Vector2f((float) s, (float) s)),
            alive: true
          };
          c.shape.setFillColor(sf::Color::Yellow);
          c.shape.setPosition(sf::Vector2f(j*s, i*s));
          c.shape.setOutlineThickness(0.5);
          c.shape.setOutlineColor(sf::Color::Red);
          cells[i].push_back(c);
        }
      }
    }

    void draw(sf::RenderWindow& win) {
      for (auto row : cells) {
        for (auto cell : row) {
          if (cell.alive) win.draw(cell.shape);
        }
      }
    }
};

int main() {
  sf::RenderWindow win(sf::VideoMode(WIDTH, HEIGHT), "Game Of Life");
  Life game(WIDTH, HEIGHT, 5);

  std::cout << "Starting application..." << std::endl;
  while (win.isOpen()) {
    handleEvents(win);
    win.clear();
    game.draw(win);
    win.display();
  }
  
  return 0;
}