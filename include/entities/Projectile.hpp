#pragma once
#include "Entity.hpp"
#include "../utils/Config.hpp"

enum class ProjectileOwner {
  Player,
  Enemy
};

class Projectile : public Entity {
public:
  Projectile(
    sf::Texture& texture,
    sf::Vector2f position,
    sf::Vector2f direction,
    ProjectileOwner owner
  );

  void update(float dt) override;

  ProjectileOwner getOwner() const { return owner; }

  Circle circleBounds() const override;

private:
  sf::Vector2f direction;
  float speed = Config::W/1.6f;  // 700f -> /1.82f   750.f -> 1.7f   800.f -> /1.6
  ProjectileOwner owner;
};

