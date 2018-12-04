#ifndef FOREST_FIRE_ENEMY_HPP
#define FOREST_FIRE_ENEMY_HPP

#include <array>
#include "enemy.hpp"

class ForestFire : public Enemy {
 public:
  ForestFire(sf::Vector2f position, ClimateGame* game);

 private:
  // Rectangle for taking textures off of main texture
  static const sf::IntRect TEXTURE_RECT;

  static const int SIZE = 75;
};

#endif  // FOREST_FIRE_ENEMY_HPP
