#include<math.h>

float getBetweenAngle(float a1, float a2)
{
    if (a1 < 0)
        a1 = 360 + a1;
    if (a2 < 0)
        a2 = 360 + a1;

    float a = a1 - a2;

    if (a < 0)
    {
        if (fabs(a) < fabs(a + 360.f))
            return a;
        else
            return a + 360.f;
    }
    else
    {
        if (fabs(a) < fabs(a - 360.f))
            return a;
        else
            return a - 360.f;
    }
}