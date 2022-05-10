#ifndef MOVEMENT
#define MOVEMENT

#include <SFML/Graphics.hpp>
#include "Line.hpp"
#include "Track.hpp"
#include <math.h>

class Movement
{
private:
    float momentum = 0.6f;
    Line *currentLine;
    Line *lastLine;

    float runningAngle = 0.f;

public:
    float angle = 0;
    sf::Vector2f position;

    bool disconnect = false;
    float direction = 1.f;
    float runingDirection = 1.f;

    Movement(sf::Vector2f pos);

    void gamePhysics(bool floor, float momentum, float millis, sf::Vector2f intersect);

    void update(sf::Time deltaTime, Track &track);

    void getRuningDirection();
};

#endif