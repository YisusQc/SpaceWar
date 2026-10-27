#include "../../include/entities/Neutral.hpp"
#include "../../include/utils/Config.hpp"
#include <SFML/System/Angle.hpp>

Neutral::Neutral(sf::Texture& texture, sf::Vector2f pos,
                 float speed, float rotation)
: rotationSpeed(rotation) {

  sprite.emplace(texture);
  sprite->setTexture(texture);
  sprite->setScale({Config::GLOBAL_SCALE, Config::GLOBAL_SCALE});

  auto b = sprite->getLocalBounds();
  sprite->setOrigin({b.size.x / 2.f, b.size.y / 2.f});

  sprite->setPosition(pos);
  velocity = {-speed, 0.f};
}

void Neutral::update(float dt) {
  sprite->move(velocity * dt);
  sprite->rotate(sf::degrees(rotationSpeed * dt));

  if (sprite->getPosition().x < -Config::W/6.4f)
    destroy();
}

Circle Neutral::circleBounds() const {
  auto b = sprite->getGlobalBounds();
  sf::Vector2f c(b.getCenter());
  float r = std::min(b.size.x, b.size.y) * 0.4f;
  return {c, r};
}

