#ifndef CLIMATE_GAME_HPP
#define CLIMATE_GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/String.hpp>
#include <thread>

#include "backgroundParticles.hpp"
#include "enemy.hpp"
#include "gameObject.hpp"
#include "player.hpp"

class ClimateGame;

class ClimateGame {
 public:
  sf::RenderWindow window;

  sf::Clock clock;
  sf::Clock animateParticlesTimer;
  sf::Clock enemySpawnTimer;

  // Game window properties
  static const int GAME_WIDTH = 1600;
  static const int GAME_HEIGHT = 1000;
  static const int NUM_THREADS = 5;
  const int MAX_NUM_ENEMIES = 50;

  int enemyNum = 0;
  int enemiesLeft = 0;

  Player player;
  Enemy enemies[100];

  BackgroundParticles particle;

  int currentBullet = 0;
  PlayerBullet playerBullets[50];

  int currentEnemyBullet = 0;
  EnemyBullet enemyBullets[50];

  // Background texture
  sf::Sprite backgroundSprite;
  sf::Texture backgroundTexture;

  // sf::CircleShape backgroundParticles[30];

  // Main texture to pull other textures off of
  sf::Texture mainTexture;

  sf::Font font;

  sf::Text playerScoreText;
  sf::Text helpText;
  sf::Text titleText;

  unsigned long long int playerScore = 0;

  ClimateGame();

  void run();
  void update(sf::Time time);
  void processEvents();
  void render();

  void spawnEnemies(int count);
};

#endif  // CLIMATE_GAME_HPP
