#include <fstream>
#include <sstream>
#include <string>

#include "climateGame.hpp"

ClimateGame::ClimateGame()
  : window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Climate 2.0"),
    particle(BackgroundParticles(30)) {
  window.setFramerateLimit(60);

  backgroundTexture.loadFromFile("Textures/black_background.png");
  backgroundSprite.setTexture(backgroundTexture);
  backgroundSprite.setScale(10000, 10000);

  // Main texture to pull others off of
  mainTexture.loadFromFile("Textures/mainTexture.png");

  // Spawn player
  player =
      Player(sf::Vector2f((SCREEN_WIDTH / 2), (SCREEN_HEIGHT * 7 / 8)), this);

  font.loadFromFile("Fonts/galaga_fonts.ttf");

  introText.setString(ClimateGame::stringFromFile("txt/intro"));
  introText.setFillColor(sf::Color::White);
  introText.setFont(font);
  introText.setCharacterSize(20);
  introText.setPosition(sf::Vector2f(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f));
  sf::FloatRect textRect = introText.getLocalBounds();
  introText.setOrigin(textRect.left + textRect.width / 2.0f,
                      textRect.top + textRect.height / 2.0f);
}

void ClimateGame::init() {
  // Show player's score
  playerScoreText.setPosition(50, 30);
  playerScoreText.setFillColor(sf::Color::White);
  playerScoreText.setFont(font);
  playerScoreText.setCharacterSize(24);

  // Show help text
  helpText.setString(ClimateGame::stringFromFile("txt/help"));
  helpText.setFillColor(sf::Color::White);
  helpText.setFont(font);
  helpText.setCharacterSize(12);
  helpText.setPosition(sf::Vector2f(SCREEN_WIDTH / 2.0f, 60));
  sf::FloatRect textRect = helpText.getLocalBounds();
  helpText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top);

  // Create title text
  titleText.setString("SAVE THE WORLD");
  titleText.setFillColor(sf::Color::White);
  titleText.setFont(font);
  titleText.setCharacterSize(24);
  titleText.setPosition(helpText.getPosition().x,
                        helpText.getPosition().y - 30);
  textRect = titleText.getLocalBounds();
  titleText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top);
}

void ClimateGame::run() {
  srand((unsigned int)time(NULL));

  particle.animateParticlesIdle();

  sf::Event event;

  // Wait to begin game until user presses space key
  while (true) {
    window.pollEvent(event);

    if (event.type == sf::Event::KeyPressed) {
      if (event.key.code == sf::Keyboard::Space) {
        intro = false;
        break;
      }
    }

    render();
    sf::sleep(sf::seconds(0.5f));
  }

  init();

  // Start some game elements on startup
  spawnEnemies();

  sf::Time timeSinceLastUpdate = sf::Time::Zero;
  clock.restart();

  while (window.isOpen()) {
    playerScoreText.setString(std::to_string(playerScore));

    processEvents();
    timeSinceLastUpdate = clock.restart();
    update(timeSinceLastUpdate);

    render();  // Draw all the game objects, textures, and fonts
  }
}

void ClimateGame::update(const sf::Time& timeElapsed) {
  if (player.isEnabled()) {
    player.update(timeElapsed);
  }

  for (PlayerBullet& b : this->playerBullets) {
    if (b.isEnabled()) {
      b.update(timeElapsed);
    }
  }

  enemiesLeft = 0;

  for (Enemy& e : enemies) {
    if (e.isEnabled()) {
      e.update(timeElapsed);
      enemiesLeft++;
    }
  }

  if (enemiesLeft == 0) {
    enemyNum = 0;
    spawnEnemies();
  }

  if (animateParticlesTimer.getElapsedTime().asSeconds() > 3.0f) {
    animateParticlesTimer.restart();

    particle.animateParticlesIdle();
  }

  particle.animateParticlesMovement();
}

