#ifndef PLAYER
#define PLAYER

#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
#include "Track.hpp"
#include "Movement.hpp"
#include "TextureLoader.hpp"

using namespace std;

class Player : public sf::Drawable, public sf::Transformable
{
private:
    Movement movement;
    TextureLoader *textures = nullptr;

public:
    Player(sf::Vector2f pos);

    void setup(TextureLoader *t);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void update(sf::Time deltaTime, Track &track);

    void setAngle(sf::Time deltaTime);
};

#endif