#include "Movement.hpp"
#include "VecFunctions.hpp"
#include <algorithm> // std::max
#include <iostream>

Movement::Movement(sf::Vector2f pos)
    : position(pos)
{
}

void Movement::update(sf::Time deltaTime, Track &track)
{
    if (currentLine)
    {
        currentLine = track.track[0];
    }
    float myMomentum = momentum * deltaTime.asMilliseconds();

    bool floor = false;
    Line player1(makeVec(-10.f, angle - M_PI / 2.f) + position,
                 makeVec(10.f, angle - M_PI / 2.f) + position);
    Line player2(makeVec(-10.f, angle) + position,
                 makeVec(10.f, angle) + position);
    Line *player = &player1;

    for (auto line : track.track)
    {

        if (player1.detect(line))
        {
            floor = true;
            currentLine = line;
            // break;
        }
        else
        {
            if (player2.detect(line))
            {
                floor = true;
                player = &player2;
                currentLine = line;
                // break;
            }
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !disconnect)
    {
        disconnect = true;
        direction = -(currentLine->flyingDirection);
    }

    gamePhysics(floor, myMomentum, deltaTime.asMilliseconds(), currentLine->getHitPoint(player, position));
}

void Movement::gamePhysics(bool floor, float momentum, float millis, sf::Vector2f intersect)
{
    if (floor && (!disconnect || lastLine != currentLine))
    {

        lastLine = currentLine;

        sf::Vector2f last = position;

        getRuningDirection();
        position = intersect;
        angle = currentLine->getAngle();
        position = position + makeVec(momentum * runingDirection, angle);
        disconnect = false;
        direction = currentLine->flyingDirection;

        sf::Vector2f v(position - last);
        runningAngle = atan2(v.y, v.x);
    }
    else
    {
        sf::Vector2f last = position;

        position = position + makeVec(0.7f * millis * direction, angle - M_PI / 2.f) +
                   makeVec(momentum * runingDirection / 2.f, angle);
        disconnect = true;

        sf::Vector2f v(position - last);
        runningAngle = atan2(v.y, v.x);
    }
}

void Movement::getRuningDirection()
{
    float diffrance = abs(runningAngle - currentLine->getAngle());

    if (diffrance <= M_PI_2 || diffrance >= M_PI_2 * 3)
    {
        runingDirection = 1.f;
    }
    else
    {
        runingDirection = -1.f;
    }
}

sf::Vector2f makeVec(float r, float a)
{
    return sf::Vector2f(r * cos(a), r * sin(a));
}