#ifndef LANDSCAPE
#define LANDSCAPE

#include <SFML/Graphics.hpp>
#include <vector>
#include "TextureLoader.hpp"

class Landscape
{
private:
    sf::View view;
    // std::vector<sf::Texture> layers;
    TextureLoader *textures = nullptr;
    sf::Shader shader;
    float time = 0;
    sf::VertexArray tiles;

public:
    Landscape(sf::Vector2u winSize);

    void setup(TextureLoader *textures);

    void update(sf::Vector2f pos, sf::Time deltaTime);

    void draw(sf::RenderTarget &target);
};

#endif