#include "enemyBullet.hpp"
#include "climateGame.hpp"

EnemyBullet::EnemyBullet() : GameObject() {}

EnemyBullet::EnemyBullet(const sf::Vector2f& pos, ClimateGame* game)
    : GameObject(pos, game) {}

void EnemyBullet::update(const sf::Time& timeElapsed) {
  this->sprite.move(this->velocity * timeElapsed.asSeconds());

  // Disable bullets when they leave playable area
  if (ClimateGame::isInBlastZone(this->sprite.getPosition())) {
    this->disable();
  }

  // End the game if bullet hits player
  if (game->player.isEnabled() && this->isColliding(&game->player)) {
    this->disable();
    game->player.disable();
    game->lose();
  }
}

sf::Vector2f EnemyBullet::getVelocity() {
  return this->velocity;
}

void EnemyBullet::setVelocity(const sf::Vector2f& v) {
  this->velocity = v;
}
