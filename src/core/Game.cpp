#include "../../include/core/Game.hpp"
#include "../../include/extras/PlayerControls.hpp"
#include "SFML/Window/WindowEnums.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <string>

PlayerControls p1Controls {
  sf::Keyboard::Key::W,
  sf::Keyboard::Key::S,
  sf::Keyboard::Key::A,
  sf::Keyboard::Key::D,
  sf::Keyboard::Key::T
};

PlayerControls p2Controls {
  sf::Keyboard::Key::Up,
  sf::Keyboard::Key::Down,
  sf::Keyboard::Key::Left,
  sf::Keyboard::Key::Right,
  sf::Keyboard::Key::RShift
};

bool collisionSoundOcurredP1, collisionSoundOcurredP2 = false;

Game::Game()
: window(sf::VideoMode({1280, 720}), "SpaceWar", sf::Style::None) {
  window.setFramerateLimit(60);

  worldBounds = sf::FloatRect({0.f, 0.f},{static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)});

  audio.loadResources();
  audio.playMusic(MusicType::Menu);

  if (!p1LogoTexture.loadFromFile("textures/logos/p1Logo.png")) { std::cout << "ERROR al cargar gameOverTexture\n"; }
  if (!p2LogoTexture.loadFromFile("textures/logos/p2Logo.png")) { std::cout << "ERROR al cargar gameOverTexture\n"; }
  if (!enemyLogoTexture.loadFromFile("textures/logos/enemyLogo.png")) { std::cout << "ERROR al cargar gameOverTexture\n"; }
  if (!neutralLogoTexture.loadFromFile("textures/logos/asteroidLogo.png")) { std::cout << "ERROR al cargar gameOverTexture\n"; }
  if (!gameOverLogoTexture.loadFromFile("textures/logos/gameoverLogo.png")) { std::cout << "ERROR al cargar gameOverTexture\n"; }
  if (!victoryLogoTexture.loadFromFile("textures/logos/victoryLogo.png")) { std::cout << "ERROR al cargar victoryLogoTexture\n"; }

  p1Logo.emplace(p1LogoTexture);
  p2Logo.emplace(p2LogoTexture);
  enemyLogo.emplace(enemyLogoTexture);
  neutralLogo.emplace(neutralLogoTexture);
  gameOverLogo.emplace(gameOverLogoTexture);
  victoryLogo.emplace(victoryLogoTexture);

  if (!titleFont.openFromFile("fonts/Asteroid Blaster.ttf")) { std::cout << "ERROR al cargar titleFont\n"; }
  if (!menuFont.openFromFile("fonts/Adventure Hollow.otf")) { std::cout << "ERROR al cargar menuFont\n"; }
  if (!restartfont.openFromFile("fonts/Bebas-Regular.otf")) { std::cout << "ERROR al cargar restartfont\n"; }
  if (!timerFont.openFromFile("fonts/Bebas-Regular.otf")) { std::cout << "ERROR al cargar timerFont\n"; }

  menu.emplace(menuFont);
  title.emplace(titleFont);
  restart.emplace(restartfont);
  timer.emplace(timerFont);

  if (!P1Texture.loadFromFile("textures/player/neutralP1.png")) { std::cout << "ERROR al cargar P1Texture\n"; }
  if (!P2Texture.loadFromFile("textures/player/neutralP2.png")) { std::cout << "ERROR al cargar P2Texture\n"; }
  if (!projectileTexture.loadFromFile("textures/shots/flame-orange.png")) { std::cout << "ERROR al cargar projectileTexture\n"; }
  if (!projectileEnemyTexture.loadFromFile("textures/shots/shot-blue.png")) { std::cout << "ERROR al cargar projectileEnemyTexture\n"; }
  if (!enemyTexture.loadFromFile("textures/enemies/enemy.png")) { std::cout << "ERROR al cargar enemyTexture\n"; }
  if (!neutralTexture.loadFromFile("textures/neutrals/asteroid.png")) { std::cout << "ERROR al cargar neutralTexture\n"; }

  P1UpTextures.reserve(3);
  P1DownTextures.reserve(3);
  P1DestroyTextures.reserve(7);

  P2UpTextures.reserve(3);
  P2DownTextures.reserve(3);
  P2DestroyTextures.reserve(7);

  enemyDestroyTextures.reserve(7);

   for (int i = 1; i <= 7; ++i) {
    enemyDestroyTextures.emplace_back();
    if (!enemyDestroyTextures.back().loadFromFile("textures/explosions/burst-orange0" + std::to_string(i) + ".png")) { std::cout << "ERROR destroy" << i << "\n"; }
    enemyDestroyFrames.push_back(&enemyDestroyTextures.back());
  }

  for (int i = 1; i <= 3; ++i) {
    P1UpTextures.emplace_back();
    if (!P1UpTextures.back().loadFromFile("textures/player/inclinedUpP10" + std::to_string(i) + ".png")) { std::cout << "ERROR upP1" << i << "\n"; }
    P1UpFrames.push_back(&P1UpTextures.back());
  }

  for (int i = 1; i <= 3; ++i) {
    P1DownTextures.emplace_back();
    if (!P1DownTextures.back().loadFromFile("textures/player/inclinedDownP10" + std::to_string(i) + ".png")) { std::cout << "ERROR downP1" << i << "\n"; }
    P1DownFrames.push_back(&P1DownTextures.back());
  }

  for (int i = 1; i <= 7; ++i) {
    P1DestroyTextures.emplace_back();
    if (!P1DestroyTextures.back().loadFromFile("textures/explosions/burst0" + std::to_string(i) + ".png")) { std::cout << "ERROR destroyP1" << i << "\n"; }
    P1DestroyFrames.push_back(&P1DestroyTextures.back());
  }

  for (int i = 1; i <= 3; ++i) {
    P2UpTextures.emplace_back();
    if (!P2UpTextures.back().loadFromFile("textures/player/inclinedUpP20" + std::to_string(i) + ".png")) { std::cout << "ERROR upP2" << i << "\n"; }
    P2UpFrames.push_back(&P2UpTextures.back());
  }

  for (int i = 1; i <= 3; ++i) {
    P2DownTextures.emplace_back();
    if (!P2DownTextures.back().loadFromFile("textures/player/inclinedDownP20" + std::to_string(i) + ".png")) { std::cout << "ERROR downP2" << i << "\n"; }
    P2DownFrames.push_back(&P2DownTextures.back());
  }

  for (int i = 1; i <= 7; ++i) {
    P2DestroyTextures.emplace_back();
    if (!P2DestroyTextures.back().loadFromFile("textures/explosions/burst0" + std::to_string(i) + ".png")) { std::cout << "ERROR destroyP2" << i << "\n"; }
    P2DestroyFrames.push_back(&P2DestroyTextures.back());
  }

  player1 = std::make_unique<Player>(
    p1Controls, P1Texture, P1UpFrames, P1DownFrames, P1DestroyFrames,
    sf::Vector2f({200.f, window.getSize().y / 3.f}),
    projectiles, projectileTexture, audio
  );

  player2 = std::make_unique<Player>(
    p2Controls, P2Texture, P2UpFrames, P2DownFrames, P2DestroyFrames,
    sf::Vector2f({220.f, window.getSize().y / 2.f}),
    projectiles, projectileTexture, audio
  );

  decorativeSpawner = std::make_unique<DecorativeSpawner>(window.getSize());
  decorativeSpawner->spawnInitial(decoratives);
}

