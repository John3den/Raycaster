#pragma once
#include <glut.h>
#include "Trig.h"
#include "Vector.h"

void DrawPlayer2D();
void Display();
void DrawRays2D();
void Resize(int w, int h);

class Ray
{
public:
	float x, y, angle;
};

extern float playerAngle;
extern Vector2 player, playerDirection;
extern float frame1, frame2, fps;