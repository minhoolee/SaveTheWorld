#ifndef CLIMATE_GAME_HPP
#define CLIMATE_GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/String.hpp>
#include <array>
#include <iostream>

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

  void initTexts();
  void run();
  void win();
  void lose();
  void update(const sf::Time& timeElapsed);
  void processEvents();
  void render();
  void displayEnding();
  void centerJustify(sf::Text& text);
  void waitForKeyPress(sf::RenderWindow& window, sf::Keyboard::Key keyCode);

  void spawnEnemies();
  static bool isInBlastZone(const sf::Vector2f& pos);
  static std::string stringFromFile(const std::string& filename);

 private:
  // Blast zone (invisible border) of constant width around screen
  static const int BLAST_ZONE = 200;

  // Maximum 60 seconds of game play
  static const int MAX_TIME = 60;

  sf::Font font;
  sf::Text introText, helpText, titleText, timeText, endText, restartText;

  // Key for user to understand the meaning of the bullet colors
  sf::Sprite key;
  static const sf::IntRect KEY_RECT;

  enum class gameMode { INTRODUCTION, PLAYING, OVER } gameState;

  // Background texture
  sf::Sprite backgroundSprite;
  sf::Texture backgroundTexture;
};

#endif  // CLIMATE_GAME_HPP
