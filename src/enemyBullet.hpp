#ifndef ENEMY_BULLET_HPP
#define ENEMY_BULLET_HPP

#include "gameObject.hpp"

class EnemyBullet : public GameObject {
 public:
  bool enabled = false;

  EnemyBullet();
  EnemyBullet(const sf::Vector2f& pos, ClimateGame* game);

  void update(const sf::Time& timeElapsed) override;
  sf::Vector2f getVelocity();
  void setVelocity(const sf::Vector2f& v);

 private:
  // Rectangle for taking texture off of main texture
  static const sf::IntRect TEXTURE_RECT;

  static const int SIZE = 25;

  sf::Vector2f velocity;
};

#endif  // ENEMY_BULLET_HPP
