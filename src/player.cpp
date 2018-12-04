#include "player.hpp"
#include "climateGame.hpp"

Player::Player() : GameObject() {}

Player::Player(sf::Vector2f position, ClimateGame* game)
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

void Player::update(sf::Time timeElapsed) {
  // Image starts pointed left, so rotate it 90 degrees clockwise
  // this->sprite.setRotation(90);

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

  /*
  // Disable if outside of walls
  if ( (this->sprite.getPosition().x > 32) && (this->sprite.getPosition().x <
  game->GAME_WIDTH - 32) )
  {
          if ( (this->sprite.getPosition().y > 32) &&
  (this->sprite.getPosition().y < game->GAME_HEIGHT - 32) )
          {
                  //TODO : FIGURE THIS OUT
          }
  }
  */

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
