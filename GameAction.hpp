#ifndef GAME_ACTION
#define GAME_ACTION

#include <SFML/Graphics.hpp>
#include "Track.hpp"
#include "Player.hpp"
#include <vector>
#include "Landscape.hpp"
#include "TextureLoader.hpp"

class GameAction
{
private:
    sf::View view;
    Player player;
    Track track;
    Landscape landscape;
    TextureLoader textures;

public:
    bool finishedSetup = false;
    GameAction(sf::Vector2u winSize);

    void setup();

    void restart();

    void update(sf::Time deltaTime);

    void draw(sf::RenderTexture &render);
};

#endif
