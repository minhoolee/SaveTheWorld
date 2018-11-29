#include "player.hpp"
#include "climateGame.hpp"

const std::string Player::TEXTURE_FILE = "Textures/earth.jpg";

Player::Player() : GameObject() {}

Player::Player(sf::Vector2f position, ClimateGame* game)
  : GameObject(position, game) {
  enabled = true;

  this->sprite.setTexture(game->mainTexture);
  this->playerTextureRect = sf::IntRect(15, 52, 20, 20);
  this->sprite.setTextureRect(playerTextureRect);

  this->sprite.setScale((double)this->WIDTH / this->playerTextureRect.width,
                        (double)this->HEIGHT / this->playerTextureRect.height);
  this->sprite.setOrigin((double)this->playerTextureRect.width / 2,
                         (double)this->playerTextureRect.height / 2);
}
/*  */
/* Player::Player(const Player& obj) { */
/*   this->texture.loadFromImage(obj.texture.copyToImage()); */
/* } */
/*  */
/* Player& Player::operator=(const Player& obj) { */
/*   this->texture.loadFromImage(obj.texture.copyToImage()); */
/*   return *this; */
/* } */

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
  game->playerBullets[game->currentBullet].enabled = true;
  game->playerBullets[game->currentBullet].velocity =
      sf::Vector2f(0, BULLET_SPEED);

  // If bullet not set, set a couple values on it
  if (game->playerBullets[game->currentBullet].game == NULL) {
    game->playerBullets[game->currentBullet].game = game;
    /* game->playerBullets[game->currentBullet].sprite.setTexture( */
    /*     game->mainTexture);  // 0th index because all bullet textures are same */
  }

  // Check if game is multiplayer and if the bullet was shot by player2 (hack
  // method)
  // if ( (game->MULTI_PLAYER) && (sprite.getPosition() ==
  // game->player2.sprite.getPosition()) )
  // game->playerBullets[game->currentBullet].sprite.setColor(sf::Color(255,
  // 255, 150));

  game->currentBullet++;

  if (game->currentBullet == 50) {
    game->currentBullet = 0;
  }
}
