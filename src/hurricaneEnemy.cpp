#include "hurricaneEnemy.hpp"
#include "climateGame.hpp"
#include "waterBullet.hpp"

const sf::IntRect Hurricane::TEXTURE_RECT = sf::IntRect(230, 12, 70, 70);

Hurricane::Hurricane(sf::Vector2f position, ClimateGame* game)
  : Enemy(position, game) {
  this->sprite.setTexture(game->mainTexture);
  this->sprite.setTextureRect(this->TEXTURE_RECT);

  // Adjust height and width (retaining proportion) to defined measurements
  double prop = (double)this->TEXTURE_RECT.height / this->TEXTURE_RECT.width;
  this->sprite.setScale((double)this->SIZE / this->TEXTURE_RECT.width,
                        (double)this->SIZE * prop / this->TEXTURE_RECT.height);
  this->sprite.setOrigin((double)this->TEXTURE_RECT.width / 2,
                         (double)this->TEXTURE_RECT.height * prop / 2);

  for (int i = 0; i < bullets.size(); ++i) {
    bullets[i] = WaterBullet(position, game);
  }
}