void Game::run() {
  sf::Clock clock;

  while (window.isOpen()) {
    float dt = clock.restart().asSeconds();

    processEvents();

    if (started) {
      update(dt);
    }

    render();
  }
}

void Game::processEvents() {
  while (const std::optional event = window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      window.close();
    }

    if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
      if (key->scancode == sf::Keyboard::Scancode::Escape) {
        window.close();
      }

      if (gameState == GameState::WaitingStart) {
        if (key->scancode == sf::Keyboard::Scancode::Up || key->scancode == sf::Keyboard::Scancode::K && twoPlayers) {
          twoPlayers = false;
          menu->setSelection(false);
          audio.playSound(SoundType::Select);
        } else if (key->scancode == sf::Keyboard::Scancode::Up || key->scancode == sf::Keyboard::Scancode::K) {
          twoPlayers = true;
          menu->setSelection(true);
          audio.playSound(SoundType::Select);
        }
        if (key->scancode == sf::Keyboard::Scancode::Down || key->scancode == sf::Keyboard::Scancode::J && !twoPlayers) {
          twoPlayers = true;
          menu->setSelection(true);
          audio.playSound(SoundType::Select);
        } else if (key->scancode == sf::Keyboard::Scancode::Down || key->scancode == sf::Keyboard::Scancode::J) {
          twoPlayers = false;
          menu->setSelection(false);
          audio.playSound(SoundType::Select);
        }
        if (key->scancode == sf::Keyboard::Scancode::Enter) {
          started = true;
          gameState = GameState::Playing;
          audio.playMusic(MusicType::Gameplay);
        }
      } else if (gameState == GameState::GameOver || gameState == GameState::Victory) {
        if (key->scancode == sf::Keyboard::Scancode::Enter) {

          gameState = GameState::WaitingStart;
          gameState = GameState::WaitingStart;
          started = false;
          gameOver = false;
          victory = false;
          collisionSoundOcurredP1 = collisionSoundOcurredP2 = false;
          victoryTimer = 61.f;

          enemies.clear();
          projectiles.clear();
          neutrals.clear();

          player1 = std::make_unique<Player>(
            p1Controls, P1Texture, P1UpFrames, P1DownFrames, P1DestroyFrames,
            sf::Vector2f({200.f, window.getSize().y / 3.f}),
            projectiles, projectileTexture, audio
          );

          if (twoPlayers) {
            player2 = std::make_unique<Player>(
              p2Controls, P2Texture, P2UpFrames, P2DownFrames, P2DestroyFrames,
              sf::Vector2f({200.f, window.getSize().y / 2.f}),
              projectiles, projectileTexture, audio
            );
          }
        }
      }
    }
  }
}

