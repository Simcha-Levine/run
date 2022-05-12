#include "TextureLoader.hpp"

TextureLoader::TextureLoader() {}

void TextureLoader::load()
{
    textures["landscape0"].loadFromFile("assets/imgs/landscape0.png");
    textures["landscape1"].loadFromFile("assets/imgs/landscape1.png");
    textures["landscape2"].loadFromFile("assets/imgs/landscape2.png");
    textures["landscape3"].loadFromFile("assets/imgs/landscape3.png");
    textures["pipe"].loadFromFile("assets/imgs/pipe.png");
    textures["run"].loadFromFile("assets/imgs/run.png");
    textures["squeeze"].loadFromFile("assets/imgs/squeeze.png");
}

sf::Texture *TextureLoader::get(std::string key)
{
    return &textures[key];
}