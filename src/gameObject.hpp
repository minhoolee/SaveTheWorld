#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <SFML/Graphics.hpp>

class ClimateGame;

class GameObject {
 public:
  GameObject();
  GameObject(const sf::Vector2f& position, ClimateGame *game);

  sf::Sprite sprite;
  ClimateGame *game;

  bool enabled = false;

  virtual void update(const sf::Time& timeElapsed);
  virtual void enable();
  virtual void disable();
  virtual bool isEnabled();

 protected:
  bool isColliding(GameObject *game);
};

#endif  // GAME_OBJECT_HPP
