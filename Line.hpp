#ifndef LINE
#define LINE

#include <SFML/Graphics.hpp>

using namespace std;

// enum class

class Line : public sf::Drawable
{
public:
    sf::Vector2f pointA;
    sf::Vector2f pointB;
    float flyingDirection = -1.f;

    Line();

    Line(sf::Vector2f pA, sf::Vector2f pB);
    // Line(const Line &l);
    // Line &operator=(const Line &l);

    bool detect(Line *line);

    float getAngle();
    float getSlope();
    float getC();

    sf::Vector2f getIntersect(Line *line);

    sf::Vector2f getHitPoint(Line *line, sf::Vector2f point);

    bool isType0();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

#endif