#include "TextureLoader.hpp"

TextureLoader::TextureLoader() {}

void TextureLoader::load()
{
    textures["landscape0"].loadFromFile("assets/landscape0.png");
    textures["landscape1"].loadFromFile("assets/landscape1.png");
    textures["landscape2"].loadFromFile("assets/landscape2.png");
    textures["landscape3"].loadFromFile("assets/landscape3.png");
    textures["pipe"].loadFromFile("assets/pipe.png");
    textures["run"].loadFromFile("assets/run.png");
    textures["squeeze"].loadFromFile("assets/squeeze.png");
}

sf::Texture *TextureLoader::get(std::string key)
{
    return &textures[key];
}