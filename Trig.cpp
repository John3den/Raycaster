#include "Trig.h"


float DegreeToRadians(float a) 
{
    return a * PI / 180.0; 
}
float ClampAngle(float a) 
{
    if (a > 359)
    {
        a -= 360;
    } 
    if (a < 0) 
    {
        a += 360; 
    }
    return a;
}
float Distance(float ax, float  ay, float  bx, float  by, float  ang)
{
    return cos(DegreeToRadians(ang)) * (bx - ax) - sin(DegreeToRadians(ang)) * (by - ay);
}

bool IsChroma(int r, int g, int b)
{
    if (r <= 100 && g >= 150 && b <= 100) return true;
    return false;
}