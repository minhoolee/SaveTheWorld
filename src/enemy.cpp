#include "enemy.hpp"
#include <array>
#include "climateGame.hpp"

const sf::IntRect Enemy::TEXTURE_RECT = sf::IntRect(0, 0, 0, 0);

Enemy::Enemy() : GameObject() {}

Enemy::Enemy(sf::Vector2f position, ClimateGame* game)
  : GameObject(position, game) {
  this->sprite.setTexture(game->mainTexture);
  this->sprite.setTextureRect(this->TEXTURE_RECT);

  // Adjust height and width (retaining proportion) to defined measurements
  double prop = (double)this->TEXTURE_RECT.height / this->TEXTURE_RECT.width;
  this->sprite.setScale((double)this->SIZE / this->TEXTURE_RECT.width,
                        (double)this->SIZE * prop / this->TEXTURE_RECT.height);
  this->sprite.setOrigin((double)this->TEXTURE_RECT.width / 2,
                         (double)this->TEXTURE_RECT.height * prop / 2);

  for (int i = 0; i < bullets.size(); ++i) {
    bullets[i] = EnemyBullet(position, game);
  }
}

void Enemy::update(sf::Time timeElapsed) {
  for (EnemyBullet& b : this->bullets) {
    if (b.isEnabled()) {
      b.update(timeElapsed);
    }
  }

  sf::Vector2f velocity(0, 0);
  sf::Vector2f currPos = this->sprite.getPosition();

  // Cause the enemies to go back to the top of the screen when hitting the
  // bottom
  if (ClimateGame::isInBlastZone(currPos)) {
    this->sprite.setPosition(currPos.x, -100);
    this->hasFired = false;
  }

  // First 5 seconds idly move and then attack
  if (moveTimer.getElapsedTime().asSeconds() < 3.0f) {
    velocity.y = 100;
    sprite.move(velocity * timeElapsed.asSeconds());
  } else if (moveTimer.getElapsedTime().asSeconds() < 7.0f) {
    // Execute idle movement pattern
    if (idleMovementTimer.getElapsedTime().asSeconds() > 0.7f) {
      idleMovementTimer.restart();
      isEnemyMovingRight = !isEnemyMovingRight;
    }

    if (isEnemyMovingRight) {
      velocity.x = ENEMY_SPEED / 2;
    }

    else if (!isEnemyMovingRight) {
      velocity.x = -ENEMY_SPEED / 2;
    }

    sprite.move(velocity * timeElapsed.asSeconds());
  } else {
    // Break position and attack player after a certain amount of time
    attackPlayer(timeElapsed);
  }

  // Only execute once
  // if (order < 4) {
  //   if (moveTimer.getElapsedTime().asSeconds() > 0.005f) {
  //     moveTimer.restart();
  //
  //     switch (order) {
  //       case (0):
  //         amplitude = 200;
  //         period = 1.0f;
  //
  //         if (point_num == 0) {
  //           center_x = currPos.x;
  //           center_y = currPos.y;
  //         }
  //
  //         sprite.setPosition(point_x, point_y);
  //
  //         if (point_num <= 90) {
  //           moveSequence(timeElapsed, velocity, point_num, SINUSOID, 90,
  //                        -2 * 360);
  //           break;
  //         }
  //
  //         order++;
  //         point_num = 0;
  //         theta = 90;
  //
  //       case (1):
  //         semi_axis_x = 350;
  //         semi_axis_y = 200;
  //
  //         // Use sprite's current position to start sequence (only for
  //         starting
  //         // point)
  //         if (point_num == 0) {
  //           center_x = currPos.x -
  //                      (semi_axis_x * std::cos(theta * (PI / 180)));
  //           center_y = currPos.y -
  //                      (semi_axis_y * std::sin(theta * (PI / 180)));
  //         }
  //
  //         if (point_num <= 30) {
  //           // moveSequence(this->shape2, timeElapsed, velocity, point_num,
  //           // ELLIPSE, 30, 90);
  //           moveSequence(timeElapsed, velocity, point_num, ELLIPSE, 30, 90);
  //           sprite.setPosition(point_x, point_y);
  //           // moveSequence(timeElapsed, velocity, point_num, ELLIPSE, 15,
  //           90); break;
  //         }
  //
  //         // Move onto next sequence
  //         order++;
  //         point_num = 0;                       // Reset counter
  //         theta = 180;                         // New initial theta
  //         center_x -= (semi_axis_x - radius);  // Move shape
  //
  //       case (2):
  //         radius = 200;
  //
  //         point_x = center_x + (radius * std::cos(theta * (PI / 180)));
  //         point_y = center_y + (radius * std::sin(theta * (PI / 180)));
  //
  //         sprite.setPosition(point_x, point_y);
  //
  //         if (point_num <= 60) {
  //           // moveSequence(this->shape3, timeElapsed, velocity, point_num,
  //           // CIRCLE, 60, 270);
  //           moveSequence(timeElapsed, velocity, point_num, CIRCLE, 60, 270);
  //           break;
  //         }
  //
  //         // Move onto next sequence
  //         order++;
  //         point_num = 0;
  //         theta = 90;
  //         center_y -= (semi_axis_x - radius);
  //
  //       case (3):
  //         semi_axis_x = 200;
  //         semi_axis_y = 350;
  //
  //         point_x = center_x + (semi_axis_x * std::cos(theta * (PI / 180)));
  //         point_y = center_y + (semi_axis_y * std::sin(theta * (PI / 180)));
  //
  //         sprite.setPosition(point_x, point_y);
  //
  //         if (point_num <= 30) {
  //           // moveSequence(this->shape4, timeElapsed, velocity, point_num,
  //           // ELLIPSE, 30, 90);
  //           moveSequence(timeElapsed, velocity, point_num, ELLIPSE, 30, 90);
  //           break;
  //         }
  //
  //         // Reset values
  //         order++;
  //         point_num = 0;
  //         theta = 0;
  //
  //         // Go from position into grid formation
  //         // moveToFormation(timeElapsed);
  //     }
  //   }
  // }

  // Execute other animations when not doing movement sequence
  // else {
  //   // Break position and attack player after a certain amount of time
  //   if (moveTimer.getElapsedTime().asSeconds() > 5.0f) {
  //     attackPlayer(timeElapsed);
  //   }
  //
  //   else {
  //     if (idleAnimateTimer.getElapsedTime().asSeconds() > 0.5f) {
  //       idleAnimateTimer.restart();
  //       hasWingsOpen = !hasWingsOpen;
  //       idleAnimation();
  //     }
  //
  //     // Execute idle movement pattern
  //     if (idleMovementTimer.getElapsedTime().asSeconds() > 0.7f) {
  //       idleMovementTimer.restart();
  //       isEnemyMovingRight = !isEnemyMovingRight;
  //     }
  //
  //     if (isEnemyMovingRight)
  //       velocity.x = ENEMY_SPEED / 2;
  //
  //     else if (!isEnemyMovingRight)
  //       velocity.x = -ENEMY_SPEED / 2;
  //
  //     sprite.move(velocity * timeElapsed.asSeconds());
  //   }
  // }
}

