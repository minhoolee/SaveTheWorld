#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>

#include "gameObject.hpp"
#include "playerBullet.hpp"

class Player : public GameObject {
 public:
  Player();
  Player(const sf::Vector2f& position, ClimateGame* game);

  void update(const sf::Time& timeElapsed) override;
  void fire();

  // Player 1 controls : ARROW KEYS
  bool isPlayerMovingUp = false;
  bool isPlayerMovingDown = false;
  bool isPlayerMovingLeft = false;
  bool isPlayerMovingRight = false;
  bool isPlayerFiring = false;

 private:
  static const int PLAYER_SPEED = 400;
  static const int BULLET_SPEED = 1000;
  static const int SIZE = 75;

  sf::Clock shotTimer;

  sf::IntRect playerTextureRect;
};

#endif  // PLAYER_HPP
