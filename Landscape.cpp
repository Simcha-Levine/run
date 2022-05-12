#include "Landscape.hpp"
#include <iostream>

int setCords(sf::VertexArray &ver, int i, sf::Vector2f size, int dx, int dy)
{
    int X = size.x * dx;
    int Y = size.y * dy;

    ver[i++].position = sf::Vector2f(X, Y);
    ver[i++].position = sf::Vector2f(X + size.x, Y);
    ver[i++].position = sf::Vector2f(X + size.x, Y + size.y);
    ver[i++].position = sf::Vector2f(X, Y + size.y);

    return i;
}

int setTexCords(int i, sf::Vector2u size, sf::VertexArray &ver)
{
    ver[i++].texCoords = sf::Vector2f(0, 0);
    ver[i++].texCoords = sf::Vector2f(size.x, 0);
    ver[i++].texCoords = sf::Vector2f(size.x, size.y);
    ver[i++].texCoords = sf::Vector2f(0, size.y);

    return i;
}

Landscape::Landscape(sf::Vector2u winSize)
    : view(sf::FloatRect(0, 0, winSize.x, winSize.y)),
      tiles(sf::Quads, 4)
{
}

void Landscape::setup(TextureLoader *t)
{
    textures = t;
    shader.loadFromFile("assets/shaders/parallax.glsl", sf::Shader::Fragment);
    shader.setUniform("u_resolution", sf::Glsl::Vec2(view.getSize().x, view.getSize().y));
    shader.setUniform("texture", sf::Shader::CurrentTexture);

    int i = setCords(tiles, 0, view.getSize(), 0, 0);
    i = setTexCords(0, textures->get("landscape0")->getSize(), tiles);
}

void Landscape::update(sf::Vector2f pos, sf::Time deltaTime)
{
    shader.setUniform("playerPos", sf::Glsl::Vec2(pos));
    time += deltaTime.asSeconds();
    // shader.setUniform("u_time", time);
}

void Landscape::draw(sf::RenderTarget &target)
{
    target.setView(view);
    sf::RenderStates states;
    states.shader = &shader;

    shader.setUniform("layer", 0.3f);
    states.texture = textures->get("landscape0");
    target.draw(tiles, states);

    shader.setUniform("layer", 0.6f);
    states.texture = textures->get("landscape1");
    target.draw(tiles, states);

    shader.setUniform("layer", 0.9f);
    states.texture = textures->get("landscape2");
    target.draw(tiles, states);

    shader.setUniform("layer", 1.f);
    states.texture = textures->get("landscape3");
    target.draw(tiles, states);
}