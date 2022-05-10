#include "GBox.hpp"

GBox::GBox(Line *lA, Line *lB, sf::Texture *pipe)
    : lineA(lA), lineB(lB), pipe(pipe)
{
}

GBox::GBox() {}

void GBox::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if (lineA != nullptr && lineB != nullptr)
    {
        sf::VertexArray vertex(sf::Quads, 4);
        vertex[0].position = lineA->pointA;
        vertex[1].position = lineA->pointB;
        vertex[2].position = lineB->pointB;
        vertex[3].position = lineB->pointA;

        vertex[0].texCoords = sf::Vector2f(0, 0);
        vertex[1].texCoords = sf::Vector2f(pipe->getSize().x, 0);
        vertex[2].texCoords = sf::Vector2f(pipe->getSize());
        vertex[3].texCoords = sf::Vector2f(0, pipe->getSize().y);

        target.draw(vertex, pipe);
    }
}