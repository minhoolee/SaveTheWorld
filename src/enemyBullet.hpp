#ifndef ENEMY_BULLET_HPP
#define ENEMY_BULLET_HPP

#include "gameObject.hpp"

class EnemyBullet : public GameObject {
 public:
  bool enabled = false;

  EnemyBullet();
  EnemyBullet(sf::Vector2f pos, ClimateGame* game);

  void update(sf::Time time);
  sf::Vector2f getVelocity();
  void setVelocity(sf::Vector2f v);

 private:
  // Rectangle for taking texture off of main texture
  static const sf::IntRect TEXTURE_RECT;

  static const int SIZE = 25;

  sf::Vector2f velocity;
};

#endif  // ENEMY_BULLET_HPP
