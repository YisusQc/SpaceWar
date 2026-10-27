#include "../../include/utils/Config.hpp"
#include "../../include/extras/Text.hpp"
#include <SFML/Graphics/Rect.hpp>

Title::Title(sf::Font& font) {
  title.emplace(font);
  title->setFont(font);
  title->setCharacterSize(Config::W/9);
  title->setString("SpaceWar");
  title->setOutlineThickness(8.f);
  sf::FloatRect boundingTitle = title->getLocalBounds();
  title->setOrigin({boundingTitle.size.x/2.f, boundingTitle.size.y/2.f});
  title->setFillColor(sf::Color::Red);
  title->setOutlineColor(sf::Color::Black);
  title->setPosition({Config::W/2.f, Config::H/3.f});
}

void Title::draw(sf::RenderWindow& window) {
  window.draw(*title);
}

Menu::Menu(sf::Font& font) {
  onePlayerText.emplace(font);
  twoPlayerText.emplace(font);

  onePlayerText->setFont(font);
  onePlayerText->setCharacterSize(Config::W/12.f);
  onePlayerText->setString("> 1 Player");
  onePlayerText->setFillColor(sf::Color::Green);
  onePlayerText->setOutlineThickness(5.f);
  onePlayerText->setOutlineColor(sf::Color::Blue);
  sf::FloatRect boundingOnePlayerText = onePlayerText->getLocalBounds();
  onePlayerText->setOrigin({boundingOnePlayerText.size.x/2.f, boundingOnePlayerText.size.y/2.f});
  onePlayerText->setPosition({Config::W/2.f, Config::H/1.53f});
  onePlayerText->setFillColor(sf::Color::Green);

  twoPlayerText->setFont(font);
  twoPlayerText->setCharacterSize(Config::W/12.8f);
  twoPlayerText->setString("2 Players");
  twoPlayerText->setFillColor(sf::Color::Green);
  twoPlayerText->setOutlineThickness(2.f);
  twoPlayerText->setOutlineColor(sf::Color::Black);
  sf::FloatRect boundingTwoPlayerText = twoPlayerText->getLocalBounds();
  twoPlayerText->setOrigin({boundingTwoPlayerText.size.x/2.f, boundingTwoPlayerText.size.y/2.f});
  twoPlayerText->setPosition({Config::W/2.f, Config::H/1.53f + onePlayerText->getLocalBounds().size.y + Config::H/42.66f});
  twoPlayerText->setFillColor(sf::Color::Green);
}

void Menu::setSelection(bool twoPlayers) {
  twoPlayersSelected = twoPlayers;

  if (twoPlayersSelected) {
    twoPlayerText->setString("> 2 Players");
    twoPlayerText->setOutlineThickness(5.f);
    twoPlayerText->setOutlineColor(sf::Color::Blue);
    twoPlayerText->setFillColor(sf::Color::Green);
    twoPlayerText->setCharacterSize(Config::W/12.f);
    sf::FloatRect boundingTwoPlayerText = twoPlayerText->getLocalBounds();
    twoPlayerText->setOrigin({boundingTwoPlayerText.size.x/2.f, boundingTwoPlayerText.size.y/2.f});
    twoPlayerText->setPosition({Config::W/2.f- Config::W/42.66f, Config::H/1.53f + onePlayerText->getLocalBounds().size.y + Config::H/42.66f - Config::H/36.f});

    onePlayerText->setString("1 player");
    onePlayerText->setOutlineThickness(2.f);
    onePlayerText->setOutlineColor(sf::Color::Black);
    onePlayerText->setCharacterSize(Config::W/12.8f);
    sf::FloatRect boundingOnePlayerText = onePlayerText->getLocalBounds();
    onePlayerText->setOrigin({boundingOnePlayerText.size.x/2.f, boundingOnePlayerText.size.y/2.f});
    onePlayerText->setPosition({Config::W/2.f + Config::W/42.66f, Config::H/1.53f - Config::H/36.f});
  } else {
    onePlayerText->setString("> 1 Player");
    onePlayerText->setOutlineThickness(5.f);
    onePlayerText->setOutlineColor(sf::Color::Blue);
    onePlayerText->setCharacterSize(Config::W/12.f);
    sf::FloatRect boundingOnePlayerText = onePlayerText->getLocalBounds();
    onePlayerText->setOrigin({boundingOnePlayerText.size.x/2.f, boundingOnePlayerText.size.y/2.f});
    onePlayerText->setPosition({Config::W/2.f, Config::H/1.53f});

    twoPlayerText->setString("2 Players");
    twoPlayerText->setOutlineThickness(2.f);
    twoPlayerText->setOutlineColor(sf::Color::Black);
    twoPlayerText->setCharacterSize(Config::W/12.8f);
    sf::FloatRect boundingTwoPlayerText = twoPlayerText->getLocalBounds();
    twoPlayerText->setOrigin({boundingTwoPlayerText.size.x/2.f, boundingTwoPlayerText.size.y/2.f});
    twoPlayerText->setPosition({Config::W/2.f, Config::H/1.53f + onePlayerText->getLocalBounds().size.y + Config::H/42.66f});
  }
}

void Menu::draw(sf::RenderWindow& window) {
  window.draw(*onePlayerText);
  window.draw(*twoPlayerText);
}

Restart::Restart(sf::Font& font) {
  restart.emplace(font);
  restart->setFont(font);
  restart->setCharacterSize(Config::W/25.6);
  restart->setString("Press 'Enter' to resume");
  sf::FloatRect boundingTitle = restart->getLocalBounds();
  restart->setOrigin({boundingTitle.size.x/2.f, boundingTitle.size.y/2.f});
  restart->setPosition({Config::W/2.f, Config::H/1.2f});
}

void Restart::draw(sf::RenderWindow& window) {
  window.draw(*restart);
}

Timer::Timer(sf::Font& font) {
  timer.emplace(font);
  timer->setFont(font);
  timer->setCharacterSize(Config::W/42.66);
  sf::FloatRect boundingTitle = timer->getLocalBounds();
  timer->setOrigin({boundingTitle.size.x/2.f, boundingTitle.size.y/2.f});
  timer->setPosition({Config::W/2.f, Config::H/24.f});
}
 void Timer::setString(std::string string) {
  timer->setString(string);
  sf::FloatRect boundingTitle = timer->getLocalBounds();
  timer->setOrigin({boundingTitle.size.x/2.f, boundingTitle.size.y/2.f});
  timer->setPosition({Config::W/2.f, Config::H/24.f});
}

void Timer::draw(sf::RenderWindow& window) {
  window.draw(*timer);
}