// FAILED ATTEMPT TO MOVE THEM INTO A GRID FORMATION
void Enemy::moveToFormation(sf::Time& timeElapsed) {
  sf::Clock movementTimer;

  for (int i = 0; i < 20; i++) {
    if (movementTimer.getElapsedTime().asSeconds() >= 0.01f) {
      movementTimer.restart();

      this->seg_x =
          (float)(this->destination_x - this->sprite.getPosition().x) / 20;
      this->seg_y =
          (float)(this->destination_y - this->sprite.getPosition().y) / 20;

      sprite.move(sf::Vector2f(seg_x, seg_y));
    }
  }

  order++;
}

void Enemy::idleAnimation() {
  // if (hasWingsOpen) {
  //   // Texture is facing left
  //   enemyTextureRect = sf::IntRect(18, 152, 13, 15);
  //   sprite.setTextureRect(enemyTextureRect);
  //   sprite.setScale(3, 3);
  //   sprite.setOrigin(6.5, 7.5);
  //   sprite.setRotation(90);
  // }
  //
  // else {
  //   // Texture is facing upwards
  //   enemyTextureRect2 = sf::IntRect(186, 153, 13, 12);
  //   sprite.setTextureRect(enemyTextureRect2);
  //   sprite.setRotation(0);
  //   sprite.setScale(3, 3);
  // }
}

