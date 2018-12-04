#ifndef CLIMATE_GAME_HPP
#define CLIMATE_GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/String.hpp>
#include <iostream>
#include <thread>
#include <array>

#include "backgroundParticles.hpp"
#include "enemy.hpp"
#include "forestFireEnemy.hpp"
#include "gameObject.hpp"
#include "hurricaneEnemy.hpp"
#include "player.hpp"
#include "smokeBullet.hpp"
#include "waterBullet.hpp"

class ClimateGame;

class ClimateGame {
 public:
  sf::RenderWindow window;

  sf::Clock clock;
  sf::Clock animateParticlesTimer;
  sf::Clock enemySpawnTimer;

  // Game window properties
  static const int SCREEN_WIDTH = 1600;
  static const int SCREEN_HEIGHT = 1000;

  int enemyNum = 0;
  int enemiesLeft = 0;
  std::array<Enemy, 10> enemies;

  Player player;
  int currentBullet = 0;
  std::array<PlayerBullet, 50> playerBullets;

  BackgroundParticles particle;

  // Main texture to pull other textures off of
  sf::Texture mainTexture;

  sf::Text playerScoreText;
  unsigned long long int playerScore = 0;

  ClimateGame();

  void run();
  void update(sf::Time time);
  void processEvents();
  void render();

  void spawnEnemies();
  static bool isInBlastZone(sf::Vector2f pos);

 private:
  // Blast zone (invisible border) of constant width around screen
  static const int BLAST_ZONE = 200;

  sf::Font font;

  sf::Text helpText;
  sf::Text titleText;

  // Background texture
  sf::Sprite backgroundSprite;
  sf::Texture backgroundTexture;
};

#endif  // CLIMATE_GAME_HPP
