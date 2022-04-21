#include "../snake.h"

Snake::Snake() {
  snake_.resize(600);
  size_snake = 5;
  dir = 2;
}

void Snake::DrawSnake(int& size_snake, sf::Sprite& snake_head_images,
               Field& field, sf::RenderWindow& window, sf::Sprite& snake_images) {
  for (int i = 0; i < size_snake; i++) {
    if (i == 0) {
      snake_head_images.setPosition(snake_[i].first * field.ts, snake_[i].second * field.ts);
      window.draw(snake_head_images);
      continue;
    }
    snake_images.setPosition(snake_[i].first * field.ts, snake_[i].second * field.ts);
    window.draw(snake_images);
  }
}