void Game::update(float dt) {
  
  for (auto& p : projectiles)
    p->update(dt);

  if (gameState != GameState::Victory)
    handleCollisions();

  if (player1 && (player1->isAlive() || player1->isDestroying())) {
    player1->update(dt);
    clampEntity(*player1);
  }

  if (twoPlayers && player2 && (player2->isAlive() || player2->isDestroying())) {
    player2->update(dt);
    clampEntity(*player2);
  }

  for (auto& e : enemies) {
    e->update(dt);
    clampEnemyVertical(*e);

    std::vector<Player*> alivePlayers;
    if (player1 && player1->isAlive()) alivePlayers.push_back(player1.get());
    if (twoPlayers && player2 && player2->isAlive()) alivePlayers.push_back(player2.get());

    if (!alivePlayers.empty()) {
      // Elegir uno al azar
      static std::mt19937 rng{std::random_device{}()};
      std::uniform_int_distribution<size_t> dist(0, alivePlayers.size() - 1);

      Player* target = alivePlayers[dist(rng)];
      sf::Vector2f targetPos = target->bounds().getCenter();

      e->shoot(projectiles, projectileEnemyTexture, targetPos);
    }
  }

  std::erase_if(projectiles,
      [](const auto& p) { return !p->isAlive(); });

  enemySpawnTimer -= dt;

  if (gameState != GameState::Victory) {
    if (enemySpawnTimer <= 0.f && player1) {
    float y = static_cast<float>(rand() % window.getSize().y);
    enemies.push_back(
      enemyFactory.create(
        enemyTexture,
        enemyDestroyFrames,
        {1100.f, y}
      )
    );
    enemySpawnTimer = enemySpawnRate;
    }
  }

  std::erase_if(enemies,
      [](const auto& e) { return !e->isAlive(); });

  neutralSpawnTimer -= dt;

  if (neutralSpawnTimer <= 0.f) {
    float y = static_cast<float>(rand() % window.getSize().y);
    float speed = 100.f + rand() % 200;
    float rot = (rand() % 2 == 0 ? 1.f : -1.f) * (50.f + rand() % 100);

    neutrals.push_back(
      std::make_unique<Neutral>(
        neutralTexture,
        sf::Vector2f(1400.f, y),
        speed,
        rot
      )
    );

    neutralSpawnTimer = neutralSpawnRate;
  }

  for (auto& n : neutrals) {
    n->update(dt);
  }

  decorativeSpawner->update(dt, decoratives);

  for (auto& d : decoratives)
    d->update(dt);

  std::erase_if(decoratives,
      [](const auto& d) { return !d->isAlive(); });

  checkGameOver();

  if (gameState == GameState::Playing) {
    victoryTimer -= dt;
    if (victoryTimer <= 0.f) {
      bool p1Alive = player1 && player1->isAlive() && !player1->isDestroying();
      bool p2Alive = twoPlayers && player2 && player2->isAlive() && !player2->isDestroying();

      if (p1Alive || p2Alive) {
        gameState = GameState::Victory;
        audio.playMusic(MusicType::Menu);
      }
    }
  }

  if ((player1 && player1->isAlive() && !player1->isDestroying()) || twoPlayers && player2 && player2->isAlive() && !player2->isDestroying()) {
    int seconds = static_cast<int>(victoryTimer);
    int minutes = seconds / 60;
    int secs = seconds % 60;

    timer->setString(std::to_string(minutes) + ":" + (secs < 10 ? "0" : "") + std::to_string(secs));
  }

  if (gameState == GameState::Victory && !victory) {
    victory = true;
    for (auto& e : enemies) {
      e->startDestroy();
      audio.playSound(SoundType::EnemyExplosion);
    }
    audio.playSound(SoundType::Victory);
  }
}

