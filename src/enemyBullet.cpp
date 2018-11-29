#include "enemyBullet.hpp"
#include "climateGame.hpp"

EnemyBullet::EnemyBullet() : GameObject() {
  /* enemyBulletTextureRect = sf::IntRect(364, 216, 5, 10); */
  /* sprite.setTextureRect(enemyBulletTextureRect); */
  sprite.setOrigin(2.5, 4);
  sprite.setScale(3, 3);
}

void EnemyBullet::update(sf::Time timeElapsed) {
  sprite.move(velocity * timeElapsed.asSeconds());

  if (sprite.getPosition().y > GAME_HEIGHT) {
    enabled = false;
  }

  if (game->player.enabled && isColliding(&game->player)) {
    // enabled = false;
    // game->player.enabled = false;
    game->player.sprite.setPosition((GAME_WIDTH / 2), ((GAME_HEIGHT * 7) / 8));
  }
}
