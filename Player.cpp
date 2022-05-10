#include "Player.hpp"
#include <iostream>
#include "VecFunctions.hpp"
#include <algorithm> // std::max

Player::Player(sf::Vector2f pos) : movement(pos) {}

void Player::setup(TextureLoader *t)
{
    textures = t;
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    sf::Sprite sprite;
    if (!movement.disconnect)
    {
        auto t = textures->get("run");
        sprite.setTexture(*t);
        sprite.scale(1.f * movement.runingDirection, -1.f * movement.direction);
        sprite.setOrigin(t->getSize().x / 2, t->getSize().y);
    }
    else
    {
        auto t = textures->get("squeeze");
        sprite.setTexture(*t);
        sprite.scale(1.f * movement.runingDirection, -1.f * movement.direction);
        sprite.setOrigin(t->getSize().x / 2, t->getSize().y / 2);
    }

    target.draw(sprite, states);
}

float getBetweenAngle(float a1, float a2)
{
    if (a1 < 0)
        a1 = 360 + a1;
    if (a2 < 0)
        a2 = 360 + a1;

    float a = a1 - a2;

    if (a < 0)
    {
        if (fabs(a) < fabs(a + 360.f))
            return a;
        else
            return a + 360.f;
    }
    else
    {
        if (fabs(a) < fabs(a - 360.f))
            return a;
        else
            return a - 360.f;
    }
}

void Player::update(sf::Time deltaTime, Track &track)
{
    movement.update(deltaTime, track);
    setPosition(movement.position);
    setAngle(deltaTime);
}

void Player::setAngle(sf::Time deltaTime)
{
    float difference = getBetweenAngle(movement.angle * 180.f / M_PI, getRotation());
    float o = 0.2f * deltaTime.asMilliseconds();
    if (compareFloat(difference, 0.f) || compareFloat(difference, 180.f))
    {
        setRotation(movement.angle * 180.f / M_PI);
    }
    else if (difference > 0)
    {
        difference = getBetweenAngle(movement.angle * 180.f / M_PI, getRotation() + o);
        if (difference <= 0)
        {
            setRotation(movement.angle * 180.f / M_PI);
        }
        else
        {
            rotate(o);
        }
    }
    else
    {
        difference = getBetweenAngle(movement.angle * 180.f / M_PI, getRotation() - o);
        if (difference >= 0)
        {
            setRotation(movement.angle * 180.f / M_PI);
        }
        else
        {
            rotate(-o);
        }
    }
}