#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>

#include "gameObject.hpp"
#include "playerBullet.hpp"

class Player : public GameObject {
 public:
  Player();
  Player(sf::Vector2f position, ClimateGame* game);

  void update(sf::Time t);
  void fire();

  // Player 1 controls : ARROW KEYS
  bool isPlayerMovingUp = false;
  bool isPlayerMovingDown = false;
  bool isPlayerMovingLeft = false;
  bool isPlayerMovingRight = false;
  bool isPlayerFiring = false;

 private:
  static const int PLAYER_SPEED = 400;
  static const int BULLET_SPEED = 1500;
  static const int WIDTH = 50;
  static const int HEIGHT = 50;
  static const std::string TEXTURE_FILE;

  sf::Clock shotTimer;

  sf::IntRect playerTextureRect;
};

#endif  // PLAYER_HPP
