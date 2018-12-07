#ifndef HURRICANE_ENEMY_HPP
#define HURRICANE_ENEMY_HPP

#include "enemy.hpp"

class Hurricane : public Enemy {
 public:
  Hurricane(const sf::Vector2f& position, ClimateGame *game);

 private:
  // Rectangle for taking textures off of main texture
  static const sf::IntRect TEXTURE_RECT;

  static const int SIZE = 75;
};

#endif  // HURRICANE_ENEMY_HPP