void Game::render() {
  window.clear(sf::Color(16,27,45));

  if (gameState == GameState::WaitingStart) {

    for (auto& d : decoratives)
      d->draw(window);

    p1Logo->draw(window);
    p2Logo->draw(window);
    enemyLogo->draw(window);
    neutralLogo->draw(window);

    title->draw(window);
    menu->draw(window);

  } else if (gameState == GameState::Playing) {

    for (auto& d : decoratives)
      d->draw(window);

    for (auto& n : neutrals)
      n->draw(window);

    for (auto& p : projectiles)
      p->draw(window);

    if (started && player1 && (player1->isAlive() || player1->isDestroying())) {
      player1->draw(window);
    }

    if (twoPlayers && started && player2 && (player2->isAlive() || player2->isDestroying())) {
      player2->draw(window);
    }

    for (auto& e : enemies) {
      if (e->isAlive() || e->isDestroying()) {
        e->draw(window);
      }
    }

    timer->draw(window);

  } else if (gameState == GameState::GameOver) {

    for (auto& d : decoratives)
      d->draw(window);

    gameOverLogo->draw(window);
    restart->draw(window);

    for (auto& n : neutrals)
      n->draw(window);

    for (auto& p : projectiles)
      p->draw(window);

    for (auto& e : enemies) {
      if (e->isAlive() || e->isDestroying()) {
        e->draw(window);
      }
    }

  } else {

    for (auto& d : decoratives)
      d->draw(window);

    victoryLogo->draw(window);
    restart->draw(window);

    for (auto& n : neutrals)
      n->draw(window);

    for (auto& p : projectiles)
      p->draw(window);

    for (auto& e : enemies) {
      if (e->isAlive() || e->isDestroying()) {
        e->draw(window);
      }
    }

    if (started && player1 && player1->isAlive()) {
      player1->draw(window);
    }

    if (twoPlayers && started && player2 && player2->isAlive()) {
      player2->draw(window);
    }
  }

  window.display();
}

void Game::handleCollisions() {

  // Proyectiles vs enemigos / jugador
  for (auto& p : projectiles) {
    if (!p->isAlive()) continue;

    Circle cp = p->circleBounds();

    if (p->getOwner() == ProjectileOwner::Player) {
      for (auto& e : enemies) {
        if (e->isAlive()) {
          Circle ce = e->circleBounds();
          sf::Vector2f diff = cp.center - ce.center;
          float dist2 = diff.x*diff.x + diff.y*diff.y;
          float rsum = cp.radius + ce.radius;

          if (dist2 < rsum*rsum) {
            p->destroy();
            e->startDestroy();
            audio.playSound(SoundType::EnemyExplosion);
            break;
          }
        }
      }
      for (auto& n : neutrals) {
        if (!n->isAlive()) continue;

        Circle cn = n->circleBounds();
        sf::Vector2f diff = cp.center - cn.center;
        float dist2 = diff.x*diff.x + diff.y*diff.y;
        float rsum = cp.radius + cn.radius;

        if (dist2 < rsum*rsum) {
          p->destroy();
          break;
        }
      }

    } else {
      if (player1 && player1->isAlive()) {
        Circle cpl = player1->circleBounds();
        sf::Vector2f diff = cp.center - cpl.center;
        float dist2 = diff.x*diff.x + diff.y*diff.y;
        float rsum = cp.radius + cpl.radius;

        if (dist2 < rsum*rsum) {
          player1->setAnimation(PlayerAnim::Destroy);
          if (!collisionSoundOcurredP1) {
            audio.playSound(SoundType::PlayerExplosion);
            collisionSoundOcurredP1 = true;
          }
          p->destroy();
        }
      }
      if (twoPlayers && player2 && player2->isAlive()) {
        Circle cpl2 = player2->circleBounds();
        sf::Vector2f diff = cp.center - cpl2.center;
        float dist2 = diff.x*diff.x + diff.y*diff.y;
        float rsum = cp.radius + cpl2.radius;

        if (dist2 < rsum*rsum) {
          player2->setAnimation(PlayerAnim::Destroy);
          if (!collisionSoundOcurredP2) {
            audio.playSound(SoundType::PlayerExplosion);
            collisionSoundOcurredP2 = true;
          }
          p->destroy();
        }
      }
    }
  }

  // Player vs enemigo
  for (auto& e : enemies) {
    if (player1 && player1->isAlive() && e->isAlive() &&
      player1->bounds().findIntersection(e->bounds())) {
      player1->setAnimation(PlayerAnim::Destroy);
      if (!collisionSoundOcurredP1) {
        audio.playSound(SoundType::PlayerExplosion);
        collisionSoundOcurredP1 = true;
      }
      e->startDestroy();
    }
    if (twoPlayers && player2 && player2->isAlive() && e->isAlive() &&
      player2->bounds().findIntersection(e->bounds())) {
      player2->setAnimation(PlayerAnim::Destroy);
      if (!collisionSoundOcurredP2) {
        audio.playSound(SoundType::PlayerExplosion);
        collisionSoundOcurredP2 = true;
      }
      e->startDestroy();
    }
  }

  // Player vs neutrales
  for (auto& n : neutrals) {
    if (player1 && player1->isAlive() && n->isAlive()) {
      Circle c1 = player1->circleBounds();
      Circle c2 = n->circleBounds();

      sf::Vector2f diff = c1.center - c2.center;
      float dist2 = diff.x*diff.x + diff.y*diff.y;
      float rsum = c1.radius + c2.radius;

      if (dist2 < rsum*rsum) {
        player1->setAnimation(PlayerAnim::Destroy);
        if (!collisionSoundOcurredP1) {
          audio.playSound(SoundType::PlayerExplosion);
          collisionSoundOcurredP1 = true;
        }
      }
    }
    if (twoPlayers && player2 && player2->isAlive() && n->isAlive()) {
      Circle c1 = player2->circleBounds();
      Circle c2 = n->circleBounds();

      sf::Vector2f diff = c1.center - c2.center;
      float dist2 = diff.x*diff.x + diff.y*diff.y;
      float rsum = c1.radius + c2.radius;

      if (dist2 < rsum*rsum) {
        player2->setAnimation(PlayerAnim::Destroy);
        if (!collisionSoundOcurredP2) {
          audio.playSound(SoundType::PlayerExplosion);
          collisionSoundOcurredP2 = true;
        }
      }
    }
  }
}

