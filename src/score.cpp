#include "../score.h"

Score::Score(Field& field, sf::Text& text_score) {
  x_ = field.GetWidth() - text_score.getLocalBounds().width - 20;
  y_ = 20;
  num_score_ = 0;
}
void Score::ScoreDraw(sf::RenderWindow& window, sf::Text& text_score, Field& field) {
  text_score.setString("SCORE: " + std::to_string(num_score_));
  text_score.setCharacterSize(24);
  text_score.setFillColor(sf::Color::Blue);
  text_score.setPosition(field.GetWidth() - text_score.getLocalBounds().width - 20, y_);
  window.draw(text_score);
}