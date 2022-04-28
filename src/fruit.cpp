#include "../fruit.h"

Fruit::Fruit() : x_(15), y_(15) { }

void Fruit::DrawFruit(sf::Sprite& image_fruit, sf::RenderWindow& window, Field& field) {
  image_fruit.setPosition(x_ * field.ts, y_ * field.ts);
  window.draw(image_fruit);
}