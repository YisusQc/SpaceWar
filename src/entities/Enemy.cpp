#include "../../include/entities/Enemy.hpp"
#include "../../include/utils/Config.hpp"
#include <random>

Enemy::Enemy(
  sf::Texture& texture,
  std::vector<sf::Texture*>& destroyFrames,
  sf::Vector2f targetPos,
  EnemyShootType shootType,
  float fireRate,
  float moveChangeRate
)
: shootType(shootType),
  fireRate(fireRate),
  moveChangeRate(moveChangeRate),
  spawnTarget(targetPos) {

  sprite.emplace(texture);
  sprite->setTexture(texture);
  sprite->setScale({Config::GLOBAL_SCALE, Config::GLOBAL_SCALE});

  auto b = sprite->getLocalBounds();
  sprite->setOrigin({b.size.x / 2.f, b.size.y / 2.f});

  sprite->setPosition({Config::W/0.91f, targetPos.y});

  for (auto* t : destroyFrames) animDestroy.addFrame(*t);

  animDestroy.setFrameTime(0.15f);
  animDestroy.setLoop(false);
}

void Enemy::updateSpawning(float dt) {
  sprite->move({-Config::W/4.26f * dt, 0.f});

  if (sprite->getPosition().x <= spawnTarget.x) {
    sprite->setPosition(spawnTarget);
    state = EnemyState::Active;
  }
}

void Enemy::shoot(
  std::vector<std::unique_ptr<Projectile>>& projectiles,
  sf::Texture& projectileTexture,
  sf::Vector2f playerPos
) {
  if (fireTimer > 0.f)
    return;

  sf::Vector2f pos = sprite->getPosition();
  sf::Vector2f dir;

  if (shootType == EnemyShootType::Straight) {
      dir = {-1.f, 0.f};
  } else {
    dir = playerPos - pos;
    float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    if (len != 0)
      dir /= len;
  }

  projectiles.push_back(
    std::make_unique<Projectile>(
      projectileTexture,
      pos,
      dir,
      ProjectileOwner::Enemy
    )
  );

  fireTimer = fireRate;
}

void Enemy::updateMovement(float dt) {
  moveTimer -= dt;

  if (moveTimer <= 0.f) {
    static std::mt19937 rng{std::random_device{}()};
    std::uniform_int_distribution<int> dist(-1, 1);

    velocity.y = static_cast<float>(dist(rng)) * 150.f;
    moveTimer = moveChangeRate;
  }

  sprite->move({0.f, velocity.y * dt});
}

void Enemy::startDestroy() {
  state = EnemyState::Destroying;
  animDestroy.reset();
}

void Enemy::update(float dt) {
  if (state == EnemyState::Spawning) {
    updateSpawning(dt);
    return;
  }

  if (state == EnemyState::Destroying) {
    animDestroy.update(dt);
    sprite->setTexture(animDestroy.getCurrentTexture());

    if (animDestroy.finished()) {
      state = EnemyState::Dead;
      destroy();
    }
    return;
  }

  // Solo si está activo
  fireTimer -= dt;
  updateMovement(dt);
}

