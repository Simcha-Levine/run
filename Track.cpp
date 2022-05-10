#include <Track.hpp>
#include <iostream>
#include <math.h>
#include "VecFunctions.hpp"
#include <fstream>
#include <sstream>
#include <string>

bool randomBool()
{
    return rand() > (RAND_MAX / 2);
}

Track::Track()
{
}

Track::~Track()
{
    for (auto t : track)
    {
        delete t;
    }
}

void Track::buildLevel(const char *file_name, TextureLoader &textures)
{
    sf::Vector2f last1;
    sf::Vector2f last2;
    bool newLine = false;
    float direction = -1.f;

    ifstream file(file_name);

    if (!file.is_open())
        return;

    string line;

    while (getline(file, line))
    {
        stringstream sline(line);

        if (line.size() == 0 || line[0] == '#')
        {
            continue;
        }

        string seg;
        float f[3];
        int i = 0;
        while (getline(sline, seg, ','))
        {
            if (seg[0] != 't' && seg[0] != 'l' && seg[0] != 'c')
            {
                f[i++] = stof(seg);
            }
        }

        switch (line[0])
        {
        case 't':
            last1 = sf::Vector2f(f[0], f[1]);
            direction = f[2];
            newLine = true;
            break;
        case 'l':
            angleVec(last1, last2, f, direction, newLine, textures.get("pipe"));
            break;
        case 'c':
            makeTurn(last1, last2, f, direction, newLine, textures.get("pipe"));
            break;

        default:
            break;
        }
    }
}

void Track::makeTurn(sf::Vector2f &last1, sf::Vector2f &last2, float *f,
                     float direction, bool &newLine, sf::Texture *pipe)
{
    sf::Vector2f center = last1 + makeVec(f[0], f[1] * M_PI / 180.f);
    float radius = f[0];
    float angle = f[1] * M_PI / 180.f - M_PI;
    float addAngle = M_PI_2 / f[2];

    for (int i = 1; i < f[2]; i++)
    {
        track.push_back(new Line(last1, center + makeVec(radius, angle + (addAngle * i) * direction)));
        auto back = track.back();
        back->flyingDirection = direction;
        last1 = back->pointB;
        makeBottom(newLine, direction, last2);
        boxes.push_back(GBox(back, track.back(), pipe));
    }
    track.push_back(new Line(last1, center + makeVec(radius, angle + M_PI_2 * direction)));
    auto back = track.back();
    back->flyingDirection = direction;
    last1 = back->pointB;
    makeBottom(newLine, direction, last2);
    boxes.push_back(GBox(back, track.back(), pipe));
}

void Track::angleVec(sf::Vector2f &last1, sf::Vector2f &last2, float *f,
                     float direction, bool &newLine, sf::Texture *pipe)
{
    track.push_back(new Line(last1, last1 + makeVec(f[0], f[1] * M_PI / 180.f)));
    auto back = track.back();
    back->flyingDirection = direction;
    last1 = back->pointB;

    makeBottom(newLine, direction, last2);

    boxes.push_back(GBox(back, track.back(), pipe));
}

void Track::makeBottom(bool &newLine, float direction, sf::Vector2f &last2)
{
    auto &back1 = track.back();

    if (newLine)
    {
        auto pA = back1->pointA + makeVec(70.f, back1->getAngle() + (M_PI / 2.f * -direction));
        auto pB = back1->pointB + makeVec(70.f, back1->getAngle() + (M_PI / 2.f * -direction));
        track.push_back(new Line(pA, pB));
        auto back2 = track.back();
        last2 = back2->pointB;
        back2->flyingDirection = -direction;
        newLine = false;
    }
    else
    {
        auto pB = back1->pointB + makeVec(70.f, back1->getAngle() + (M_PI / 2.f * -direction));
        track.push_back(new Line(last2, pB));
        auto &back2 = track.back();
        back2->flyingDirection = -direction;
        last2 = back2->pointB;
    }
}

void Track::draw(sf::RenderTarget &target, sf::RenderStates) const
{

    for (auto &&box : boxes)
    {
        target.draw(box);
    }
}