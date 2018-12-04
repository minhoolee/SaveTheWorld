#include "backgroundParticles.hpp"
#include "climateGame.hpp"

BackgroundParticles::BackgroundParticles(int n) : num_particles(n) {}

void BackgroundParticles::animateParticlesIdle() {
  for (int i = 0; i < num_particles; ++i) {
    // Particle has not reached bottom of game yet
    if (backgroundParticles[i].getPosition().y != 0 &&
        backgroundParticles[i].getPosition().y < ClimateGame::SCREEN_HEIGHT) {
      continue;
    }

    float random_x = 0.0f;
    float random_y = 0.0f;

    // Set random positions that are not within a border of 20 from the
    // left/right and 10 from the top/bottom
    random_x = (float)(rand() % (ClimateGame::SCREEN_WIDTH - 49)) + 20;
    random_y = (float)(rand() % (ClimateGame::SCREEN_HEIGHT - 49)) + 10;

    sf::Vector2f coord(random_x, random_y);

    backgroundParticles[i].setPosition(coord);

    int rand_r = rand() % 256;
    int rand_g = rand() % 256;
    int rand_b = rand() % 256;

    backgroundParticles[i].setFillColor(sf::Color(rand_r, rand_g, rand_b));

    // Some particles are bigger than others in order to have foreground and
    // backgrounds
    float random_radius = (rand() % 3) + 1;

    backgroundParticles[i].setRadius(random_radius);
  }
}

void BackgroundParticles::animateParticlesMovement() {
  for (int i = 0; i < num_particles; ++i) {
    int speed = backgroundParticles[i].getRadius();

    backgroundParticles[i].setPosition(
        backgroundParticles[i].getPosition().x,
        backgroundParticles[i].getPosition().y + speed);
  }
}
