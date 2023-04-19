#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "field.h"
#include "snake.h"
#include "fruit.h"
#include <ctime>
#include "score.h"


void GameOver(sf::RenderWindow& window, Field& field, sf::Sprite& field_image,
              sf::Text& game_over, int& num_score, sf::Music& sound_lose) {
  window.clear(sf::Color(200, 127, 227));
  for (int i = 0; i < field.N; i++) {
    for (int j = 0; j < field.M; j++) {
      field_image.setPosition(i * field.ts, j * field.ts);
      window.draw(field_image);
    }
  }
  game_over.setString("GAME OVER");
  game_over.setCharacterSize(64);
  game_over.setFillColor(sf::Color::Black);
  game_over.setPosition((field.GetWidth() - game_over.getLocalBounds().width) / 2,
                        ((field.GetHeight() - game_over.getLocalBounds().height) / 3));
  window.draw(game_over);
  game_over.setString("Score: "  + std::to_string(num_score));
  game_over.setCharacterSize(56);
  game_over.setFillColor(sf::Color::Black);
  game_over.setPosition((field.GetWidth() - game_over.getLocalBounds().width) / 2,
                        (field.GetHeight() - game_over.getLocalBounds().height) / 2);
  window.draw(game_over);
  window.display();
  sound_lose.play();
  sf::sleep(sf::seconds(5.0));
  window.close();
}

void ActionSnake(Snake& snake, int& size_snake, int& dir, Field& field, Fruit& fruit,
                 sf::Sound sound_ate_fruit, int& num_score, bool& GAME) {
  for (int i = size_snake; i > 0; i--) {
    snake.snake_[i].first = snake.snake_[i - 1].first;
    snake.snake_[i].second = snake.snake_[i - 1].second;
  }

  if (dir == 0) {
    snake.snake_[0].second += 1;
  }
  else if (dir == 1) {
    snake.snake_[0].first -= 1;
  }
  else if (dir == 2) {
    snake.snake_[0].first += 1;
  }
  else if (dir == 3) {
    snake.snake_[0].second -= 1;
  }

  if (snake.snake_[0].first > field.N) {
    GAME = false;
  }
  if (snake.snake_[0].first < 0) {
    GAME = false;
  }
  if (snake.snake_[0].second > field.M) {
    GAME = false;
  }
  if (snake.snake_[0].second < 0) {
    GAME = false;
  }

  if ((snake.snake_[0].first == fruit.x_) && (snake.snake_[0].second == fruit.y_)) {
    size_snake++;
    num_score++;
    sound_ate_fruit.play();
    fruit.x_ = rand() % field.N;
    fruit.y_ = rand() % field.M;
  }

  for (int i = 1; i < size_snake; i++) {
    if (snake.snake_[0].first == snake.snake_[i].first && snake.snake_[0].second == snake.snake_[i].second) {
      GAME = false;
    }
  }
}

void KeyboardInteraction(int& dir) {
  if (dir != 2 && sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    dir = 1;
  }
  if (dir != 1 && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    dir = 2;
  }
  if (dir != 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
    dir = 3;
  }
  if (dir != 3 && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
    dir = 0;
  }
}


void Game(float speed_snack) {
  bool GAME = true;

  sf::Texture texture_snake;
  texture_snake.loadFromFile("../images/snake.png");
  sf::Sprite snake_images(texture_snake);

  sf::Font score_font;
  sf::Text text_score;
  score_font.loadFromFile("../fonts/score_font.ttf");
  text_score.setFont(score_font);

  sf::Font game_over_font;
  sf::Text game_over;
  game_over_font.loadFromFile("../fonts/game_over_font.otf");
  game_over.setFont(game_over_font);


  sf::SoundBuffer temp_buffer_sound;
  temp_buffer_sound.loadFromFile("../sound/eat_fruit.wav");
  sf::Sound sound_ate_fruit(temp_buffer_sound);

  sf::Music sound_lose;
  sound_lose.openFromFile("../sound/lose.wav");

  sf::Texture texture_snake_head;
  texture_snake_head.loadFromFile("../images/snake_head.png");
  sf::Sprite snake_head_images(texture_snake_head);

  sf::Texture fruit_texture;
  fruit_texture.loadFromFile("../images/apple.png");
  sf::Sprite image_fruit(fruit_texture);

  sf::Texture field_texture;
  field_texture.loadFromFile("../images/tiles.png");
  sf::Sprite field_image(field_texture);

  Fruit fruit;
  Field field;
  Snake snake;
  Score score(field, text_score);

  sf::RenderWindow window(sf::VideoMode(field.N * field.ts, field.M * field.ts), "SNAKE!");

  srand(time(nullptr));

  sf::Clock clock;
  float timer = 0, delay = speed_snack;

  while (window.isOpen()) {
    float time = clock.getElapsedTime().asSeconds();
    clock.restart();
    timer += time;

    sf::Event event {};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
    KeyboardInteraction(snake.dir);
    if (GAME && timer > delay) {
      timer = 0;
      ActionSnake(snake, snake.size_snake, snake.dir, field, fruit, sound_ate_fruit, score.num_score_, GAME);
    }

    window.clear(sf::Color(200, 127, 227));
    field.DrawField(window, field_image);
    snake.DrawSnake(snake.size_snake, snake_head_images, field, window, snake_images);

    fruit.DrawFruit(image_fruit, window, field);

    if (!GAME) {
      GameOver(window, field, field_image, game_over, score.num_score_, sound_lose);
    }
    score.ScoreDraw(window, text_score, field);

    window.display();
  }
}
