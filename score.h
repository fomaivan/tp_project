#pragma once
#include "field.h"

class Score {
 public:
  int x_, y_;
  int num_score_;
  Score(Field& field, sf::Text& text_score);
  void ScoreDraw(sf::RenderWindow& window, sf::Text& text_score, Field& field);
};
