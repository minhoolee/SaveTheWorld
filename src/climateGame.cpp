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

  player =
      Player(sf::Vector2f((SCREEN_WIDTH / 2), (SCREEN_HEIGHT * 7 / 8)), this);

  font.loadFromFile("Fonts/galaga_fonts.ttf");

  playerScoreText.setPosition(50, 30);
  playerScoreText.setFont(font);
  playerScoreText.setFillColor(sf::Color::White);
  playerScoreText.setCharacterSize(24);

  // Show help text
  helpText.setPosition(sf::Vector2f(SCREEN_WIDTH / 2.0f, 60));
  helpText.setFont(font);
  helpText.setFillColor(sf::Color::White);
  helpText.setString(
      "\n          Written by Mark Lee (2018)\
      \n          Press \"q\" to quit the game!\
      \n   Move with arrow keys and shoot with SPACE\
      \n   Finish within the time limit or you lose!");
  helpText.setCharacterSize(12);

  // Create title text
  titleText.setPosition(helpText.getPosition().x - 20,
                        helpText.getPosition().y - 30);
  titleText.setFont(font);
  titleText.setFillColor(sf::Color::White);
  titleText.setString("SAVE THE WORLD");
  titleText.setCharacterSize(24);

  // Center texts
  sf::FloatRect textRect = helpText.getLocalBounds();
  helpText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top);
  textRect = titleText.getLocalBounds();
  titleText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top);
}

void ClimateGame::run() {
  srand((unsigned int)time(NULL));

  sf::Time timeSinceLastUpdate = sf::Time::Zero;

  // Start some game elements on startup
  spawnEnemies();

  particle.animateParticlesIdle();

  while (window.isOpen()) {
    playerScoreText.setString(std::to_string(playerScore));

    processEvents();
    timeSinceLastUpdate = clock.restart();
    update(timeSinceLastUpdate);

    render();  // Draw all the game objects, textures, and fonts
  }
}

void ClimateGame::update(sf::Time time) {
  // float time_f = time.asSeconds();
  // void *thread_arg = &time_f;

  if (player.isEnabled()) {
    player.update(time);
  }

  for (PlayerBullet &b : this->playerBullets) {
    if (b.isEnabled()) {
      b.update(time);
    }
  }

  enemiesLeft = 0;
  for (Enemy &e : enemies) {
    if (e.isEnabled()) {
      e.update(time);
      enemiesLeft++;
    }
  }

  if (enemiesLeft == 0) {
    enemyNum = 0;
    spawnEnemies();
  }

  // if (enemySpawnTimer.getElapsedTime().asSeconds() > 0.05f) {
  //   if (enemyNum < enemiesLeft) {
  //     if (enemyNum < (enemiesLeft / 2)) {
  //       enemies[enemyNum] =
  //           Enemy(sf::Vector2f(SCREEN_WIDTH + 100, (SCREEN_HEIGHT / 2)),
  //           this);
  //       enemies[enemyNum].destination_x +=
  //           (100.0f * enemyNum);  // Set the enemies in a grid like formation
  //       enemies[enemyNum].enable();
  //       enemies[enemyNum].update(time);
  //       enemyNum++;
  //     }
  //   }
  // }
  //
  // if (enemySpawnTimer.getElapsedTime().asSeconds() > 0.1f) {
  //   enemySpawnTimer.restart();
  //
  //   if (enemyNum < enemiesLeft) {
  //     if (enemyNum >= (enemiesLeft / 2)) {
  //       enemies[enemyNum] = Enemy(
  //           sf::Vector2f(SCREEN_WIDTH + 100, (SCREEN_HEIGHT / 2) + 100),
  //           this);
  //       enemies[enemyNum].destination_x +=
  //           (100.0f * (enemyNum - (enemiesLeft / 2)));  // Next row of
  //           enemies
  //       enemies[enemyNum].enable();
  //       enemies[enemyNum].update(time);
  //       enemyNum++;
  //     }
  //   }
  // }

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

  if (player.isEnabled()) window.draw(player.sprite);

  for (PlayerBullet &b : playerBullets) {
    if (b.isEnabled()) {
      window.draw(b.sprite);
    }
  }

  // Draw all enemies and their bullets if shooting
  for (Enemy &e : enemies) {
    if (e.isEnabled()) {
      window.draw(e.sprite);
      for (EnemyBullet &b : e.bullets) {
        if (b.isEnabled()) {
          window.draw(b.sprite);
        }
      }
    }
  }

  // Draw all background particles
  for (sf::CircleShape &p : particle.backgroundParticles) {
    window.draw(p);
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
        sf::Vector2f(START_POS + ((i - enemies.size() / 2) * spacing), -100),
        this);
    enemies[i].enable();
    enemiesLeft++;
  }
}

bool ClimateGame::isInBlastZone(sf::Vector2f pos) {
  return pos.x < -ClimateGame::BLAST_ZONE ||
         pos.x > ClimateGame::SCREEN_WIDTH + ClimateGame::BLAST_ZONE ||
         pos.y < -ClimateGame::BLAST_ZONE ||
         pos.y > ClimateGame::SCREEN_HEIGHT + ClimateGame::BLAST_ZONE;
}
