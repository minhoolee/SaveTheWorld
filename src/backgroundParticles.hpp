#ifndef BACKGROUND_PARTICLES_HPP
#define BACKGROUND_PARTICLES_HPP

#include <SFML/Graphics.hpp>

class BackgroundParticles {
 public:
  BackgroundParticles(int n);

  void animateParticlesIdle();
  void animateParticlesMovement();

  std::array<sf::CircleShape, 30> backgroundParticles;

 private:
  int num_particles;
};

#endif  // BACKGROUND_PARTICLES_HPP
