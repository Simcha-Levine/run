#ifndef TEXTURE_LOADER
#define TEXTURE_LOADER

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class TextureLoader
{
public:
    std::map<std::string, sf::Texture> textures;
    TextureLoader();

    void load();

    sf::Texture *get(std::string key);
};

#endif