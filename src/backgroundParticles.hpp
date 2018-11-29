#ifndef BACKGROUND_PARTICLES_HPP
#define BACKGROUND_PARTICLES_HPP

#include <SFML/Graphics.hpp>

class BackgroundParticles {
 public:
  BackgroundParticles(int n);

  void animateParticlesIdle();
  void animateParticlesMovement();

  sf::CircleShape backgroundParticles[30];

 private:
  int num_particles;
};

#endif  // BACKGROUND_PARTICLES_HPP