void Enemy::attackPlayer(sf::Time& timeElapsed) {
  sf::Vector2f velocity(0, 0);
  double degrees = 0;

  // Rotate sprite so that it faces downwards
  // degrees = 270;
  // sprite.setRotation(degrees);

  // Rotate sprite so that it faces downwards (255 <= degrees <= 285; 30 degree
  // arc) degrees = rand() % 31 + 255; sprite.setRotation(degrees);

  float enemy_x = rand() % (ENEMY_SPEED) - ENEMY_SPEED / 2;
  float enemy_y =
      sqrt(pow(ENEMY_SPEED, 2) -
           pow(enemy_x, 2));  // Use pythagorean theorem to calculate the y
  // distance the enmey must travel

  // velocity.x = enemy_x;
  velocity.y = ENEMY_SPEED;

  // degrees = atan(velocity.y / velocity.x);
  // sprite.setRotation(degrees + 270);
  //
  sprite.move(velocity * timeElapsed.asSeconds());

  float maxFiringPos = 0.0f;
  maxFiringPos = rand() % (ClimateGame::SCREEN_HEIGHT / 4);

  if (sprite.getPosition().y > (ClimateGame::SCREEN_HEIGHT / 4)) {
    if (!hasFired) {
      fire();
      hasFired = true;
    }
  }
}

void Enemy::moveSequence(sf::Time timeElapsed, sf::Vector2f& velocity,
                         int point_num, int select_mode, int point_total,
                         double degrees_total) {
  // Range of theta (degrees) is 0 <= theta < 360
  if (theta >= 360) {
    theta = theta - 360;
  }

  sprite.setRotation(theta + 270);

  // Select flight path
  if (select_mode == CIRCLE) {
    point_x = center_x + (radius * std::cos(theta * (PI / 180)));
    point_y = center_y + (radius * std::sin(theta * (PI / 180)));
  }

  else if (select_mode == ELLIPSE) {
    point_x = center_x + (semi_axis_x * std::cos(theta * (PI / 180)));
    point_y = center_y + (semi_axis_y * std::sin(theta * (PI / 180)));
  }

  else if (select_mode == SINUSOID) {
    point_x = center_x + theta;
    point_y =
        center_y + (amplitude * (std::sin(period * (theta * (PI / 180)))));
  }

  velocity.x = point_x;
  velocity.y = point_y;

  // shape.setPoint(point_num, sf::Vector2f(point_x, point_y));

  this->point_num++;

  this->theta += (degrees_total /
                  point_total);  // Increment by number of degrees necessary to
  // create a total number of degrees
}

void Enemy::fire() {
  // When enemy fires, make it turn to the bottom and move off the screen
  // Fire a random number (up until a maximum) of bullets at random positions
  // for (int bullet_num = 0; bullet_num < rand() % this->bullets.size();
  //      ++bullet_num) {
  EnemyBullet* bullet = &(this->bullets[curr_bullet]);

  bullet->sprite.setPosition(
      sf::Vector2f((this->sprite.getPosition().x),
                   (this->sprite.getPosition().y) + 10.5 + 10));
  bullet->enable();

  float enemy_x =
      fmod(rand(),
           (this->getBulletSpeed() / 6.0) -
           ((this->getBulletSpeed() / 6.0 * 2) +
            1));  // Bullets can fly in any direction of a certain range
  float enemy_y =
      sqrt(pow(this->getBulletSpeed(), 2) -
           pow(enemy_x, 2));  // Use pythagorean theorem to calculate the y
  // distance the bullet must travel

  bullet->setVelocity(sf::Vector2f(enemy_x, enemy_y));

  // If bullet not set, set a couple values on it
  if (bullet->game == NULL) {
    std::cout << "Bullet game not set" << std::endl;
    bullet->game = game;
  }

  // Move to next bullet in circular array
  curr_bullet = (curr_bullet + 1) % this->bullets.size();
  // }
}

void Enemy::disable() {
  GameObject::disable();
  this->point_num = 0;
}

int Enemy::getBulletSpeed() {
  return this->BULLET_SPEED;
}
