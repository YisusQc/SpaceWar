#include "../../include/entities/Player.hpp"
#include "../../include/utils/Config.hpp"
#include <SFML/Audio/AudioResource.hpp>
#include <SFML/Window/Keyboard.hpp>

Player::Player(
  const PlayerControls& controls_,
  sf::Texture& idle,
  std::vector<sf::Texture*>& upFrames,
  std::vector<sf::Texture*>& downFrames,
  std::vector<sf::Texture*>& destroyFrames,
  sf::Vector2f targetPos,
  std::vector<std::unique_ptr<Projectile>>& projectilesRef,
  sf::Texture& projectileTex,
  AudioManager& audioRef
) : projectiles(projectilesRef), projectileTexture(projectileTex), audio(audioRef) {

  controls = controls_;
  sprite.emplace(idle);
  sprite->setTexture(idle);
  sprite->setScale({Config::GLOBAL_SCALE, Config::GLOBAL_SCALE});

  spawnTarget = targetPos;

  auto bounds = sprite->getLocalBounds();
  sprite->setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});

  // Nace fuera de la pantalla
  sprite->setPosition({-Config::W/8.53f, targetPos.y});

  animIdle.addFrame(idle);
  animIdle.setFrameTime(0.f);

  for (auto* t : upFrames) animUp.addFrame(*t);
  for (auto* t : downFrames) animDown.addFrame(*t);
  for (auto* t : destroyFrames) animDestroy.addFrame(*t);

  animUp.setFrameTime(0.08f);
  animDown.setFrameTime(0.08f);
  animDestroy.setFrameTime(0.40f);
  animDestroy.setLoop(false);
}

void Player::updateSpawning(float dt) {
  sprite->move({Config::W/3.2f * dt, 0.f});

  if (sprite->getPosition().x >= spawnTarget.x) {
    sprite->setPosition(spawnTarget);
    state = PlayerState::Active;
  }
}

void Player::shoot(std::vector<std::unique_ptr<Projectile>>& projectiles,
                   sf::Texture& projectileTexture) {

  if (shootTimer > 0.f)
    return;

  sf::Vector2f pos = sprite->getPosition();
  sf::Vector2f dir = {1.f, 0.f};

  projectiles.push_back(
    std::make_unique<Projectile>(
      projectileTexture,
      pos,
      dir,
      ProjectileOwner::Player
    )
  );

  shootTimer = shootCooldown;
  audio.playSound(SoundType::PlayerShoot);
}

void Player::handleInput() {
  velocity = {0.f, 0.f};

  if (sf::Keyboard::isKeyPressed(controls.up)) {
    velocity.y -= speed;
    setAnimation(PlayerAnim::MoveUp);
  }
  else if (sf::Keyboard::isKeyPressed(controls.down)) {
    velocity.y += speed;
    setAnimation(PlayerAnim::MoveDown);
  }
  else {
    setAnimation(PlayerAnim::Idle);
  }

  if (sf::Keyboard::isKeyPressed(controls.left))
    velocity.x -= speed;
  if (sf::Keyboard::isKeyPressed(controls.right))
    velocity.x += speed;
  if (sf::Keyboard::isKeyPressed(controls.shoot))
    shoot(projectiles, projectileTexture);
}

void Player::update(float dt) {
  if (state == PlayerState::Spawning) {
    updateSpawning(dt);
    return;
  }

  if (state == PlayerState::Destroying) {
    updateAnimation(dt);
    if (animDestroy.finished()) {
      state = PlayerState::Dead;
      destroy();
    }
    return;
  }

  // Solo si está activo
  shootTimer -= dt;
  handleInput();
  sprite->move(velocity * dt);
  updateAnimation(dt);
}

void Player::setAnimation(PlayerAnim anim) {
  if (currentAnim == anim) return;

  currentAnim = anim;

  switch (anim) {
    case PlayerAnim::Idle:
      animIdle.reset();
      break;
    case PlayerAnim::MoveUp:
      animUp.reset();
      break;
    case PlayerAnim::MoveDown:
      animDown.reset();
      break;
    case PlayerAnim::Destroy:
      animDestroy.reset();
      state = PlayerState::Destroying;
      break;
  }
}

void Player::updateAnimation(float dt) {
  Animation* anim = nullptr;

  switch (currentAnim) {
    case PlayerAnim::Idle: anim = &animIdle; break;
    case PlayerAnim::MoveUp: anim = &animUp; break;
    case PlayerAnim::MoveDown: anim = &animDown; break;
    case PlayerAnim::Destroy: anim = &animDestroy; break;
  }

  anim->update(dt);
  sprite->setTexture(anim->getCurrentTexture());
}

