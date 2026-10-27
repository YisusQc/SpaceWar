#include "../../include/utils/Config.hpp"
#include "../../include/extras/Logo.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>

P1Logo::P1Logo(sf::Texture& texture) {
  p1Logo.emplace(texture);
  p1Logo->setTexture(texture);
  p1Logo->setScale({Config::W/1422.22f, Config::H/800.f});
  sf::FloatRect bounds = p1Logo->getLocalBounds();
  p1Logo->setOrigin(bounds.getCenter());
  p1Logo->setPosition({Config::W/5.81f, Config::H/1.16f});
}

void P1Logo::draw(sf::RenderWindow& window) {
  window.draw(*p1Logo);
}

P2Logo::P2Logo(sf::Texture& texture) {
  p2Logo.emplace(texture);
  p2Logo->setTexture(texture);
  p2Logo->setScale({Config::W/1600.f, Config::H/900.f});
  sf::FloatRect bounds = p2Logo->getLocalBounds();
  p2Logo->setOrigin(bounds.getCenter());
  p2Logo->setPosition({Config::W/1.08f, Config::H/1.34f});
}

void P2Logo::draw(sf::RenderWindow& window) {
  window.draw(*p2Logo);
}

EnemyLogo::EnemyLogo(sf::Texture& texture) {
  enemyLogo.emplace(texture);
  enemyLogo->setTexture(texture);
  enemyLogo->setScale({Config::W/640.f,Config::H/360.f});
  sf::FloatRect bounds = enemyLogo->getLocalBounds();
  enemyLogo->setOrigin(bounds.getCenter());
  enemyLogo->setPosition({Config::W/1.43f, Config::H/18.f});
}

void EnemyLogo::draw(sf::RenderWindow& window) {
  window.draw(*enemyLogo);
}

NeutralLogo::NeutralLogo(sf::Texture& texture) {
  neutralLogo.emplace(texture);
  neutralLogo->setTexture(texture);
  neutralLogo->setScale({Config::W/640.f, Config::H/360.f});
  sf::FloatRect bounds = neutralLogo->getLocalBounds();
  neutralLogo->setOrigin(bounds.getCenter());
  neutralLogo->setPosition({Config::W/4.41f, Config::H/4.23f});
}

void NeutralLogo::draw(sf::RenderWindow& window) {
  window.draw(*neutralLogo);
}

GameOverLogo::GameOverLogo(sf::Texture& texture) {
  gameOverLogo.emplace(texture);
  gameOverLogo->setTexture(texture);
  gameOverLogo->setScale({Config::W/1422.22f, Config::H/800.f});
  sf::FloatRect bounds = gameOverLogo->getLocalBounds();
  gameOverLogo->setOrigin(bounds.getCenter());
  gameOverLogo->setPosition({Config::W/2.f, Config::H/2.f});
}

void GameOverLogo::draw(sf::RenderWindow& window) {
  window.draw(*gameOverLogo);
}

VictoryLogo::VictoryLogo(sf::Texture& texture) {
  victoryLogo.emplace(texture);
  victoryLogo->setTexture(texture);
  victoryLogo->setScale({Config::W/1422.22f, Config::H/800.f});
  sf::FloatRect bounds = victoryLogo->getLocalBounds();
  victoryLogo->setOrigin(bounds.getCenter());
  victoryLogo->setPosition({Config::W/2.f, Config::H/2.f});
}

void VictoryLogo::draw(sf::RenderWindow& window) {
  window.draw(*victoryLogo);
}

