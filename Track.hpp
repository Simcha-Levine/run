#ifndef TRACK
#define TRACK

#include <SFML/Graphics.hpp>
#include <vector>
#include "Line.hpp"
#include "GBox.hpp"
#include "TextureLoader.hpp"

class Track : public sf::Drawable
{
private:
    std::vector<GBox> boxes;

public:
    std::vector<Line *> track;
    Track();
    ~Track();

    void buildLevel(const char *file_name, TextureLoader &textures);
    void makeBottom(bool &newLine, float direction, sf::Vector2f &last2);
    void angleVec(sf::Vector2f &last1, sf::Vector2f &last2, float *f,
                  float direction, bool &newLine, sf::Texture *pipe);
    void makeTurn(sf::Vector2f &last1, sf::Vector2f &last2, float *f,
                  float direction, bool &newLine, sf::Texture *pipe);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

#endif