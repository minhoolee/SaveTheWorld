#include "player.hpp"
#include "climateGame.hpp"

Player::Player() : GameObject() {}

Player::Player(const sf::Vector2f& position, ClimateGame* game)
  : GameObject(position, game) {
  enabled = true;

  this->sprite.setTexture(game->mainTexture);
  this->playerTextureRect = sf::IntRect(21, 13, 48, 50);
  this->sprite.setTextureRect(playerTextureRect);

  // Adjust height and width (retaining proportion) to defined measurements
  double prop =
      (double)this->playerTextureRect.height / this->playerTextureRect.width;
  this->sprite.setScale(
      (double)this->SIZE / this->playerTextureRect.width,
      (double)this->SIZE * prop / this->playerTextureRect.height);
  this->sprite.setOrigin((double)this->playerTextureRect.width / 2,
                         (double)this->playerTextureRect.height * prop / 2);
}

void Player::update(const sf::Time& timeElapsed) {
  sf::Vector2f playerMovement(0, 0);

  if (this->isPlayerMovingUp) {
    playerMovement.y -= PLAYER_SPEED;
  }

  if (this->isPlayerMovingDown) {
    playerMovement.y += PLAYER_SPEED;
  }

  if (this->isPlayerMovingLeft) {
    playerMovement.x -= PLAYER_SPEED;
  }

  if (this->isPlayerMovingRight) {
    playerMovement.x += PLAYER_SPEED;
  }

  this->sprite.move(playerMovement * timeElapsed.asSeconds());

  if ((this->isPlayerFiring) &&
      (this->shotTimer.getElapsedTime().asSeconds() > 0.25)) {
    fire();
    this->shotTimer.restart();
  }
}

void Player::fire() {
  game->playerBullets[game->currentBullet].sprite.setPosition(
      sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y - 32 - 20));
  game->playerBullets[game->currentBullet].enable();
  game->playerBullets[game->currentBullet].setVelocity(
      sf::Vector2f(0, BULLET_SPEED));

  // If bullet not set, set a couple values on it
  if (game->playerBullets[game->currentBullet].game == NULL) {
    game->playerBullets[game->currentBullet].game = game;
  }

  game->currentBullet = (game->currentBullet + 1) % 50;
}