void Game::checkGameOver() {
  bool p1Dead = player1 && !player1->isAlive();
  bool p2Dead = twoPlayers && player2 && !player2->isAlive();

  if (p1Dead && (!twoPlayers || p2Dead)) {
    if (gameState != GameState::GameOver) { 
      gameOver = true;
      gameState = GameState::GameOver;
      audio.playSound(SoundType::GameOver);
    }
    audio.playMusic(MusicType::Menu);
  }
}

void Game::clampEntity(Entity& entity) {
  auto bounds = entity.bounds();
  auto pos = entity.getPosition();

  float entityLeft   = pos.x - bounds.size.x / 2.f;
  float entityRight  = pos.x + bounds.size.x / 2.f;
  float entityTop    = pos.y - bounds.size.y / 2.f;
  float entityBottom = pos.y + bounds.size.y / 2.f;

  float worldLeft = worldBounds.getCenter().x - worldBounds.size.x / 2.f;
  float worldRight = worldBounds.getCenter().x + worldBounds.size.x / 2.f;
  float worldTop = worldBounds.getCenter().y - worldBounds.size.y / 2.f;
  float worldBottom = worldBounds.getCenter().y + worldBounds.size.y / 2.f;

  sf::Vector2f newPos = entity.bounds().getCenter();

  if (entityLeft < worldLeft)
    newPos.x += worldLeft - entityLeft;

  if (entityRight > worldRight)
    newPos.x -= entityRight - worldRight;

  if (entityTop < worldTop)
    newPos.y += worldTop - entityTop;

  if (entityBottom > worldBottom)
    newPos.y -= entityBottom - worldBottom;

  entity.setPosition(
    entity.getPosition() +
    (newPos - entity.bounds().getCenter())
  );
}

void Game::clampEnemyVertical(Entity& entity) {
  auto bounds = entity.bounds();
  auto pos = entity.getPosition();

  float entityTop = pos.y - bounds.size.y / 2.f;
  float entityBottom = pos.y + bounds.size.y / 2.f;
  float worldTop = worldBounds.getCenter().y - worldBounds.size.y / 2.f;
  float worldBottom = worldBounds.getCenter().y + worldBounds.size.y / 2.f;

  if (entityTop < worldTop)
    entity.setPosition({pos.x, pos.y + (worldTop - entityTop)});

  if (entityBottom > worldBottom)
    entity.setPosition({pos.x, pos.y - (entityBottom - worldBottom)});
}

