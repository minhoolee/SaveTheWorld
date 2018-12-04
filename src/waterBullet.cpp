#include "waterBullet.hpp"
#include "climateGame.hpp"

const sf::IntRect WaterBullet::TEXTURE_RECT = sf::IntRect(78, 78, 9, 11);

WaterBullet::WaterBullet(sf::Vector2f pos, ClimateGame* game)
  : EnemyBullet(pos, game) {
  this->sprite.setTexture(game->mainTexture);
  this->sprite.setTextureRect(this->TEXTURE_RECT);

  // Adjust height and width (retaining proportion) to defined measurements
  double prop = (double)this->TEXTURE_RECT.height / this->TEXTURE_RECT.width;
  this->sprite.setScale((double)this->SIZE / this->TEXTURE_RECT.width,
                        (double)this->SIZE * prop / this->TEXTURE_RECT.height);
  this->sprite.setOrigin((double)this->TEXTURE_RECT.width / 2,
                         (double)this->TEXTURE_RECT.height * prop / 2);
}
