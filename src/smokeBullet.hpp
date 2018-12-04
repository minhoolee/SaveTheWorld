#ifndef SMOKE_BULLET_HPP
#define SMOKE_BULLET_HPP

#include "enemyBullet.hpp"
#include "gameObject.hpp"

class SmokeBullet : public EnemyBullet {
 public:
  bool enabled = false;

  sf::Vector2f velocity;

  SmokeBullet(sf::Vector2f pos, ClimateGame* game);

 private:
  // Rectangle for taking texture off of main texture
  static const sf::IntRect TEXTURE_RECT;

  static const int SIZE = 75;
};

#endif  // SMOKE_BULLET_HPP
