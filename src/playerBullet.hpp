#ifndef PLAYER_BULLET_HPP
#define PLAYER_BULLET_HPP

#include "enemy.hpp"
#include "gameObject.hpp"

class PlayerBullet : public GameObject {
 public:
  bool enabled = false;

  PlayerBullet();

  void update(const sf::Time& timeElapsed) override;
  void setVelocity(const sf::Vector2f& velocity);

 private:
  sf::Vector2f velocity;

  static const int SIZE = 20;

  // Rectangles for taking texture off of main texture
  static const sf::IntRect COMPOST_RECT, DIET_RECT, UNPLUG_RECT;

  // Returns a random pre-defined rectangle for the bullet texture
  sf::IntRect getRandomRect();
};

#endif  // PLAYER_BULLET_HPP
