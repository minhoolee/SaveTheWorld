#include "enemyBullet.hpp"
#include "climateGame.hpp"

EnemyBullet::EnemyBullet() : GameObject() {}

EnemyBullet::EnemyBullet(const sf::Vector2f& pos, ClimateGame* game)
    : GameObject(pos, game) {}

void EnemyBullet::update(const sf::Time& timeElapsed) {
  // std::cout << velocity.x << " " << velocity.y << std::endl;
  this->sprite.move(this->velocity * timeElapsed.asSeconds());

  if (ClimateGame::isInBlastZone(this->sprite.getPosition())) {
    this->disable();
  }

  if (game->player.isEnabled() && this->isColliding(&game->player)) {
    this->disable();
    game->player.disable();
    // game->player.sprite.setPosition((ClimateGame::SCREEN_WIDTH / 2),
    //                                 ((ClimateGame::SCREEN_HEIGHT * 7) / 8));
  }
}

sf::Vector2f EnemyBullet::getVelocity() {
  return this->velocity;
}

void EnemyBullet::setVelocity(const sf::Vector2f& v) {
  this->velocity = v;
}
