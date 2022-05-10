#ifndef G_BOX
#define G_BOX

#include <SFML/Graphics.hpp>
#include <Line.hpp>

class GBox : public sf::Drawable
{
public:
    Line *lineA = nullptr;
    Line *lineB = nullptr;
    sf::Texture *pipe;

    GBox(Line *lA, Line *lB, sf::Texture *pipe);
    GBox();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

#endif