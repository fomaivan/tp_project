#pragma once
#include "SFML/Graphics.hpp"
#include "field.h"
#include <vector>

class Snake {
 public:
  std::vector<std::pair<int, int>> snake_;
  int size_snake;
  int dir;
  Snake();

  void DrawSnake(int& size_snake, sf::Sprite& snake_head_images,
                 Field& field, sf::RenderWindow& window, sf::Sprite& snake_images);
};

