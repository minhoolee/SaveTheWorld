#include "playerBullet.hpp"
#include "climateGame.hpp"

const sf::IntRect PlayerBullet::COMPOST_RECT = sf::IntRect(78, 16, 5, 11);
const sf::IntRect PlayerBullet::DIET_RECT = sf::IntRect(78, 38, 5, 11);
const sf::IntRect PlayerBullet::UNPLUG_RECT = sf::IntRect(78, 58, 5, 11);

PlayerBullet::PlayerBullet() : GameObject() {
  sf::IntRect rect = getRandomRect();
  this->sprite.setTextureRect(rect);

  double prop = (double)rect.height / rect.width;
  this->sprite.setScale((double)this->SIZE / rect.width,
                        (double)this->SIZE * prop / rect.height);
  this->sprite.setOrigin((double)rect.width / 2,
                         (double)rect.height * prop / 2);
}

sf::IntRect PlayerBullet::getRandomRect() {
  int choice = rand() % 3;
  switch (choice) {
    case 0:
      return COMPOST_RECT;
      break;
    case 1:
      return DIET_RECT;
      break;
    case 2:
      return UNPLUG_RECT;
      break;
  }

  // Should never get to here
  return COMPOST_RECT;
}

void PlayerBullet::update(sf::Time timeElapsed) {
  this->sprite.setTexture(game->mainTexture);

  // Make sprite move upwards (negative)
  sprite.move(-velocity * timeElapsed.asSeconds());

  if (sprite.getPosition().y < 0) {
    enabled = false;
  }

  for (Enemy &e : game->enemies) {
    if (isColliding(&e)) {
      enabled = false;
      this->disable();
      e.disable();
      // e.point_num = 0;
      game->playerScore += 100;
      game->playerScoreText.setString(std::to_string(game->playerScore));
      break; // Only hit one enemy
    }
  }
}

void PlayerBullet::setVelocity(sf::Vector2f velocity) {
  this->velocity = velocity;
}
