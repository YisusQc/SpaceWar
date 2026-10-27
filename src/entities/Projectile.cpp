#include "../../include/entities/Projectile.hpp"
#include "../../include/utils/Config.hpp"
#include <SFML/System/Angle.hpp>

Projectile::Projectile(
  sf::Texture& texture,
  sf::Vector2f position,
  sf::Vector2f dir,
  ProjectileOwner owner
)
: direction(dir), owner(owner) {

  sprite.emplace(texture);
  sprite->setTexture(texture);
  if (owner == ProjectileOwner::Enemy) {
    sprite->rotate(sf::degrees(180.f));
  }
  sprite->setScale({Config::GLOBAL_SCALE, Config::GLOBAL_SCALE});

  auto bounds = sprite->getLocalBounds();
  sprite->setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});

  sprite->setPosition(position);
}

void Projectile::update(float dt) {
  sprite->move(direction * speed * dt);

  // Destruir si sale de pantalla
  if (sprite->getPosition().x > Config::W/0.91f || sprite->getPosition().x < -Config::W/6.4f) {
    destroy();
  }
}

Circle Projectile::circleBounds() const {
  auto b = sprite->getGlobalBounds();
  sf::Vector2f c(b.getCenter());

  float r = std::min(b.size.x, b.size.y) * 0.35f; 
  return {c, r};
}

