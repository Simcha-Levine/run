#include "GameAction.hpp"
#include <iostream>

GameAction::GameAction(sf::Vector2u winSize)
    : view(sf::FloatRect(0, 0, winSize.x, winSize.y * -1.f)),
      player(sf::Vector2f(1.f, 0)),
      landscape(winSize)
{
    view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
    view.setCenter(sf::Vector2f(0, 0));
}

void GameAction::setup()
{
    textures.load();
    track.buildLevel("assets/levels/level.csv", textures);
    landscape.setup(&textures);
    player.setup(&textures);
    finishedSetup = true;
}

void GameAction::restart() {}

void GameAction::update(sf::Time deltaTime)
{
    player.update(deltaTime, track);

    view.setCenter(player.getPosition());
    // view.setRotation(player.getRotation());

    landscape.update(player.getPosition(), deltaTime);
}

void GameAction::draw(sf::RenderTexture &render)
{

    render.clear();

    landscape.draw(render);

    render.setView(view);

    render.draw(player);

    render.draw(track);

    render.display();
}