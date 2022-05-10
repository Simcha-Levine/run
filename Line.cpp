#include "Line.hpp"
#include <math.h>
#include <algorithm> // std::max
#include <iostream>

Line::Line(sf::Vector2f pA, sf::Vector2f pB) : pointA(pA), pointB(pB) {}
Line::Line() {}

bool compareFloat(double a, double b)
{
    return abs(a - b) < .1f;
}

bool isTouching(float x, float y, Line *line)
{
    return (y <= std::max(line->pointA.y, line->pointB.y) &&
            y >= std::min(line->pointA.y, line->pointB.y)) &&
           (x <= std::max(line->pointA.x, line->pointB.x) &&
            x >= std::min(line->pointA.x, line->pointB.x));
}

bool Line::detect(Line *line)
{
    sf::Vector2f v = getIntersect(line);

    return isTouching(v.x, v.y, this) && isTouching(v.x, v.y, line);
}

float Line::getAngle()
{
    sf::Vector2f v(pointB - pointA);
    return atan2(v.y, v.x);
}

float Line::getSlope()
{
    if (pointA.x - pointB.x != 0.f && pointA.y - pointB.y != 0.f)
    {
        return (pointA.y - pointB.y) / (pointA.x - pointB.x);
    }
    return 0.f;
}

float Line::getC()
{
    return pointB.y - pointB.x * getSlope();
}

bool Line::isType0()
{
    return compareFloat(pointA.x, pointB.x);
}

sf::Vector2f Line::getHitPoint(Line *line, sf::Vector2f point)
{
    if (isType0())
    {
        if (!line->isType0())
        {
            point.x = pointA.x;
            point.y = line->getSlope() * point.x + line->getC();
        }
    }
    else
    {
        if (line->isType0())
        {
            point.x = line->pointA.x;
            point.y = getSlope() * point.x + getC();
        }
        else
        {
            if (!compareFloat(getSlope(), line->getSlope()) && !compareFloat(getC(), line->getC()))
            {
                if (compareFloat(line->getSlope(), 0.f))
                {
                    point.x = (getC() - line->getC()) / (line->getSlope() - getSlope());
                    point.y = line->getSlope() * point.x + line->getC();
                }
                else
                {
                    point.x = (line->getC() - getC()) / (getSlope() - line->getSlope());
                    point.y = getSlope() * point.x + getC();
                }
            }
        }
    }
    return point;
}

sf::Vector2f Line::getIntersect(Line *line)
{
    sf::Vector2f v;
    if (isType0())
    {
        if (line->isType0())
        {
            v.x = pointA.x;
            v.y = min(max(pointA.y, pointB.y), max(line->pointA.y, line->pointB.y));
            // cout << "00\n";
        }
        else // 1
        {
            v.x = pointA.x;
            v.y = line->getSlope() * v.x + line->getC();
            // cout << "01\n";
        }
    }
    else // 1
    {
        if (line->isType0())
        {
            v.x = line->pointA.x;
            v.y = getSlope() * v.x + getC();
            // cout << "10\n";
        }
        else // 1
        {
            if (compareFloat(getSlope(), line->getSlope())) // m1 == m2
            {
                if (compareFloat(getC(), line->getC())) // c1 == c2
                {
                    if (max(pointA.x, pointB.x) < max(line->pointA.x, line->pointB.x))
                    {
                        if (pointA.x > pointB.x)
                        {
                            v = pointA;
                        }
                        else
                        {
                            v = pointB;
                        }
                    }
                    else
                    {
                        if (line->pointA.x > line->pointB.x)
                        {
                            v = line->pointA;
                        }
                        else
                        {
                            v = line->pointB;
                        }
                    }
                    // cout << "11 , m1 == m2 , c1 == c2\n";
                }
                else
                {
                    // cout << "11 , m1 == m2\n";
                }
            }
            else
            {
                if (compareFloat(line->getSlope(), 0.f))
                {
                    v.x = (getC() - line->getC()) / (line->getSlope() - getSlope());
                    v.y = line->getSlope() * v.x + line->getC();
                }
                else
                {
                    v.x = (line->getC() - getC()) / (getSlope() - line->getSlope());
                    v.y = getSlope() * v.x + getC();
                }
                // cout << "11\n";
            }
        }
    }
    return v;
}

void Line::draw(sf::RenderTarget &target, sf::RenderStates) const
{
    sf::VertexArray line(sf::Lines, 2);
    line[0].position = pointA;
    line[1].position = pointB;
    target.draw(line);

    float r = 3.f;
    sf::CircleShape circle(r);
    circle.setFillColor(sf::Color::Yellow);
    circle.setOrigin(r, r);
    circle.setPosition(pointA);
    target.draw(circle);
    circle.setPosition(pointB);
    target.draw(circle);
}