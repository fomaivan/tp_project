#include "../field.h"

Field::Field() : N(35), M(25), ts(40) {
  sf::Texture field_texture;
  field_texture.loadFromFile("/Users/foma_ivan/CLionProjects/Tp_SNAKE_GAME/images/tiles.png");
  sf::Sprite temp_images(field_texture);
  tiles = temp_images;
}

int Field::GetWidth() {
  return N * ts;
}

int Field::GetHeight() {
  return M * ts;
}

void Field::DrawField(sf::RenderWindow& window, sf::Sprite& field_image) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      field_image.setPosition(i * ts, j * ts);
      window.draw(field_image);
    }
  }
}