#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <cmath>
#include "enemyBullet.hpp"
#include "gameObject.hpp"

#define PI 3.14159265f

class Enemy : public GameObject {
 public:
  Enemy();
  Enemy(sf::Vector2f position, ClimateGame *game);

  std::array<EnemyBullet, 10> bullets;

  void update(sf::Time t);
  void idleAnimation();
  void attackPlayer(sf::Time &timeElapsed);
  void moveToFormation(sf::Time &timeElapsed);
  // void moveSequence(sf::ConvexShape &shape, sf::Time &timeElapsed,
  // sf::Vector2f &velocity, int point_num, int select_mode, int point_total,
  // double degrees_total);
  void moveSequence(sf::Time timeElapsed, sf::Vector2f &velocity, int point_num,
                    int select_mode, int point_total, double degrees_total);
  void fire();
  void disable() override;
  virtual int getBulletSpeed();

 private:
  // Rectangle for taking textures off of main texture
  static const sf::IntRect TEXTURE_RECT;

  static const int SIZE = 75;

  sf::Clock fireTimer;
  sf::Clock idleMovementTimer;
  sf::Clock idleAnimateTimer;
  sf::Clock moveTimer;

  // Game properties
  static const int ENEMY_SPEED = 500;
  static const int BULLET_SPEED = 800;

  // Circlular movements for enemies
  sf::ConvexShape shape1;
  sf::ConvexShape shape2;
  sf::ConvexShape shape3;
  sf::ConvexShape shape4;
  sf::CircleShape circle;

  int curr_bullet = 0;

  int order = 0;  // Sprite moves in a sequence (ellipse -> circle -> ellipse)

  int center_x = 1000;
  int center_y = 500;

  // Circle
  int radius = 200;
  // Ellipse
  int semi_axis_x = 350;
  int semi_axis_y = 200;
  // Sinusoid
  int amplitude = 0;
  float period = 0;

  int point_num = 0;
  float point_x = 0.0f;
  float point_y = 0.0f;
  double theta = 0;

  // Formation destination
  float destination_x = 600.0f;
  float destination_y = 300.0f;
  float seg_x = 0.0f;
  float seg_y = 0.0f;

  enum movementMode { CIRCLE, ELLIPSE, PARABOLA, SINUSOID } mode;

  // Enemy attributes
  bool hasWingsOpen = true;
  bool hasFired = false;
  bool isEnemyMovingRight = true;
};

#endif  // ENEMY_HPP
