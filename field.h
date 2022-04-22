#pragma once
#include "SFML/Graphics.hpp"

class Field {
 public:
  int N; int M;
  int ts;
  sf::Sprite tiles;
  Field();
  int GetWidth();
  int GetHeight();
  void DrawField(sf::RenderWindow& window, sf::Sprite& field_image);
};

