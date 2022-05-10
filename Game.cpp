#include "Game.hpp"
#include <iostream>

Game::Game()
    : window(sf::VideoMode::getDesktopMode(), "Run", sf::Style::Fullscreen),
      // : window(sf::VideoMode(700, 700), "Run"),
      gameAction(window.getSize())
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

    window.setVerticalSyncEnabled(true);

    texture.create(window.getSize().x, window.getSize().y);

    gameAction.setup();
}

void Game::run()
{
    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q)
                window.close();
        }

        update(clock.getElapsedTime());
        // std::cout << clock.getElapsedTime().asMilliseconds() << '\n';
        clock.restart();
        draw();
    }
}

void Game::update(sf::Time deltaTime)
{

    gameAction.update(deltaTime);
    gameAction.draw(texture);
}

void Game::draw()
{
    window.clear();
    sprite.setTexture(texture.getTexture());
    window.draw(sprite);
    window.display();
}