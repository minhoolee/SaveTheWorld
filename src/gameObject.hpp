#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <SFML/Graphics.hpp>
#include <mutex>

class ClimateGame;

class GameObject {
 public:
  sf::Sprite sprite;
  ClimateGame *game;

  bool enabled = false;

  // Game properties
  static const int GAME_WIDTH = 1600;
  static const int GAME_HEIGHT = 1000;

  GameObject();
  GameObject(sf::Vector2f position, ClimateGame *game);

  virtual void update(sf::Time t);
  bool isColliding(GameObject *game);
};

#endif  // GAME_OBJECT_HPP
