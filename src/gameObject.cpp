#include "gameObject.hpp"

GameObject::GameObject() : GameObject::GameObject(sf::Vector2f(0, 0), NULL) {}

GameObject::GameObject(const sf::Vector2f& position, ClimateGame* game) {
  this->game = game;
  this->sprite.setPosition(position);
}

void GameObject::update(const sf::Time& timeElapsed) {}

bool GameObject::isColliding(GameObject* obj) {
  return (obj->enabled &&
          sprite.getGlobalBounds().intersects(obj->sprite.getGlobalBounds()));
}

void GameObject::enable() { this->enabled = true; }

void GameObject::disable() { this->enabled = false; }

bool GameObject::isEnabled() { return this->enabled; }
