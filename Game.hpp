#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>
#include "GameAction.hpp"
class Game
{
private:
    sf::RenderWindow window;
    sf::RenderTexture texture;
    GameAction gameAction;
    sf::Sprite sprite;

public:
    Game();

    void run();

    void update(sf::Time deltaTime);

    void draw();
};

#endif