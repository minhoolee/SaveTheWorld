#ifndef WATER_BULLET_HPP
#define WATER_BULLET_HPP

#include "enemyBullet.hpp"
#include "gameObject.hpp"

class WaterBullet : public EnemyBullet {
 public:
  bool enabled = false;

  sf::Vector2f velocity;

  WaterBullet(const sf::Vector2f& pos, ClimateGame* game);

 private:
  // Rectangle for taking texture off of main texture
  static const sf::IntRect TEXTURE_RECT;

  static const int SIZE = 20;
};

#endif  // WATER_BULLET_HPP