void ClimateGame::processEvents() {
  sf::Event event;

  while (window.pollEvent(event)) {
    // Click 'x' to exit
    if (event.type == sf::Event::Closed) {
      window.close();
    }

    // Control player with arrow keys and space
    if (event.type == sf::Event::KeyPressed) {
      if (event.key.code == sf::Keyboard::Up) {
        player.isPlayerMovingUp = true;
      }

      if (event.key.code == sf::Keyboard::Down) {
        player.isPlayerMovingDown = true;
      }

      if (event.key.code == sf::Keyboard::Left) {
        player.isPlayerMovingLeft = true;
      }

      if (event.key.code == sf::Keyboard::Right) {
        player.isPlayerMovingRight = true;
      }

      if (event.key.code == sf::Keyboard::Space) {
        player.isPlayerFiring = true;
      }

      // Press 'Q' to quit
      if (event.key.code == sf::Keyboard::Q) {
        window.close();
      }
    }

    if (event.type == sf::Event::KeyReleased) {
      if (event.key.code == sf::Keyboard::Up) {
        player.isPlayerMovingUp = false;
      }

      if (event.key.code == sf::Keyboard::Down) {
        player.isPlayerMovingDown = false;
      }

      if (event.key.code == sf::Keyboard::Left) {
        player.isPlayerMovingLeft = false;
      }

      if (event.key.code == sf::Keyboard::Right) {
        player.isPlayerMovingRight = false;
      }

      if (event.key.code == sf::Keyboard::Space) {
        player.isPlayerFiring = false;
      }
    }
  }
}

void ClimateGame::render() {
  window.clear();
  window.draw(backgroundSprite);

  if (player.isEnabled()) {
    window.draw(player.sprite);

    for (PlayerBullet& b : playerBullets) {
      if (b.isEnabled()) {
        window.draw(b.sprite);
      }
    }

    // Draw all enemies and their bullets if shooting
    for (Enemy& e : enemies) {
      if (e.isEnabled()) {
        window.draw(e.sprite);

        for (EnemyBullet& b : e.bullets) {
          if (b.isEnabled()) {
            window.draw(b.sprite);
          }
        }
      }
    }
  }

  // Draw all background particles
  for (sf::CircleShape& p : particle.backgroundParticles) {
    window.draw(p);
  }

  if (intro) {
    window.draw(introText);
  }

  window.draw(playerScoreText);
  window.draw(helpText);
  window.draw(titleText);
  window.display();
}

void ClimateGame::spawnEnemies() {
  // First half (hurricanes)
  int START_POS = 300;
  int spacing =
      (double)(ClimateGame::SCREEN_WIDTH - 2 * START_POS) / (enemies.size() / 2 - 1);

  for (int i = 0; i < enemies.size() / 2; ++i) {
    enemies[i] = Hurricane(sf::Vector2f(START_POS + (i * spacing), -150), this);
    enemies[i].enable();
    enemiesLeft++;
  }

  // Second half (forest fires)
  for (int i = enemies.size() / 2; i < enemies.size(); ++i) {
    enemies[i] = ForestFire(
                     sf::Vector2f(START_POS + ((i - enemies.size() / 2) * spacing), -50),
                     this);
    enemies[i].enable();
    enemiesLeft++;
  }
}

bool ClimateGame::isInBlastZone(const sf::Vector2f& pos) {
  return pos.x < -ClimateGame::BLAST_ZONE ||
         pos.x > ClimateGame::SCREEN_WIDTH + ClimateGame::BLAST_ZONE ||
         pos.y < -ClimateGame::BLAST_ZONE ||
         pos.y > ClimateGame::SCREEN_HEIGHT + ClimateGame::BLAST_ZONE;
}

std::string ClimateGame::stringFromFile(const std::string& filename) {
  std::ifstream file;
  std::stringstream buf;

  // Open file and direct contents to stringstream
  file.open(filename);
  buf << file.rdbuf();
  file.close();

  return buf.str();
}
