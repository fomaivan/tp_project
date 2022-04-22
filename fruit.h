#pragma once
#include "SFML/Graphics.hpp"
#include "field.h"

class Fruit {
 public:
  int x_; int y_;
  Fruit();
  void DrawFruit(sf::Sprite& image_fruit, sf::RenderWindow& window, Field& field);
};
